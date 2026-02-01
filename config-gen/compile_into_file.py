import json
from pathlib import Path

directory = Path('./configs')
files = [json.loads(open(p).read()) for p in directory.iterdir() if p.is_file()]


# verify sizes
def get_size(file):
    s = 0
    for field in file["fields"]:
        s += field["size"]
    return s


for file in files:
    if file["depends_on"] is not None:
        assert (any([f["name"] == file["depends_on"] for f in files]))

    assert (file["size"] == get_size(file))

# compile
template = open("template.h").read()

"""
config{
    "test",
    "eth",
    10,
    std::vector<config_field>{config_field{
        "test",
        10
    }}
},
"""

with open("include/packet_configs.h", "w+") as out_file:
    output = ""

    for file in files:
        output += "config{\"" + file["name"] + "\"," + ("\"\"" if file["depends_on"] == None else f"\"{file['depends_on']}\"") + "," + str(file["size"]) + ","
        output += "std::vector<config_field>{"

        # the fields
        for field in file["fields"]:
            output += "config_field{"
            output += f"\"{field['name']}\"" + ","
            output += str(field["size"])
            output += "}"
            if field != file["fields"][-1]:
                output+=","

        output += "}}"
        if file != files[-1]:
            output += ","

    out_file.write(template.replace("REPLACE_CONFIGS", output))

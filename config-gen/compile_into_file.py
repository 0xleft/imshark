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
    assert(file["size"] == get_size(file))

# compile


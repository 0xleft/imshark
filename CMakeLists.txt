cmake_minimum_required(VERSION 3.30)

project(ImShark LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
        imgui
        GIT_REPOSITORY https://github.com/ocornut/imgui.git
        GIT_TAG v1.92.5
)

FetchContent_MakeAvailable(imgui)

set(IMGUI_DIR ${imgui_SOURCE_DIR})

set(IMGUI_SOURCES
        ${IMGUI_DIR}/imgui.cpp
        ${IMGUI_DIR}/imgui_draw.cpp
        ${IMGUI_DIR}/imgui_widgets.cpp
        ${IMGUI_DIR}/imgui_tables.cpp
        ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
        ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
)

add_library(imgui-lib STATIC ${IMGUI_SOURCES})

target_include_directories(imgui-lib PUBLIC
        ${IMGUI_DIR}
        ${IMGUI_DIR}/backends
)

FetchContent_Declare(
        libpcap
        GIT_REPOSITORY https://github.com/the-tcpdump-group/libpcap.git
        GIT_TAG libpcap-1.10.6
)

FetchContent_MakeAvailable(libpcap)

find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)

file(GLOB_RECURSE IMSHARK_SOURCES
        "src/*.cpp"
        "src/*/*.cpp"
        "src/*/*/*.cpp"
        "src/*/*/*/*.cpp"
        "src/*/*/*/*/*.cpp"
        "src/*.c"
        "src/*/*.c"
        "src/*/*/*.c"
        "src/*/*/*/*.c"
)

add_executable(ImShark ${IMSHARK_SOURCES})

target_include_directories(ImShark PRIVATE
        ${libpcap_SOURCE_DIR}
)

target_link_libraries(ImShark PRIVATE
        imgui-lib
        glfw
        OpenGL::GL
        pcap
)
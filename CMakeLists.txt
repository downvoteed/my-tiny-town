cmake_minimum_required(VERSION 3.22)
project(MyTinyTown LANGUAGES CXX)

include(FetchContent)

set(CMAKE_DOWNLOAD_EXTRACT_TIMESTAMP NEW)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
if (CMAKE_VERSION VERSION_GREATER_EQUAL "3.24.0")
    cmake_policy(SET CMP0135 NEW)
endif()
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(OpenGL REQUIRED)

FetchContent_Declare(
        glad
        GIT_REPOSITORY https://github.com/Dav1dde/glad.git)
FetchContent_Declare(
        glfw3
        URL https://github.com/glfw/glfw/releases/download/3.3.8/glfw-3.3.8.zip)
FetchContent_Declare(glm URL
        https://github.com/g-truc/glm/releases/download/0.9.9.8/glm-0.9.9.8.zip)
FetchContent_Declare(
    tinyobjloader
    GIT_REPOSITORY  https://github.com/tinyobjloader/tinyobjloader 
    GIT_TAG v1.0.6
) 
FetchContent_MakeAvailable(glfw3)
FetchContent_MakeAvailable(glm)
FetchContent_MakeAvailable(glad)
FetchContent_MakeAvailable(tinyobjloader)

set(SRC
        "main.cc"
        "lib/imgui/imgui.cpp"
        "lib/ImGuiFileDialog/ImGuiFileDialog.cpp"
        "lib/imgui/imgui_draw.cpp"
        "lib/imgui/backends/imgui_impl_opengl3.cpp"
        "lib/imgui/backends/imgui_impl_glfw.cpp"
        "lib/imgui/imgui_demo.cpp"
        "lib/imgui/imgui_tables.cpp"
        "lib/imgui/imgui_widgets.cpp")

add_executable(MyTinyTown main.cc ${SRC})

set_target_properties(MyTinyTown PROPERTIES CXX_STANDARD 20)
target_compile_options(MyTinyTown PRIVATE -Wall)

add_subdirectory(src)

target_include_directories(MyTinyTown PRIVATE "src/"
        "common"
        "render"
        "lib"
        "lib/ImGuiFileDialog"
        "lib/imgui"
        )
target_link_libraries(MyTinyTown PRIVATE glfw OpenGL::GL glm glad tinyobjloader)

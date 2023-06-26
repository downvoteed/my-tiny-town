target_sources(MyTinyTown PRIVATE 
"textures/textures.cc"
"camera/camera.cc"
"utils/objloader.cc"
#"renderer/renderer.cc"
)

add_subdirectory("renderer")
add_subdirectory("ui")
add_subdirectory("models")

target_include_directories(MyTinyTown PRIVATE
"utils"
"ui"
"textures"
"renderer"
"models"
"camera"
)
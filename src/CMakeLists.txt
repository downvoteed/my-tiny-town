target_sources(MyTinyTown PRIVATE 
"ui/application.cc"
#"camera/camera.cc"
#"renderer/renderer.cc"
#"textures/textures.cc"
)

target_include_directories(MyTinyTown PRIVATE
"utils"
"ui"
"textures"
"renderer"
"models"
"camera"
)
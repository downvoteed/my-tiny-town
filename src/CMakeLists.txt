target_sources(MyTinyTown PRIVATE 
"ui/application.cc"
"ui/imgui-layer.cc"
"ui/windows/demo-window.cc"
"renderer/vertex-buffer.cc"
"renderer/shader.cc"
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
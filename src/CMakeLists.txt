target_sources(MyTinyTown PRIVATE 
"ui/application.cc"
"ui/imgui-layer.cc"
"ui/windows/demo-window.cc"
"renderer/vertex-buffer.cc"
"renderer/shader.cc"
"textures/textures.cc"
"renderer/index-buffer.cc"
"renderer/scene.cc"
"models/grass-plane-model.cc"
"renderer/vertex-buffer-layout.cc"
#"camera/camera.cc"
#"renderer/renderer.cc"
)

target_include_directories(MyTinyTown PRIVATE
"utils"
"ui"
"textures"
"renderer"
"models"
"camera"
)
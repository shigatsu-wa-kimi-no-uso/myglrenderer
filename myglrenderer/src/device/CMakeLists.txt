
add_library(device STATIC 
"model/material/Texture.cpp"
"model/mesh/Mesh.cpp" "model/Model.cpp" "shader/Shader.cpp"
"model/mesh/CommonMesh.cpp"   "camera/Camera.cpp"  "model/mesh/CommonMeshEx.cpp" )
target_link_libraries(device PRIVATE common)


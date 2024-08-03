#include "common/global.h"
#include "common/utility.h"
#include <iostream>
#include "device/model/Model.h"
#include "window/Window.h"
#include "device/shader/Shader.h"
#include "loader/ShaderLoader.h"
#include "device/model/mesh/CommonMesh.h"
#include "device/model/mesh/Mesh.h"
#include "loader/ModelLoader.h"
#include "renderer/Renderer.h"


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;


const char* vsSrcFilePath = "C:/Users/Administrator/Documents/Visual Studio 2022/Projects/myglrenderer/myglrenderer/res/shaders/test.vert";

const char* fsSrcFilePath = "C:/Users/Administrator/Documents/Visual Studio 2022/Projects/myglrenderer/myglrenderer/res/shaders/test.frag";

const char* wall = "C:/Users/Administrator/Documents/Visual Studio 2022/Projects/myglrenderer/myglrenderer/res/textures/wall.jpg";
const char* container = "C:/Users/Administrator/Documents/Visual Studio 2022/Projects/myglrenderer/myglrenderer/res/textures/container.jpg";
const char* awesomeface = "C:/Users/Administrator/Documents/Visual Studio 2022/Projects/myglrenderer/myglrenderer/res/textures/awesomeface.png";


Model getTriangle()
{
    float vertices[] = {
-0.5f, -0.5f, 0.0f,
 0.5f, -0.5f, 0.0f,
 0.0f,  0.5f, 0.0f
    };

    float texCoords[] = {
    0.0f, 0.0f, // 左下角
    1.0f, 0.0f, // 右下角
    0.5f, 1.0f // 上中
    };

    Model model;
    CommonMesh mesh;
    Vertex v[4];
    v[0].position = vec3(0.5, 0.5, 0);
    v[1].position = vec3(0.5, -0.5, 0);
    v[2].position = vec3(-0.5, -0.5, 0);
    v[3].position = vec3(-0.5, 0.5, 0);
    v[0].texCoords = vec2(1, 1);
    v[1].texCoords = vec2(1, 0);
    v[2].texCoords = vec2(0, 0);
    v[3].texCoords = vec2(0, 1);
    mesh.addVertexAttribute(v[0]);
    mesh.addVertexAttribute(v[1]);
    mesh.addVertexAttribute(v[2]);
    mesh.addVertexAttribute(v[3]);
    mesh.addTriangleIndex(0);
    mesh.addTriangleIndex(1);
    mesh.addTriangleIndex(3);

    mesh.addTriangleIndex(1);
    mesh.addTriangleIndex(2);
    mesh.addTriangleIndex(3);

    model.addMesh(make_shared<CommonMesh>(mesh));
    return model;
}


Model getCube()
{
    float vertices[] = {
       -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
       -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
       -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

       -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
       -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
       -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

       -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
       -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
       -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
       -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
       -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
       -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

       -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
       -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
       -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

       -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
       -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
       -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };
    Model model;
    CommonMesh mesh;
    Vertex v[36];
    for (size_t i = 0; i < 36; ++i) {
        v[i].position = vec3(vertices[i * 5], vertices[i * 5 + 1], vertices[i * 5 + 2]);
        v[i].texCoords = vec2(vertices[i * 5 + 3], vertices[i * 5 + 4]);
        mesh.addVertexAttribute(v[i]);
        mesh.addTriangleIndex(i);
    }
    model.addMesh(make_shared<CommonMesh>(mesh));
    return model;
}


int main()
{

    bool a = initGLFW();

    WindowConfig wconfig;
    wconfig.glVerMajor = 4;
    wconfig.glVerMinor = 3;
    wconfig.szTitle = "Test";
    wconfig.hideCursor = false;
    wconfig.msaaSampleCnt = 4;
    wconfig.width = 800;
    wconfig.height = 600;
    wconfig.vpWidth = 800;
    wconfig.vpHeight = 600;
    wconfig.vpx = 0;
    wconfig.vpy = 0;
    wconfig.vsync = false;

    Renderer renderer;
    renderer.createWindow(wconfig);
    const char* nanoPath = "C:/Users/Administrator/Documents/Visual Studio 2022/Projects/myglrenderer/myglrenderer/res/nanosuit/nanosuit.obj";
    const char* nahidaPath = "C:/Users/Administrator/Documents/Visual Studio 2022/Projects/myglrenderer/myglrenderer/res/nahida/nahida.obj";
    ModelLoader modelLoader;
    Model nahida;
    modelLoader.loadModel(nahidaPath, nahida,make_shared<CommonMeshEx>());
    char* pVertCode = ShaderLoader::loadCode(vsSrcFilePath);
    char* pFragCode = ShaderLoader::loadCode(fsSrcFilePath);
   // Shader s = renderer.createShader( pVertCode, pFragCode);
    Image image, image2;
    modelLoader.loadImageFromFile(container, image);
    modelLoader.loadImageFromFile(awesomeface, image2);
    Model m = getCube();

    uint contextId = renderer.createContext<RenderContext>();
    renderer.loadModel(contextId, m);
    renderer.loadShader(contextId, pVertCode, pFragCode);
    
    shared_ptr<mat4> pModeling2 = make_shared<mat4>(1);
    *pModeling2 = translate(*pModeling2, vec3(0.0f, -1.0f, -2.0f));
  
    uint currContextId;
    for (const shared_ptr<Mesh>& mesh : nahida.getMeshes()) {
        currContextId = renderer.createContext<RenderContext>();
        renderer.loadMesh(currContextId, mesh);
        renderer.loadShader(currContextId, contextId);
        shared_ptr<RenderContext> p = renderer.getContext<RenderContext>(currContextId);
        p->pModeling = pModeling2;
        p->textureVarNamePolicy = [](TextureType type, uint index)->string {
            return "texture" + to_string(index + 1);
        };
        renderer.bindShaderUniforms(currContextId);
    }



    //renderer.loadModel(contextId2, nahida);

    shared_ptr<RenderContext> c = renderer.getContext<RenderContext>(contextId);
    c->textures.push_back(renderer.loadTexture(image));
    c->textures.push_back(renderer.loadTexture(image2,1));
    c->textureVarNamePolicy = [](TextureType type, uint index) -> string {
        return "texture" + to_string(index + 1);
        };

    shared_ptr<mat4> pModeling1 = make_shared<mat4>(1);
    *pModeling1 = translate(*pModeling1, vec3(2.0f, 5.0f, -15.0f));
    c->pModeling = pModeling1;
    c->bindShaderUniforms();


   

    CameraConfig cameraCfg;
    cameraCfg.cameraPos = vec3(0, 0, 0);
    cameraCfg.worldUp = vec3(0, 1, 0);
    cameraCfg.negZAxis = vec3(0, 0, -1);
    cameraCfg.yaw = -90.0f;
    cameraCfg.pitch = 0;
    cameraCfg.width = 800;
    cameraCfg.height = 600;
    cameraCfg.near = 0.1;
    cameraCfg.fov = 45.0f;
    cameraCfg.far = 100;
    RenderContext::camera.setCameraConfig(cameraCfg);

    c->texMixRatio = 0.2;
   // for (int i = 1; i < 10; i++) {
     //   renderer.createContext(*renderer.getContext<RenderContext>(contextId));
    //}

    renderer.render();
}


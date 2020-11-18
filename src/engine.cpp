



#include "engine.h"



Engine::Engine(int width, int height) : _width(width), _height(height), _drawfill(true)
        , _activecamera(0), _camera(nullptr)
        , _shader{std::make_unique<Shader>("../shaders/phong_vs.glsl", "../shaders/phong_fs.glsl")}
        , _colorShader{std::make_unique<Shader>("../shaders/color_vs.glsl", "../shaders/color_fs.glsl")}
        , _lightShader{std::make_unique<Shader>("../shaders/color_vs.glsl", "../shaders/color_fs.glsl")}
        , _drawLights{false}
        , screen_shader{std::make_unique<Shader>("../shaders/screen_vs.glsl", "../shaders/hdr_fs.glsl")}
        , frame_buffer{std::make_unique<FrameBuffer>(_width,_height,1)}
        , screen_quad{std::make_shared<ScreenQuad>(-1.f, 1.f, 2.f, 2.f)}
        , m_depth_shader{std::make_unique<Shader>("../shaders/depth_vs.glsl", "../shaders/depth_fs.glsl")}
        , m_transparency_shader(std::make_unique<Shader>("../shaders/phong_vs.glsl", "../shaders/transparency_fs.glsl"))
        , m_blend_shader(std::make_unique<Shader>("../shaders/screen_vs.glsl", "../shaders/screen_OIT_fs.glsl"))
        , m_transparency_buffer(std::make_unique<FrameBuffer>(_width,_height,1))
        , m_lights_manager(std::make_shared<LightsManager>())
        , m_asset_manager(std::make_shared<AssetManager>())
{

    //TODO : enable cull facing only for closed shapes
    glViewport(0, 0, width, height);

    //m_lightsManager.addPointLight(glm::vec3(0, 2, -6));


    /*auto sphere1 = std::make_shared<Sphere>();
    std::shared_ptr<Material> matsphere1 = std::make_shared<Material>();
    matsphere1->setDiffuseVal(glm::vec3(1,0,0));
    matsphere1->setAlpha(0.5);
    sphere1->setMaterial(matsphere1);
    addToTransparentModels(sphere1);

    auto sphere2 = std::make_shared<Sphere>();
    std::shared_ptr<Material> matsphere2 = std::make_shared<Material>();
    matsphere2->setDiffuseVal(glm::vec3(1,1,0));
    matsphere2->setAlpha(0.5);
    sphere2->setMaterial(matsphere2);
    addToTransparentModels(sphere2);

    auto sphere3 = std::make_shared<Sphere>();
    std::shared_ptr<Material> matsphere3 = std::make_shared<Material>();
    matsphere3->setDiffuseVal(glm::vec3(0,0,1));
    matsphere3->setAlpha(0.5);
    sphere3->setMaterial(matsphere3);
    addToTransparentModels(sphere3);*/

    /*auto sphere1 = std::make_shared<Sphere>();
    std::shared_ptr<Material> matsphere1 = std::make_shared<Material>();
    matsphere1->addDiffuseMap(std::make_shared<Texture>("../textures/1/wood_parket_pack1_basecolor.jpg",Texture::TextureType::DIFFUSE));
    sphere1->setMaterial(matsphere1);
    addToOpaqueModels(sphere1);
    auto sphere2 = std::make_shared<Sphere>();
    std::shared_ptr<Material> matsphere2 = std::make_shared<Material>();
    matsphere2->addDiffuseMap(std::make_shared<Texture>("../textures/2/wood_parket_pack1_2_basecolor.jpg",Texture::TextureType::DIFFUSE));
    sphere2->setMaterial(matsphere2);
    addToOpaqueModels(sphere2);
    auto sphere3 = std::make_shared<Sphere>();
    std::shared_ptr<Material> matsphere3 = std::make_shared<Material>();
    matsphere3->addDiffuseMap(std::make_shared<Texture>("../textures/5/wood_parket_pack1_5_basecolor.jpg",Texture::TextureType::DIFFUSE));
    sphere3->setMaterial(matsphere3);
    addToOpaqueModels(sphere3);

    auto sphere4 = std::make_shared<Sphere>();
    std::shared_ptr<Material> matsphere4 = std::make_shared<Material>();
    matsphere4->setSpecularVal(glm::vec3(0.5));
    matsphere4->setShininess(5);
    matsphere4->addDiffuseMap(std::make_shared<Texture>("../textures/iron.png",Texture::TextureType::DIFFUSE));
    sphere4->setMaterial(matsphere4);
    addToOpaqueModels(sphere4);
    auto sphere5 = std::make_shared<Sphere>();
    std::shared_ptr<Material> matsphere5 = std::make_shared<Material>();
    matsphere5->setShininess(5);
    matsphere5->addDiffuseMap(std::make_shared<Texture>("../textures/marble.png",Texture::TextureType::DIFFUSE));
    sphere5->setMaterial(matsphere5);
    addToOpaqueModels(sphere5);
    auto sphere6 = std::make_shared<Sphere>();
    std::shared_ptr<Material> matsphere6 = std::make_shared<Material>();
    matsphere6->setShininess(5);
    matsphere6->addDiffuseMap(std::make_shared<Texture>("../textures/gold.png",Texture::TextureType::DIFFUSE));
    sphere6->setMaterial(matsphere6);
    addToOpaqueModels(sphere6);*/



    /*auto church = std::make_shared<AssimpModel>("../objects/source/origins.fbx");
    church->setScale(glm::vec3(0.01));
    std::shared_ptr<Material> matChurch = std::make_shared<Material>();
    matChurch->addDiffuseMap(std::make_shared<Texture>("../objects/textures/material_baseColor.jpeg",Texture::TextureType::DIFFUSE));
    church->setMaterial(matChurch);
    m_opaque_models.emplace_back(church);
    m_models.emplace_back(church);
    m_interfaces.emplace_back([church]()->ModelInterface*
                              {
                                  return new ModelInterface(church);
                              });*/


    _cameraselector.emplace_back([]()->Camera*{return new EulerCamera(glm::vec3(0.f, 0.f, 3.f));} );
    _cameraselector.emplace_back([]()->Camera*{return new TrackballCamera(glm::vec3(0.f, 0.f, 3.f),glm::vec3(0.f, 1.f, 0.f),glm::vec3(0.f, 0.f, 0.f));} );

    _camera.reset(_cameraselector[_activecamera]());

    _camera->setviewport(glm::vec4(0.f, 0.f, _width, _height));
    _view = _camera->viewmatrix();

    _projection = glm::perspective(_camera->zoom(), float(_width) / _height, 0.1f, 100.0f);

    frame_buffer->addColorTexture();
    frame_buffer->addDepthStencilBuffer();
    frame_buffer->drawBuffers();

    m_transparency_buffer->addColorTexture();
    m_transparency_buffer->addColorTexture();
    m_transparency_buffer->addDepthStencilBuffer();
    m_transparency_buffer->drawBuffers();
    m_revealageTex = std::make_shared<Texture>(m_transparency_buffer->textures()[1],Texture::TextureType::DIFFUSE);
    m_accumTex = std::make_shared<Texture>(m_transparency_buffer->textures()[0],Texture::TextureType::DIFFUSE);
    m_hdrTex = std::make_shared<Texture>(frame_buffer->textures()[0],Texture::TextureType::DIFFUSE);
}




Engine::~Engine()
= default;

void Engine::resize(int width, int height)
{
   _width = width;
   _height = height;
    _camera->setviewport(glm::vec4(0.f, 0.f, _width, _height));
    _projection = glm::perspective(_camera->zoom(), float(_width) / _height, 0.1f, 100.0f);
}

void Engine::draw()
{
    if(m_scene_has_changed) {
        if (m_waiting_demo) {
            m_demo_lambda();
            m_waiting_demo = false;
        }
        m_lights_manager->createWaitingLights();
        m_lights_manager->destroyWaitingLights();
        m_asset_manager->createWaitingAssets();
        m_asset_manager->destroyWaitingAssets();

        //Render ShadowMaps
        m_depth_shader->use();
        m_lights_manager->renderShadowMaps(*m_depth_shader, _width, _height, glm::vec3{0.f},
                                           m_asset_manager->getAssets());
        m_scene_has_changed=false;
    }

    //Rendering from Camera

    frame_buffer->use();
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT |  GL_DEPTH_BUFFER_BIT);
    _view = _camera->viewmatrix();
    glPolygonMode(GL_FRONT_AND_BACK,_drawfill ? GL_FILL : GL_LINE);

    _colorShader->use();
    _colorShader->setMat4("view",_view);
    _colorShader->setMat4("projection",_projection);
    _colorShader->setVec3("color", glm::vec3(0.f, 1.f, 0.f));

    if(_drawLights) {
        _lightShader->use();
        _lightShader->setMat4("view", _view);
        _lightShader->setMat4("projection", _projection);
        _lightShader->setVec3("color", glm::vec3(1.f, 1.f, 1.f));
        m_lights_manager->renderLights(*_lightShader,*_colorShader, GL_TRIANGLES);
    }

    _shader->use();
    _shader->setVec3("viewPos", _camera->position());
    _shader->setMat4("view",_view);
    _shader->setMat4("projection",_projection);
    m_lights_manager->addLightsToShader(*_shader);
    m_asset_manager->renderOpaqueAssets(*_shader,*_colorShader,GL_TRIANGLES);
    frame_buffer->stop(_width,_height);

    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    m_transparency_buffer->use();
    m_transparency_shader->use();
    m_transparency_shader->setVec3("viewPos", _camera->position());
    m_transparency_shader->setMat4("view",_view);
    m_transparency_shader->setMat4("projection",_projection);
    m_lights_manager->addLightsToShader(*m_transparency_shader);
    glClear(GL_COLOR_BUFFER_BIT);
    const GLfloat ones[4] = {1,1,1,1};
    const GLfloat zeros[4] = {0,0,0,0};

    glClearBufferfv(GL_COLOR, 0,zeros);
    glClearBufferfv(GL_COLOR, 1,ones);
    m_transparency_buffer->copyDepthBuffer(*frame_buffer);
    glDepthMask(GL_FALSE);
    glEnable(GL_BLEND);
    glBlendFunci(0, GL_ONE, GL_ONE);
    glBlendFunci(1, GL_ZERO, GL_ONE_MINUS_SRC_ALPHA);
    m_asset_manager->renderTransparentAssets(*m_transparency_shader,*_colorShader,GL_TRIANGLES);
    m_transparency_buffer->stop(_width,_height);

    frame_buffer->use();
    m_blend_shader->use();
    m_blend_shader->setInt("accumTex",1);
    m_blend_shader->setInt("revealageTex",2);
    m_accumTex->bindToGL(*m_blend_shader,1);
    m_revealageTex->bindToGL(*m_blend_shader,2);
    glDepthMask(GL_TRUE);
    glBlendFunc(GL_ONE_MINUS_SRC_ALPHA, GL_SRC_ALPHA);
    screen_quad->drawModel(*m_blend_shader,GL_TRIANGLES);
    frame_buffer->stop(_width,_height);


    glClear(GL_COLOR_BUFFER_BIT);
    glDisable(GL_BLEND);
    glDepthMask(GL_TRUE);
    glEnable(GL_DEPTH_TEST);
    screen_shader->use();
    screen_shader->setFloat("exposure",1.0);
    screen_shader->setInt("screenTexture",0);
    m_hdrTex->bindToGL(*screen_shader,0);
    screen_quad->drawModel(*screen_shader,GL_TRIANGLES);
}

void Engine::mouseclick(int button, float xpos, float ypos)
{
    _button = button;
    _mousex = xpos;
    _mousey = ypos;
    _camera->processmouseclick(_button, xpos, ypos);
}

void Engine::mousemove(float xpos, float ypos)
{
    _camera->processmousemovement(_button, xpos, ypos, true);
}

void Engine::keyboardmove(int key, double time)
{
    _camera->processkeyboard(Camera_Movement(key), time);
}

bool Engine::keyboard(unsigned char k)
{
    switch(k) {
        case 'p':
            _activecamera = (_activecamera+1)%2;
            _camera.reset(_cameraselector[_activecamera]());
            _camera->setviewport(glm::vec4(0.f, 0.f, _width, _height));
            return true;
        case 'l':{
            _drawLights = !_drawLights;
            return true;
        }
        default:
            return false;
    }
}

void Engine::toggledrawmode()
{
    _drawfill = !_drawfill;
}

void Engine::createNewSphere()
{
    m_asset_manager->addSphere();
}

void Engine::createNewIcoSphere()
{
    m_asset_manager->addIcoSphere();
}



void Engine::createImportedModel(const std::string &path)
{
    m_asset_manager->addAssimpFromFile(path);

}


void Engine::setShader(const std::string &name)
{
    if(name == "Phong")
        _shader = std::make_unique<Shader>("../shaders/phong_vs.glsl", "../shaders/phong_fs.glsl");
    else if(name == "Approximation Error")
        _shader = std::make_unique<Shader>("../shaders/error_vs.glsl", "../shaders/error_fs.glsl");
    else if(name == "Basic Texture")
        _shader = std::make_unique<Shader>("../shaders/texture_vs.glsl", "../shaders/texture_fs.glsl");
}

void Engine::createPointLight() {
    m_lights_manager->addPointLight();
}

void Engine::createDirLight() {
    m_lights_manager->addDirLight();
}

void Engine::createSpotLight() {
    m_lights_manager->addSpotLight();
}

void Engine::createDemo() {
    auto lm =m_lights_manager;
    auto am=m_asset_manager;
    m_demo_lambda=[lm,am]()->void {
        auto dir = std::make_shared<DirLight>();
        dir->setPosition(glm::vec3(0,40,0));
        dir->setName("dirlight");
        //lm->addSpotLight();
        lm->addDirLight(dir);
        //lm->addPointLight();


        auto quad = std::make_shared<ScreenQuad>(-10,-10,20,20);
        quad->setRotation(glm::vec3(90,180,0));
        quad->setTranslation(glm::vec3(0,-1,19.5));
        std::shared_ptr<Material> mat = std::make_shared<Material>();
        mat->setDiffuseVal(glm::vec3(1));
        quad->setMaterial(mat);
        quad->setName("quad");
        am->addAsset(quad);

        auto sphere = std::make_shared<Sphere>();
        /*std::shared_ptr<Material> matsphere = std::make_shared<Material>();
        matsphere->setDiffuseVal(glm::vec3(1));
        matsphere->setAlpha(0.5);
        sphere->setMaterial(matsphere);*/
        sphere->setName("sphere");
        //am->addAsset(sphere);

        /*auto sphere1 = std::make_shared<Sphere>();
        std::shared_ptr<Material> matsphere1 = std::make_shared<Material>();
        matsphere1->setDiffuseVal(glm::vec3(1,0,0));
        matsphere1->setAlpha(0.5);
        sphere1->setMaterial(matsphere1);
        sphere1->setName("Tsphere1");
        sphere1->setShaderType(Asset::ShaderType::TRANSPARENT);
        am->addAsset(sphere1);

        auto sphere2 = std::make_shared<Sphere>();
        std::shared_ptr<Material> matsphere2 = std::make_shared<Material>();
        matsphere2->setDiffuseVal(glm::vec3(1,1,0));
        matsphere2->setAlpha(0.5);
        sphere2->setMaterial(matsphere2);
        sphere2->setName("Tsphere2");
        sphere2->setShaderType(Asset::ShaderType::TRANSPARENT);
        am->addAsset(sphere2);

        auto sphere3 = std::make_shared<Sphere>();
        std::shared_ptr<Material> matsphere3 = std::make_shared<Material>();
        matsphere3->setDiffuseVal(glm::vec3(0,0,1));
        matsphere3->setAlpha(0.5);
        sphere3->setMaterial(matsphere3);
        sphere3->setName("Tsphere3");
        sphere3->setShaderType(Asset::ShaderType::TRANSPARENT);
        am->addAsset(sphere3);*/
    };
    m_waiting_demo=true;

}

void Engine::createMetaBall() {
    m_asset_manager->addMetaBall();
}



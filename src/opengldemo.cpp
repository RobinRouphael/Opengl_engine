


#include <src/geometry/b_spline2D.h>
#include "opengldemo.h"



OpenGLDemo::OpenGLDemo(int width, int height) : _width(width), _height(height), _drawfill(true)
        , _activecamera(0), _camera(nullptr)
        , _shader{std::make_unique<Shader>("../shaders/phong_vs.glsl", "../shaders/phong_fs.glsl")}
        , _colorShader{std::make_unique<Shader>("../shaders/color_vs.glsl", "../shaders/color_fs.glsl")}
        , _lightShader{std::make_unique<Shader>("../shaders/color_vs.glsl", "../shaders/color_fs.glsl")}
        , _selectedModel{-1}
        , _waitingModels{false}
        , _waitingToDestroyModel{false}
        , _modelConstructor{nullptr}
        , _drawLights{false}
{
    glEnable(GL_DEPTH_TEST);
    glViewport(0, 0, width, height);

    auto l = std::make_shared<PointLight>(glm::vec3(0, 0, -6));
    _lights.emplace_back(std::make_pair(l, new PointLightWidget(l)));

    auto l2 = std::make_shared<PointLight>(glm::vec3(4.5, 0, 4.5));
    _lights.emplace_back(std::make_pair(l2, new PointLightWidget(l2)));

    auto l3 = std::make_shared<PointLight>(glm::vec3(-4.5, 0, 4));
    _lights.emplace_back(std::make_pair(l3, new PointLightWidget(l3)));

    auto bspline2D = std::make_shared<BSpline2D>();
    _models.emplace_back(std::make_pair(bspline2D,nullptr));



    _cameraselector.push_back( []()->Camera*{return new EulerCamera(glm::vec3(0.f, 0.f, 3.f));} );
    _cameraselector.push_back( []()->Camera*{return new TrackballCamera(glm::vec3(0.f, 0.f, 3.f),glm::vec3(0.f, 1.f, 0.f),glm::vec3(0.f, 0.f, 0.f));} );

    _camera.reset(_cameraselector[_activecamera]());

    _camera->setviewport(glm::vec4(0.f, 0.f, _width, _height));
    _view = _camera->viewmatrix();

    _projection = glm::perspective(_camera->zoom(), float(_width) / _height, 0.1f, 100.0f);
}




OpenGLDemo::~OpenGLDemo()
{
}

void OpenGLDemo::resize(int width, int height)
{
   _width = width;
   _height = height;
    _camera->setviewport(glm::vec4(0.f, 0.f, _width, _height));
    _projection = glm::perspective(_camera->zoom(), float(_width) / _height, 0.1f, 100.0f);
}

void OpenGLDemo::draw()
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    _view = _camera->viewmatrix();

    _shader->use();
    _shader->setVec3("viewPos", _camera->position());
    _shader->setMat4("view",_view);
    _shader->setMat4("projection",_projection);

    _lightShader->use();
    _lightShader->setMat4("view",_view);
    _lightShader->setMat4("projection",_projection);
    _lightShader->setVec3("color", glm::vec3(1.f, 1.f, 1.f));

    _colorShader->use();
    _colorShader->setMat4("view",_view);
    _colorShader->setMat4("projection",_projection);
    _colorShader->setVec3("color", glm::vec3(0.f, 1.f, 0.f));


    if(_waitingModels){
        _waitingModels = false;
        createWaitingModels();
    }
    if(_waitingToDestroyModel){
        _waitingToDestroyModel=false;
        destroyWaitingModels();
    }

    glPolygonMode(GL_FRONT_AND_BACK,_drawfill ? GL_FILL : GL_LINE);
    for(auto i=0; i < _lights.size(); i++){
        _lights[i].first->addToShader(*_shader);
        if(_drawLights)
            _lights[i].first->drawLight(*_lightShader);
    }



    for(auto i =0; i < _models.size(); i++){
        _models[i].first->drawModel(*_shader);
        if(_selectedModel == i){
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            glLineWidth(1);
            glEnable( GL_POLYGON_OFFSET_LINE );
            glPolygonOffset( -1, -1 );
            _models[i].first->drawModel(*_colorShader);
            glDisable( GL_POLYGON_OFFSET_LINE );
            glPolygonMode(GL_FRONT_AND_BACK,_drawfill ? GL_FILL : GL_LINE);
        }
    }
    glDepthRange(0.0, 1.0);
    _shader->clearLights();
}

void OpenGLDemo::mouseclick(int button, float xpos, float ypos)
{
    _button = button;
    _mousex = xpos;
    _mousey = ypos;
    _camera->processmouseclick(_button, xpos, ypos);
}

void OpenGLDemo::mousemove(float xpos, float ypos)
{
    _camera->processmousemovement(_button, xpos, ypos, true);
}

void OpenGLDemo::keyboardmove(int key, double time)
{
    _camera->processkeyboard(Camera_Movement(key), time);
}

bool OpenGLDemo::keyboard(unsigned char k)
{
    switch(k) {
        case 'p':
            _activecamera = (_activecamera+1)%2;
            _camera.reset(_cameraselector[_activecamera]());
            _camera->setviewport(glm::vec4(0.f, 0.f, _width, _height));
            return true;
        case '+': {
            if(_models.size() != 0){
                _selectedModel = (_selectedModel + 1) % _models.size();
                return true;
            }

            return false;
        }
        case '-': {
            if(_models.size() != 0){
                _selectedModel = (_selectedModel - 1) % _models.size();
                return true;
            }

            return false;
        }
        case 'd': {
            if(_selectedModel != -1){
                _selectedModel = -1;
                return true;
            }
            return false;
        }
        case 'l':{
            _drawLights = !_drawLights;
            return true;
        }
        default:
            return false;
    }
}

ModelInterface *OpenGLDemo::getSelection()
{
    return _models[_selectedModel].second();
}

void OpenGLDemo::toggledrawmode()
{
    _drawfill = !_drawfill;
}

void OpenGLDemo::createNewSphere()
{
    _modelConstructor = []()->std::pair<std::shared_ptr<Model>,InterfaceConstructor>{
        auto sphere = std::make_shared<Sphere>();

        InterfaceConstructor sphereWidgetConstructor = [sphere]()->ModelInterface*
                {
            return new SphereWidget(sphere);
        };

        return std::make_pair(sphere,sphereWidgetConstructor);
    };
    _waitingModels = true;
}

void OpenGLDemo::createNewIcoSphere()
{
    _modelConstructor = []()->std::pair<std::shared_ptr<Model>,InterfaceConstructor>{
        auto sphere = std::make_shared<Icosphere>();

        InterfaceConstructor sphereWidgetConstructor = [sphere]()->ModelInterface*
                {
            return new IcoSphereWidget(sphere);
        };

        return std::make_pair(sphere,sphereWidgetConstructor);
    };
    _waitingModels = true;
}



void OpenGLDemo::createImportedModel(const std::string &path)
{
    _modelConstructor = [path]()->std::pair<std::shared_ptr<Model>,InterfaceConstructor>{
        auto  model = std::make_shared<AssimpModel>(path);
        InterfaceConstructor modelWidgetConstructor = [model]()->ModelInterface*
                {
            return new ImportedModelWidget(model);
        };
        return std::make_pair(model,modelWidgetConstructor);
    };
    _waitingModels = true;

}

void OpenGLDemo::createWaitingModels()
{
    _models.emplace_back(_modelConstructor());
}

void OpenGLDemo::destroySelected()
{
    _waitingToDestroyModel = true;
}

void OpenGLDemo::destroyWaitingModels()
{
    _models.erase(_models.begin() + _selectedModel);
    _selectedModel = -1;
}

void OpenGLDemo::setShader(const std::string &name)
{
    if(name == "Phong")
        _shader = std::make_unique<Shader>("../shaders/phong_vs.glsl", "../shaders/phong_fs.glsl");
    else if(name == "Approximation Error")
        _shader = std::make_unique<Shader>("../shaders/error_vs.glsl", "../shaders/error_fs.glsl");
    else if(name == "Basic Texture")
        _shader = std::make_unique<Shader>("../shaders/texture_vs.glsl", "../shaders/texture_fs.glsl");
}

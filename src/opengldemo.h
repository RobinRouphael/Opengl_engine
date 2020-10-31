#ifndef SCENE_H
#define SCENE_H


#include "src/core/camera.h"
#include "core/model.h"
#include "modelWidget/modelInterface.h"
#include "src/modelWidget/sphereWidget.h"
#include "src/models/sphere.h"
#include <functional>
#include <QtWidgets/QWidget>
#include <src/core/light.h>
#include <src/modelWidget/lightInterface.h>
#include <src/models/assimpmodel.h>
#include <src/models/icosphere.h>
#include <src/modelWidget/icoSphereWidget.h>
#include <src/modelWidget/importedModelWidget.h>
#include "src/models/bSplineSurface.h"
#include <src/models/cube.h>
#include <src/core/frameBuffer.h>
#include <src/models/quad.h>


class OpenGLDemo {
/**
 * Engine demo
 */
public:
    explicit OpenGLDemo(int width, int height);
    ~OpenGLDemo();

    void resize(int width, int height);
    void draw();

    void mouseclick(int button, float xpos, float ypos);
    void mousemove(float xpos, float ypos);
    void keyboardmove(int key, double time);
    bool keyboard(unsigned char k);
    /**
     * Get Widget of selected model
     * @return
     */
    ModelInterface *getSelection();
    /**
     * Create new UV sphere
     */
    void createNewSphere();
    /**
     * Create new IcoSphere
     */
    void createNewIcoSphere();
    /**
     * Create Imported Model
     * @param path to file
     */
    void createImportedModel(const std::string &path);
    /**
     * Delete selected model
     */
    void destroySelected();
    /**
     * Set main shader to draw models
     * @param name
     */
    void setShader(const std::string &name);

    void toggledrawmode();




private:
    /**
     * Create models through main thread
     */
    void createWaitingModels();
    /**
     * Delete models through main thread
     */
    void destroyWaitingModels();

protected:
    // Width and heigth of the viewport
    int _width;
    int _height;

private:
    // Rendering mode (true is filled, false is wireframed
    bool _drawfill;
    bool _drawLights;

    using InterfaceConstructor = std::function<ModelInterface*()>;

    //Models and Model Widgets constructor
    std::function<std::pair<std::shared_ptr<Model>,InterfaceConstructor>()> _modelConstructor;
    std::function<std::pair<std::shared_ptr<Light>,LightInterface*>()> _lightConstructor;

    //Lights and Lights Widget constructor
    std::vector<std::pair<std::shared_ptr<Model>,InterfaceConstructor>> _models;
    std::vector<std::pair<std::shared_ptr<Light>,LightInterface*>> _lights;


    bool _waitingModels;
    bool _waitingToDestroyModel;
    int _selectedModel;
    int _selectedLight;

    // Shader program for rendering
    std::unique_ptr<Shader> _shader;
    std::unique_ptr<Shader> _colorShader;
    std::unique_ptr<Shader> _lightShader;
    std::unique_ptr<Shader> screen_shader;
    std::unique_ptr<FrameBuffer> frame_buffer;
    std::shared_ptr<ScreenQuad> screen_quad;

    // for mouse management
    int _button; // 0 --> left. 1 --> right. 2 --> middle. 3 --> other
    float _mousex{0};
    float _mousey{0};

    // Camera
    using CameraSelector=std::function<Camera*()>;
    std::vector<CameraSelector> _cameraselector;
    unsigned int _activecamera;

    std::unique_ptr<Camera> _camera;

    // matrices
    glm::mat4 _view;
    glm::mat4 _projection;
};


#endif // SCENE_H

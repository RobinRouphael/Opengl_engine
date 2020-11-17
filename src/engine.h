#ifndef SCENE_H
#define SCENE_H


#include "src/core/camera.h"
#include "core/asset.h"
#include "widgets/modelInterface.h"
#include "src/widgets/sphereWidget.h"
#include "src/models/sphere.h"
#include <functional>
#include <QtWidgets/QWidget>
#include "src/lights/light.h"
#include "src/lights/dirLight.h"
#include "src/lights/pointLight.h"
#include "src/lights/spotLight.h"
#include <src/widgets/lightInterface.h>
#include <src/models/assimpmodel.h>
#include <src/models/icosphere.h>
#include <src/widgets/icoSphereWidget.h>
#include <src/widgets/importedModelWidget.h>
#include "src/models/bSplineSurface.h"
#include <src/models/cube.h>
#include <src/core/frameBuffer.h>
#include <src/models/quad.h>
#include <src/core/lightsManager.h>
#include <src/core/assetManager.h>


class Engine {
/**
 * Engine demo
 */
public:
    explicit Engine(int width, int height);
    ~Engine();

    void resize(int width, int height);
    void draw();

    void mouseclick(int button, float xpos, float ypos);
    void mousemove(float xpos, float ypos);
    void keyboardmove(int key, double time);
    bool keyboard(unsigned char k);
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
     * Set main shader to draw models
     * @param name
     */
    void setShader(const std::string &name);

    void createPointLight();
    void createDirLight();
    void createSpotLight();
    void createDemo();
    void createMetaBall();
    void setSceneHasChanged(bool t_sceneChanged){m_scene_has_changed=t_sceneChanged;}

    void toggledrawmode();


    const std::shared_ptr<LightsManager>  &getLightManager(){return m_lights_manager;}
    const std::shared_ptr<AssetManager>   &getAssetManager(){return m_asset_manager;}


protected:
    // Width and heigth of the viewport
    int _width;
    int _height;

private:
    // Rendering mode (true is filled, false is wireframed
    bool _drawfill;
    bool _drawLights;

    std::shared_ptr<LightsManager> m_lights_manager;
    std::shared_ptr<AssetManager> m_asset_manager;
    std::function<void()> m_demo_lambda;
    bool m_waiting_demo{false};
    bool m_scene_has_changed{false};
    // Shader program for rendering
    std::unique_ptr<Shader> _shader;
    std::unique_ptr<Shader> _colorShader;
    std::unique_ptr<Shader> _lightShader;
    std::unique_ptr<Shader> m_depth_shader;
    std::unique_ptr<Shader> screen_shader;
    std::unique_ptr<Shader> m_transparency_shader;
    std::unique_ptr<Shader> m_blend_shader;
    std::unique_ptr<FrameBuffer> frame_buffer;
    std::unique_ptr<FrameBuffer> m_transparency_buffer;
    std::shared_ptr<ScreenQuad> screen_quad;
    std::shared_ptr<Texture> m_revealageTex;
    std::shared_ptr<Texture> m_accumTex;
    std::shared_ptr<Texture> m_hdrTex;

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

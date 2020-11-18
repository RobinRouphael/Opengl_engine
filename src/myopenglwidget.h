#ifndef MYOPENGLWIDGET_H
#define MYOPENGLWIDGET_H
#include "engine.h"
#include <QOpenGLWidget>
#include <QOpenGLFunctions_4_1_Core>
#include <QKeyEvent>
#include <memory>
#include <src/core/assetManager.h>


class MyOpenGLWidget : public QOpenGLWidget, protected QOpenGLFunctions_4_1_Core {
    Q_OBJECT
    /**
     * Main OpenGL Widget for rendering
     */
public:
    /**
     * Constructor
     * @param parent
     */
    explicit MyOpenGLWidget(QWidget *parent = 0);
    /**
     * Destructor
     */
    ~MyOpenGLWidget();

    // size hints for the widget
    QSize minimumSizeHint() const override;
    QSize sizeHint() const override;
    /**
     * Create a new sphere
     */
    void createNewSphere();
    /**
     * Create a new icoSphere
     */
    void createNewIcoSphere();
    /**
     * Create Imported Model
     */
    void createImportedModel(const std::string &path);
    /**
     * Set shader for Models
     * @param name
     */
    void setShader(QString name);

    void createNewPointLight();
    void createNewDirLight();
    void createNewSpotLight();
    void createDemo();
    void createMetaBall();
    const std::shared_ptr<LightsManager>  &getLightManager(){return m_engine->getLightManager();}
    const std::shared_ptr<AssetManager>   &getAssetManager(){return m_engine->getAssetManager();}



signals:
    /**
     * Selected Model has changed
     * @param properties panel for the selected Model
     */
    void objectSelectionChanged(ModelInterface *panel);
    /**
     * No Model is currently selected
     */
    void noObjectSelected();
    void glInitialized();
    void sceneTreeChanged();

public slots:
    void cleanup();
    /**
     * Properties of the selected model have changed
     */
    void modelPropertiesChanged();
    /**
     * The selected model must be deleted
     */
    void selectedIsToBeDestroyed();

protected:
    // OpenGL management
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int width, int height) override;

    // Event maagement
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

    void keyPressEvent(QKeyEvent *event) override;

private :
    std::unique_ptr<Engine> m_engine;
    bool m_sceneTreeHasChanged{false};

    // for event management
    std::int64_t _lastime;
};

#endif // MYOPENGLWIDGET_H

#include "myopenglwidget.h"

#include <QMessageBox>
#include <QApplication>
#include <QDateTime>

#include <iostream>
#include <stdexcept>


MyOpenGLWidget::MyOpenGLWidget(QWidget *parent) :
        QOpenGLWidget(parent)/*, QOpenGLFunctions_4_1_Core()*/,
        m_engine(nullptr),
        _lastime(0)
{

}

MyOpenGLWidget::~MyOpenGLWidget()
{

}

QSize MyOpenGLWidget::minimumSizeHint() const
{
    return QSize(50, 50);
}

QSize MyOpenGLWidget::sizeHint() const
{
    return QSize(512, 512);
}

void MyOpenGLWidget::cleanup()
{
    m_engine.reset(nullptr);
}

void MyOpenGLWidget::initializeGL()
{
    connect(context(), &QOpenGLContext::aboutToBeDestroyed, this, &MyOpenGLWidget::cleanup);

    if (!initializeOpenGLFunctions()) {
        QMessageBox::critical(this, "OpenGL initialization error", "MyOpenGLWidget::initializeGL() : Unable to initialize OpenGL functions");
        exit(1);
    }
    // Initialize OpenGL and all OpenGL dependent stuff below
    m_engine.reset(new Engine(width(), height()));
    emit glInitialized();
}

void MyOpenGLWidget::paintGL()
{
    FrameBuffer::setDefaultFbo(defaultFramebufferObject());
    std::int64_t starttime = QDateTime::currentMSecsSinceEpoch();
    m_engine->draw();
    glFinish();
    std::int64_t endtime = QDateTime::currentMSecsSinceEpoch();
    _lastime = endtime-starttime;
    if(m_sceneTreeHasChanged){
        emit sceneTreeChanged();
        m_sceneTreeHasChanged=false;
    }
}

void MyOpenGLWidget::resizeGL(int width, int height)
{
    m_engine->resize(width, height);
}

void MyOpenGLWidget::mousePressEvent(QMouseEvent *event)
{
    // buttons are 0(left), 1(right) to 2(middle)
    int b;
    Qt::MouseButton button=event->button();
    if (button & Qt::LeftButton) {
        if ((event->modifiers() & Qt::ControlModifier))
            b = 2;
        else
            b = 0;
    } else if (button & Qt::RightButton)
        b = 1;
    else if (button & Qt::MiddleButton)
        b = 2;
    else
        b=3;
    m_engine->mouseclick(b, event->x(), event->y());
    _lastime = QDateTime::currentMSecsSinceEpoch();
    setFocus();
}

void MyOpenGLWidget::mouseMoveEvent(QMouseEvent *event)
{
    m_engine->mousemove(event->x(), event->y());
    update();
}

void MyOpenGLWidget::keyPressEvent(QKeyEvent *event)
{
    switch(event->key()) {
        // Demo keys
        case Qt::Key_0:
        case Qt::Key_1:
        case Qt::Key_2:
        case Qt::Key_3:
        case Qt::Key_4:
        case Qt::Key_5:
        case Qt::Key_6:
        case Qt::Key_7:
        case Qt::Key_8:
        case Qt::Key_9:
        case Qt::Key_Left:
        case Qt::Key_Up:
        case Qt::Key_Right:
        case Qt::Key_Down:
            m_engine->keyboardmove(event->key() - Qt::Key_Left, 1. / 100/*double(_lastime)/10.*/);
            update();
        break;
        case Qt::Key_Escape:
            if(m_engine->keyboard('d'))
                emit noObjectSelected();
            //update();
            break;
        // Wireframe key
        case Qt::Key_W:
            m_engine->toggledrawmode();
            update();
        break;
        // Other keys are transmitted to the scene
        default :
            if (m_engine->keyboard(event->text().toLower().toStdString()[0]))
                update();
        break;
    }
}

void MyOpenGLWidget::createNewSphere()
{
    m_engine->setSceneHasChanged(true);
    m_engine->createNewSphere();
    m_sceneTreeHasChanged=true;
    update();
}

void MyOpenGLWidget::createNewIcoSphere()
{
    m_engine->setSceneHasChanged(true);
    m_engine->createNewIcoSphere();
    m_sceneTreeHasChanged=true;
    update();

}

void MyOpenGLWidget::modelPropertiesChanged()
{
    m_engine->setSceneHasChanged(true);
    update();
}

void MyOpenGLWidget::createImportedModel(const std::string &path)
{
    m_engine->setSceneHasChanged(true);
    m_engine->createImportedModel(path);
    m_sceneTreeHasChanged=true;
    update();
}

void MyOpenGLWidget::selectedIsToBeDestroyed()
{
    m_engine->setSceneHasChanged(true);
    m_sceneTreeHasChanged=true;
    update();
}

void MyOpenGLWidget::setShader(QString name)
{
    m_engine->setSceneHasChanged(true);
    m_engine->setShader(name.toStdString());
    update();
}

void MyOpenGLWidget::createNewPointLight() {
    m_engine->setSceneHasChanged(true);
    m_engine->createPointLight();
    m_sceneTreeHasChanged=true;
    update();
}

void MyOpenGLWidget::createNewDirLight() {
    m_engine->setSceneHasChanged(true);
    m_engine->createDirLight();
    m_sceneTreeHasChanged=true;
    update();
}

void MyOpenGLWidget::createNewSpotLight() {
    m_engine->setSceneHasChanged(true);
    m_engine->createSpotLight();
    m_sceneTreeHasChanged=true;
    update();
}

void MyOpenGLWidget::createMetaBall() {
    m_engine->setSceneHasChanged(true);
    m_engine->createMetaBall();
    m_sceneTreeHasChanged=true;
    update();
}

void MyOpenGLWidget::createDemo() {
    m_engine->setSceneHasChanged(true);
    m_engine->createDemo();
    m_sceneTreeHasChanged=true;
    update();
}





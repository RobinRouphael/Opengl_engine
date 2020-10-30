#include "myopenglwidget.h"

#include <QMessageBox>
#include <QApplication>
#include <QDateTime>

#include <iostream>
#include <stdexcept>


MyOpenGLWidget::MyOpenGLWidget(QWidget *parent) :
    QOpenGLWidget(parent)/*, QOpenGLFunctions_4_1_Core()*/,
    _engine(nullptr),
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
    _engine.reset(nullptr);
}

void MyOpenGLWidget::initializeGL()
{
    connect(context(), &QOpenGLContext::aboutToBeDestroyed, this, &MyOpenGLWidget::cleanup);

    if (!initializeOpenGLFunctions()) {
        QMessageBox::critical(this, "OpenGL initialization error", "MyOpenGLWidget::initializeGL() : Unable to initialize OpenGL functions");
        exit(1);
    }
    // Initialize OpenGL and all OpenGL dependent stuff below
    _engine.reset(new OpenGLDemo(width(), height()));
}

void MyOpenGLWidget::paintGL()
{
    FrameBuffer::setDefaultFbo(defaultFramebufferObject());
    std::int64_t starttime = QDateTime::currentMSecsSinceEpoch();
    _engine->draw();
    glFinish();
    std::int64_t endtime = QDateTime::currentMSecsSinceEpoch();
    _lastime = endtime-starttime;
}

void MyOpenGLWidget::resizeGL(int width, int height)
{
    _engine->resize(width, height);
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
    _engine->mouseclick(b, event->x(), event->y());
    _lastime = QDateTime::currentMSecsSinceEpoch();
    setFocus();
}

void MyOpenGLWidget::mouseMoveEvent(QMouseEvent *event)
{
    _engine->mousemove(event->x(), event->y());
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
            _engine->keyboardmove(event->key()-Qt::Key_Left, 1./100/*double(_lastime)/10.*/);
            update();
        break;
        case Qt::Key_Plus:
            if(_engine->keyboard('+'))
                emit objectSelectionChanged(_engine->getSelection());

            //update();
            break;
        case Qt::Key_Minus:
            if(_engine->keyboard('-'))
                emit objectSelectionChanged(_engine->getSelection());
            //update();
            break;
        case Qt::Key_Escape:
            if(_engine->keyboard('d'))
                emit noObjectSelected();
            //update();
            break;
        // Wireframe key
        case Qt::Key_W:
            _engine->toggledrawmode();
            update();
        break;
        // Other keys are transmitted to the scene
        default :
            if (_engine->keyboard(event->text().toLower().toStdString()[0]))
                update();
        break;
    }
}

void MyOpenGLWidget::createNewSphere()
{
    _engine->createNewSphere();
    update();
}

void MyOpenGLWidget::createNewIcoSphere()
{
    _engine->createNewIcoSphere();
    update();

}

void MyOpenGLWidget::modelPropertiesChanged()
{
    update();
}

void MyOpenGLWidget::createImportedModel(const std::string &path)
{
    _engine->createImportedModel(path);
    update();
}

void MyOpenGLWidget::selectedIsToBeDestroyed()
{
    emit noObjectSelected();
    _engine->destroySelected();
    //update();
}

void MyOpenGLWidget::setShader(QString name)
{
    _engine->setShader(name.toStdString());
    update();
}





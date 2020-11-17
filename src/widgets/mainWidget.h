//
// Created by robin on 13/11/2020.
//

#ifndef ENGINE_MAINWIDGET_H
#define ENGINE_MAINWIDGET_H


#include <QtWidgets/QWidget>
#include <QtWidgets/QVBoxLayout>
#include <memory>
#include <src/myopenglwidget.h>
#include "treeWidget.h"
#include "lightInterface.h"
#include "metaballWidget.h"
#include "modelInterface.h"

class MainWidget : public QWidget {
    Q_OBJECT
public:

    MainWidget(QWidget *parent);
    ~MainWidget() override =default;

    std::unique_ptr<MyOpenGLWidget>& getGLWidget(){return m_opengl_widget;}


private:
    void reconnectInterface();

private:
    std::unique_ptr<QHBoxLayout> m_main_layout;
    std::unique_ptr<QWidget> m_side_widget;
    std::unique_ptr<QVBoxLayout>m_side_layout;
    std::unique_ptr<TreeWidget> m_assets_tree;
    std::unique_ptr<ObjectInterface> m_model_settings;
    std::unique_ptr<MyOpenGLWidget> m_opengl_widget;

public slots:
    void on_treeSelectionChanged();
    void on_glInitialized();
    void on_updateSceneTree();
};


#endif //ENGINE_MAINWIDGET_H

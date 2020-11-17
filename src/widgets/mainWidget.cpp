//
// Created by robin on 13/11/2020.
//

#include "mainWidget.h"


MainWidget::MainWidget(QWidget *parent) :
        m_main_layout{std::make_unique<QHBoxLayout>()},

        m_side_layout{std::make_unique<QVBoxLayout>()},
        m_side_widget{std::make_unique<QWidget>()},
        m_opengl_widget{std::make_unique<MyOpenGLWidget>()},
        m_assets_tree{std::make_unique<TreeWidget>()},
        m_model_settings{nullptr}

{
    QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    sizePolicy.setHorizontalStretch(4);
    sizePolicy.setVerticalStretch(0);
    m_opengl_widget->setSizePolicy(sizePolicy);
    QSizePolicy sizePolicySide(QSizePolicy::Preferred, QSizePolicy::Preferred);
    sizePolicySide.setHorizontalStretch(2);
    sizePolicySide.setVerticalStretch(0);
    m_side_widget->setSizePolicy(sizePolicySide);


    m_side_layout->addWidget(m_assets_tree.get());
    m_side_widget->setLayout(m_side_layout.get());
    m_main_layout->addWidget(m_opengl_widget.get());
    m_main_layout->addWidget(m_side_widget.get());
    setLayout(m_main_layout.get());
    connect(m_opengl_widget.get(),SIGNAL(glInitialized()),this,SLOT(on_glInitialized()));
    connect(m_opengl_widget.get(),SIGNAL(sceneTreeChanged()),this,SLOT(on_updateSceneTree()));
}

void MainWidget::on_treeSelectionChanged() {
    auto index{m_assets_tree->selectionModel()->currentIndex()};
    auto name = index.data(Qt::DisplayRole).toString().toStdString();
    auto parentName = index.parent().data(Qt::DisplayRole).toString().toStdString();
    m_model_settings=nullptr;
    if(parentName == "Spheres"){
        m_model_settings = std::make_unique<SphereWidget>(m_opengl_widget->getAssetManager()->selectSphereFromName(name));
        m_side_layout->addWidget(m_model_settings.get());
        reconnectInterface();
        m_model_settings->propertiesHaveChanged();
        m_opengl_widget->setFocus();

    }
    else if(parentName == "IcoSpheres"){
        m_model_settings = std::make_unique<IcoSphereWidget>(m_opengl_widget->getAssetManager()->selectIcoSphereFromName(name));
        m_side_layout->addWidget(m_model_settings.get());
        reconnectInterface();
        m_model_settings->propertiesHaveChanged();
        m_opengl_widget->setFocus();

    }
    else if(parentName == "Custom"){
        m_model_settings = std::make_unique<ModelInterface>(m_opengl_widget->getAssetManager()->selectCustomFromName(name));
        m_side_layout->addWidget(m_model_settings.get());
        reconnectInterface();
        m_model_settings->propertiesHaveChanged();
        m_opengl_widget->setFocus();

    }
    else if(parentName == "MetaBalls"){
        m_model_settings = std::make_unique<MetaballWidget>(m_opengl_widget->getAssetManager()->selectMetaballFromName(name));
        m_side_layout->addWidget(m_model_settings.get());
        reconnectInterface();
        m_model_settings->propertiesHaveChanged();
        m_opengl_widget->setFocus();
    }
    else if(parentName == "Spot Lights")
    {
        m_model_settings = std::make_unique<SpotLightInterface>(m_opengl_widget->getLightManager()->selectSpotFromName(name));
        m_side_layout->addWidget(m_model_settings.get());
        reconnectInterface();
        m_model_settings->propertiesHaveChanged();
        m_opengl_widget->setFocus();
    }
    else if(parentName == "Dir Lights")
    {

        m_model_settings = std::make_unique<DirLightInterface>(m_opengl_widget->getLightManager()->selectDirFromName(name));
        m_side_layout->addWidget(m_model_settings.get());
        reconnectInterface();
        m_model_settings->propertiesHaveChanged();
        m_opengl_widget->setFocus();

    }
    else if(parentName == "Point Lights")
    {
        m_model_settings = std::make_unique<PointLightInterface>(
                m_opengl_widget->getLightManager()->selectPointFromName(name));
        m_side_layout->addWidget(m_model_settings.get());
        reconnectInterface();
        m_model_settings->propertiesHaveChanged();
        m_opengl_widget->setFocus();
    }


}
void MainWidget::on_glInitialized() {
    m_assets_tree->setupTree(m_opengl_widget->getLightManager(),m_opengl_widget->getAssetManager());
    connect(m_assets_tree->selectionModel(), &QItemSelectionModel::selectionChanged, this,
            &MainWidget::on_treeSelectionChanged);
}


void MainWidget::reconnectInterface()
{
    QObject::connect(m_model_settings.get(), &ObjectInterface::propertiesHaveChanged, m_opengl_widget.get(),
                     &MyOpenGLWidget::modelPropertiesChanged);
    QObject::connect(m_model_settings.get(), &ObjectInterface::objectIsToBeDestroyed, m_opengl_widget.get(), &MyOpenGLWidget::selectedIsToBeDestroyed);
}

void MainWidget::on_updateSceneTree() {
    m_assets_tree->setupTree(m_opengl_widget->getLightManager(),m_opengl_widget->getAssetManager());
    connect(m_assets_tree->selectionModel(), &QItemSelectionModel::selectionChanged, this,
            &MainWidget::on_treeSelectionChanged);
}

//
// Created by robin on 18/11/2020.
//

#include "singleMeshModelWidget.h"

SingleMeshModelWidget::SingleMeshModelWidget(const std::shared_ptr<Asset> &t_asset):
    ModelInterface(t_asset),
    m_asset(t_asset),
    openDiffuse(new QPushButton("Diffuse Color")),
    editDiffuse(new QColorDialog())
{
    editDiffuse->setOption(QColorDialog::DontUseNativeDialog,true);
    editDiffuse->setOption(QColorDialog::ShowAlphaChannel,true);
    glm::vec4 diffusecolor =m_asset->getDiffuseColor();
    editDiffuse->setCurrentColor(QColor::fromRgbF(diffusecolor.r,diffusecolor.g,diffusecolor.b,diffusecolor.a));
    editDiffuse->setVisible(false);

    mainLayout->addWidget(openDiffuse);

    QObject::connect(openDiffuse,SIGNAL(clicked()),this,SLOT(showDiffuse()));

    QObject::connect(editDiffuse,SIGNAL(currentColorChanged(const QColor)),this,SLOT(diffuseChanged(const QColor)));
}

SingleMeshModelWidget::~SingleMeshModelWidget() {

}

void SingleMeshModelWidget::diffuseChanged(const QColor &color) {
    m_asset->setDiffuseColor(glm::vec4(color.redF(),color.greenF(),color.blueF(),color.alphaF()));
    emit ObjectInterface::propertiesHaveChanged();
}

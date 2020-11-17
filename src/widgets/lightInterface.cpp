//
// Created by Robin on 10/03/2020.
//



#include "lightInterface.h"

LightInterface::LightInterface(const std::shared_ptr<Light> &light):
m_light(light),
editPositionX(new QDoubleSpinBox()),
editPositionY(new QDoubleSpinBox()),
editPositionZ(new QDoubleSpinBox()),
positionLayout(new QGridLayout()),
destroyButton(new QPushButton("Destroy Object")),
openAmbient(new QPushButton("Ambient")),
openDiffuse(new QPushButton("Diffuse")),
openSpecular(new QPushButton("Specular")),
editAmbient(new QColorDialog()),
editDiffuse(new QColorDialog()),
editSpecular(new QColorDialog()),

colorLayout(new QGridLayout),
mainLayout(new QVBoxLayout())
{
    m_light->setSelected(true);
    editPositionX->setMinimum(-99);
    editPositionY->setMinimum(-99);
    editPositionZ->setMinimum(-99);
    auto currentPosition =m_light->position();
    editPositionX->setValue(currentPosition.x);
    editPositionY->setValue(currentPosition.y);
    editPositionZ->setValue(currentPosition.z);
    positionLayout->addWidget(new QLabel("XPosition"),0,0);
    positionLayout->addWidget(new QLabel("YPosition"),0,1);
    positionLayout->addWidget(new QLabel("ZPosition"),0,2);
    positionLayout->addWidget(editPositionX,1,0);
    positionLayout->addWidget(editPositionY,1,1);
    positionLayout->addWidget(editPositionZ,1,2);
    mainLayout->addLayout(positionLayout);

    editSpecular->setOption(QColorDialog::DontUseNativeDialog,true);
    editDiffuse->setOption(QColorDialog::DontUseNativeDialog,true);
    editAmbient->setOption(QColorDialog::DontUseNativeDialog,true);
    editSpecular->setCurrentColor(QColor::fromRgbF(m_light->specular().r,m_light->specular().g,m_light->specular().b));
    editDiffuse->setCurrentColor(QColor::fromRgbF(m_light->diffuse().r,m_light->diffuse().g,m_light->diffuse().b));
    editAmbient->setCurrentColor(QColor::fromRgbF(m_light->ambient().r,m_light->ambient().g,m_light->ambient().b));
    editSpecular->setVisible(false);
    editAmbient->setVisible(false);
    editDiffuse->setVisible(false);
    colorLayout->addWidget(openAmbient,0,0);
    colorLayout->addWidget(openDiffuse,0,1);
    colorLayout->addWidget(openSpecular,0,2);

    mainLayout->addLayout(colorLayout);

    mainLayout->addWidget(destroyButton);
    setLayout(mainLayout);

    QObject::connect(destroyButton,SIGNAL(clicked()),this,SLOT(destroy()));

    QObject::connect(editPositionX,SIGNAL(valueChanged(double)),this,SLOT(positionEdited(double)));
    QObject::connect(editPositionY,SIGNAL(valueChanged(double)),this,SLOT(positionEdited(double)));
    QObject::connect(editPositionZ,SIGNAL(valueChanged(double)),this,SLOT(positionEdited(double)));

    QObject::connect(openAmbient,SIGNAL(clicked()),this,SLOT(showAmbient()));
    QObject::connect(openDiffuse,SIGNAL(clicked()),this,SLOT(showDiffuse()));
    QObject::connect(openSpecular,SIGNAL(clicked()),this,SLOT(showSpecular()));

    QObject::connect(editSpecular,SIGNAL(currentColorChanged(const QColor)),this,SLOT(specularChanged(const QColor)));
    QObject::connect(editAmbient,SIGNAL(currentColorChanged(const QColor)),this,SLOT(ambientChanged(const QColor)));
    QObject::connect(editDiffuse,SIGNAL(currentColorChanged(const QColor)),this,SLOT(diffuseChanged(const QColor)));
}

LightInterface::~LightInterface(){

    delete editPositionX;
    delete editPositionY;
    delete editPositionZ;
    delete positionLayout;
    delete mainLayout;
    m_light->setSelected(false);
}

void LightInterface::positionEdited(double t_pos) {
    m_light->setPosition(glm::vec3(editPositionX->value(), editPositionY->value(), editPositionZ->value()));
    emit ObjectInterface::propertiesHaveChanged();
}

void LightInterface::specularChanged(const QColor &color) {
    m_light->specular()=glm::vec3(color.redF(),color.greenF(),color.blueF());
    emit ObjectInterface::propertiesHaveChanged();

}

void LightInterface::ambientChanged(const QColor &color) {
    m_light->ambient()=glm::vec3(color.redF(),color.greenF(),color.blueF());
    emit ObjectInterface::propertiesHaveChanged();
}

void LightInterface::diffuseChanged(const QColor &color) {
    m_light->diffuse()=glm::vec3(color.redF(),color.greenF(),color.blueF());
    emit ObjectInterface::propertiesHaveChanged();
}

void LightInterface::destroy() {
    m_light->setToBeDestroyed(true);
    emit ObjectInterface::objectIsToBeDestroyed();
}



PointLightInterface::PointLightInterface(const std::shared_ptr<PointLight> &pointLight):
    LightInterface(pointLight),
    m_pointLight(pointLight),
    layout(new QVBoxLayout()),
    editConstant(new QDoubleSpinBox()),
    editQuadratic(new QDoubleSpinBox()),
    editLinear(new QDoubleSpinBox())
{
    editQuadratic->setSingleStep(0.01);
    editConstant->setSingleStep(0.01);
    editLinear->setSingleStep(0.01);
    editQuadratic->setValue(m_pointLight->getQuad());
    editConstant->setValue(m_pointLight->getConst());
    editLinear->setValue(m_pointLight->getLin());
    layout->addWidget(new QLabel("Quadratic : "));
    layout->addWidget(editQuadratic);
    layout->addWidget(new QLabel("Constant : "));
    layout->addWidget(editConstant);
    layout->addWidget(new QLabel("Linear : "));
    layout->addWidget(editLinear);
    mainLayout->addLayout(layout);

    QObject::connect(editQuadratic,SIGNAL(valueChanged(double)),this,SLOT(quadraticEdited(double)));
    QObject::connect(editConstant,SIGNAL(valueChanged(double)),this,SLOT(constantEdited(double)));
    QObject::connect(editLinear,SIGNAL(valueChanged(double)),this,SLOT(linearEdited(double)));

}

void PointLightInterface::quadraticEdited(double val) {
    m_pointLight->setQuadratic(val);
    emit propertiesHaveChanged();
}

void PointLightInterface::linearEdited(double val) {
    m_pointLight->setLinear(val);
    emit propertiesHaveChanged();
}

void PointLightInterface::constantEdited(double val) {
    m_pointLight->setConstant(val);
    emit propertiesHaveChanged();
}

PointLightInterface::~PointLightInterface() {
    delete editLinear;
    delete editConstant;
    delete editQuadratic;
    delete layout;
}


DirLightInterface::DirLightInterface(const std::shared_ptr<DirLight> &light, QWidget *parent):
LightInterface(light),
m_light(light),
editDirX(new QDoubleSpinBox()),
editDirY(new QDoubleSpinBox()),
editDirZ(new QDoubleSpinBox()),
directionLayout(new QGridLayout())
{
    editDirX->setMinimum(-1);
    editDirY->setMinimum(-1);
    editDirZ->setMinimum(-1);
    editDirX->setMaximum(1);
    editDirY->setMaximum(1);
    editDirZ->setMaximum(1);
    editDirX->setSingleStep(0.1);
    editDirY->setSingleStep(0.1);
    editDirZ->setSingleStep(0.1);
    editDirX->setValue(m_light->getDirection().x);
    editDirY->setValue(m_light->getDirection().y);
    editDirZ->setValue(m_light->getDirection().z);
    directionLayout->addWidget(new QLabel("Dir X"),0,0);
    directionLayout->addWidget(new QLabel("Dir Y"),0,1);
    directionLayout->addWidget(new QLabel("Dir Z"),0,2);
    directionLayout->addWidget(editDirX,1,0);
    directionLayout->addWidget(editDirY,1,1);
    directionLayout->addWidget(editDirZ,1,2);
    mainLayout->addLayout(directionLayout);

    QObject::connect(editDirX,SIGNAL(valueChanged(double)),this,SLOT(directionEdited(double)));
    QObject::connect(editDirY,SIGNAL(valueChanged(double)),this,SLOT(directionEdited(double)));
    QObject::connect(editDirZ,SIGNAL(valueChanged(double)),this,SLOT(directionEdited(double)));
}

DirLightInterface::~DirLightInterface() {

}

void DirLightInterface::directionEdited(double t_pos) {
    m_light->setDirection(glm::vec3(editDirX->value(),editDirY->value(),editDirZ->value()));
    emit ObjectInterface::propertiesHaveChanged();
}


SpotLightInterface::SpotLightInterface(const std::shared_ptr<SpotLight> &light):
LightInterface(light),
m_spotLight(light),
editDirX(new QDoubleSpinBox()),
editDirY(new QDoubleSpinBox()),
editDirZ(new QDoubleSpinBox()),
editConstant(new QDoubleSpinBox()),
editLinear(new QDoubleSpinBox()),
editQuadratic(new QDoubleSpinBox()),
editICO(new QDoubleSpinBox()),
editOCO(new QDoubleSpinBox()),
spotLayout(new QGridLayout())
{
    editQuadratic->setSingleStep(0.01);
    editConstant->setSingleStep(0.01);
    editLinear->setSingleStep(0.01);
    editDirX->setMinimum(-99);
    editDirY->setMinimum(-99);
    editDirZ->setMinimum(-99);
    editDirX->setValue(m_spotLight->getDirection().x);
    editDirY->setValue(m_spotLight->getDirection().y);
    editDirZ->setValue(m_spotLight->getDirection().z);
    spotLayout->addWidget(new QLabel("Target X"),0,0);
    spotLayout->addWidget(new QLabel("Target Y"),0,1);
    spotLayout->addWidget(new QLabel("Target Z"),0,2);
    spotLayout->addWidget(editDirX,1,0);
    spotLayout->addWidget(editDirY,1,1);
    spotLayout->addWidget(editDirZ,1,2);
    editConstant->setValue(m_spotLight->getConstant());
    editLinear->setValue(m_spotLight->getLinear());
    editQuadratic->setValue(m_spotLight->getQuad());
    editICO->setValue(glm::degrees(m_spotLight->getInnerCO()));
    editOCO->setValue(glm::degrees(m_spotLight->getInnerCO()));
    spotLayout->addWidget(new QLabel("Constant"),2,0);
    spotLayout->addWidget(new QLabel("Linear"),2,1);
    spotLayout->addWidget(new QLabel("Quadratic"),2,2);
    spotLayout->addWidget(editConstant,3,0);
    spotLayout->addWidget(editLinear,3,1);
    spotLayout->addWidget(editQuadratic,3,2);
    spotLayout->addWidget(new QLabel("Inner cut-off"),4,0);
    spotLayout->addWidget(new QLabel("Outer cut-off"),4,1);
    spotLayout->addWidget(editICO,5,0);
    spotLayout->addWidget(editOCO,5,1);

    mainLayout->addLayout(spotLayout);

    QObject::connect(editDirX,SIGNAL(valueChanged(double)),this,SLOT(directionEdited(double)));
    QObject::connect(editDirY,SIGNAL(valueChanged(double)),this,SLOT(directionEdited(double)));
    QObject::connect(editDirZ,SIGNAL(valueChanged(double)),this,SLOT(directionEdited(double)));
    QObject::connect(editConstant,SIGNAL(valueChanged(double)),this,SLOT(constantEdited(double)));
    QObject::connect(editLinear,SIGNAL(valueChanged(double)),this,SLOT(linearEdited(double)));
    QObject::connect(editQuadratic,SIGNAL(valueChanged(double)),this,SLOT(quadraticEdited(double)));
    QObject::connect(editICO,SIGNAL(valueChanged(double)),this,SLOT(icoEdited(double)));
    QObject::connect(editOCO,SIGNAL(valueChanged(double)),this,SLOT(ocoEdited(double)));
}

void SpotLightInterface::quadraticEdited(double val) {
    m_spotLight->setQuad(val);
    emit ObjectInterface::propertiesHaveChanged();
}

void SpotLightInterface::linearEdited(double val) {
    m_spotLight->setLinear(val);
    emit ObjectInterface::propertiesHaveChanged();
}

void SpotLightInterface::constantEdited(double val) {
    m_spotLight->setConstant(val);
    emit ObjectInterface::propertiesHaveChanged();
}

void SpotLightInterface::icoEdited(double val) {
    m_spotLight->setInnerCO(glm::radians(val));
    emit ObjectInterface::propertiesHaveChanged();
}

void SpotLightInterface::ocoEdited(double val) {
    m_spotLight->setOuterCO(glm::radians(val));
    emit ObjectInterface::propertiesHaveChanged();
}

void SpotLightInterface::directionEdited(double t_pos) {
    m_spotLight->setDirection(glm::vec3(editDirX->value(),editDirY->value(),editDirZ->value()));
    emit ObjectInterface::propertiesHaveChanged();
}

SpotLightInterface::~SpotLightInterface() {
    delete editQuadratic;
    delete editConstant;
    delete editLinear;
    delete editICO;
    delete editOCO;
    delete editDirZ;
    delete editDirY;
    delete editDirX;
    delete spotLayout;


}

//
// Created by Robin on 06/03/2020.
//


#include "modelInterface.h"

ModelInterface::ModelInterface(const std::shared_ptr<Asset> &t_asset):
        editScaleX(new QDoubleSpinBox()),
        editScaleY(new QDoubleSpinBox()),
        editScaleZ(new QDoubleSpinBox()),
        editPositionX(new QDoubleSpinBox()),
        editPositionY(new QDoubleSpinBox()),
        editPositionZ(new QDoubleSpinBox()),
        editRotationX(new QDoubleSpinBox()),
        editRotationY(new QDoubleSpinBox()),
        editRotationZ(new QDoubleSpinBox()),
        editB1RotationX(new QDoubleSpinBox()),
        editB1RotationY(new QDoubleSpinBox()),
        editB1RotationZ(new QDoubleSpinBox()),
        editB2RotationX(new QDoubleSpinBox()),
        editB2RotationY(new QDoubleSpinBox()),
        editB2RotationZ(new QDoubleSpinBox()),
        destroyButton(new QPushButton("Destroy Object")),
        scaleLayout(new QGridLayout()),
        rotationLayout(new QGridLayout()),
        positionLayout(new QGridLayout()),
        boneRotationLayout(new QGridLayout()),
        bones(t_asset->getBones()),
        chooseShader(new QComboBox()),
        m_asset(t_asset),
        mainLayout(new QVBoxLayout())


{
    m_asset->setSelected(true);
    chooseShader->addItem(QString{"Opaque"});
    chooseShader->addItem(QString{"Transparent"});
    chooseShader->setCurrentIndex(m_asset->getShaderType()==Asset::ShaderType::OPAQUE ? 0 :1);
    auto currentScale = m_asset->getScale();

    editScaleX->setValue(currentScale.x);
    editScaleX->setSingleStep(0.1);
    editScaleY->setValue(currentScale.y);
    editScaleY->setSingleStep(0.1);
    editScaleZ->setValue(currentScale.z);
    editScaleZ->setSingleStep(0.1);
    scaleLayout->addWidget(new QLabel("XScale"),0,0);
    scaleLayout->addWidget(new QLabel("YScale"),0,1);
    scaleLayout->addWidget(new QLabel("ZScale"),0,2);
    scaleLayout->addWidget(editScaleX,1,0);
    scaleLayout->addWidget(editScaleY,1,1);
    scaleLayout->addWidget(editScaleZ,1,2);

    auto currentRotation = m_asset->getRotation();


    editRotationX->setMaximum(180);
    editRotationX->setMinimum(-180);
    editRotationY->setMaximum(180);
    editRotationY->setMinimum(-180);
    editRotationZ->setMaximum(180);
    editRotationZ->setMinimum(-180);
    editRotationX->setValue(currentRotation.x);
    editRotationY->setValue(currentRotation.y);
    editRotationZ->setValue(currentRotation.z);
    rotationLayout->addWidget(new QLabel("XRotation"),0,0);
    rotationLayout->addWidget(new QLabel("YRotation"),0,1);
    rotationLayout->addWidget(new QLabel("ZRotation"),0,2);
    rotationLayout->addWidget(editRotationX,1,0);
    rotationLayout->addWidget(editRotationY,1,1);
    rotationLayout->addWidget(editRotationZ,1,2);

    auto currentPosition = m_asset->getTranslation();
    editPositionX->setMinimum(-99);
    editPositionY->setMinimum(-99);
    editPositionZ->setMinimum(-99);
    editPositionX->setValue(currentPosition.x);
    editPositionY->setValue(currentPosition.y);
    editPositionZ->setValue(currentPosition.z);

    positionLayout->addWidget(new QLabel("XPosition"),0,0);
    positionLayout->addWidget(new QLabel("YPosition"),0,1);
    positionLayout->addWidget(new QLabel("ZPosition"),0,2);
    positionLayout->addWidget(editPositionX,1,0);
    positionLayout->addWidget(editPositionY,1,1);
    positionLayout->addWidget(editPositionZ,1,2);



    mainLayout->addWidget(destroyButton);
    mainLayout->addLayout(positionLayout);
    mainLayout->addLayout(scaleLayout);
    mainLayout->addLayout(rotationLayout);

    if(bones->size() == 2){
        editB1RotationX->setMaximum(180);
        editB1RotationX->setMinimum(-180);
        editB1RotationY->setMaximum(180);
        editB1RotationY->setMinimum(-180);
        editB1RotationZ->setMaximum(180);
        editB1RotationZ->setMinimum(-180);
        editB1RotationX->setValue((*bones)[0].getTransformRot().x);
        editB1RotationY->setValue((*bones)[0].getTransformRot().y);
        editB1RotationZ->setValue((*bones)[0].getTransformRot().z);
        boneRotationLayout->addWidget(new QLabel("Bone 1 XRotation"),0,0);
        boneRotationLayout->addWidget(new QLabel("Bone 1 YRotation"),0,1);
        boneRotationLayout->addWidget(new QLabel("Bone 1 ZRotation"),0,2);
        boneRotationLayout->addWidget(editB1RotationX,1,0);
        boneRotationLayout->addWidget(editB1RotationY,1,1);
        boneRotationLayout->addWidget(editB1RotationZ,1,2);

        editB2RotationX->setMaximum(180);
        editB2RotationX->setMinimum(-180);
        editB2RotationY->setMaximum(180);
        editB2RotationY->setMinimum(-180);
        editB2RotationZ->setMaximum(180);
        editB2RotationZ->setMinimum(-180);
        editB2RotationX->setValue((*bones)[1].getTransformRot().x);
        editB2RotationY->setValue((*bones)[1].getTransformRot().y);
        editB2RotationZ->setValue((*bones)[1].getTransformRot().z);
        boneRotationLayout->addWidget(new QLabel("Bone 2 XRotation"),2,0);
        boneRotationLayout->addWidget(new QLabel("Bone 2 YRotation"),2,1);
        boneRotationLayout->addWidget(new QLabel("Bone 2 ZRotation"),2,2);
        boneRotationLayout->addWidget(editB2RotationX,3,0);
        boneRotationLayout->addWidget(editB2RotationY,3,1);
        boneRotationLayout->addWidget(editB2RotationZ,3,2);
    }
    mainLayout->addLayout(boneRotationLayout);




    mainLayout->addWidget(chooseShader);


    setLayout(mainLayout);
    QObject::connect(destroyButton,SIGNAL(clicked()),this,SLOT(destroyModel()));

    QObject::connect(chooseShader,SIGNAL(currentIndexChanged(int)),this,SLOT(changeShader(int)));



    QObject::connect(editScaleX,SIGNAL(valueChanged(double)),this,SLOT(scaleEdited(double)));
    QObject::connect(editScaleY,SIGNAL(valueChanged(double)),this,SLOT(scaleEdited(double)));
    QObject::connect(editScaleZ,SIGNAL(valueChanged(double)),this,SLOT(scaleEdited(double)));

    QObject::connect(editRotationX,SIGNAL(valueChanged(double)),this,SLOT(rotationEdited(double)));
    QObject::connect(editRotationY,SIGNAL(valueChanged(double)),this,SLOT(rotationEdited(double)));
    QObject::connect(editRotationZ,SIGNAL(valueChanged(double)),this,SLOT(rotationEdited(double)));

    QObject::connect(editPositionX,SIGNAL(valueChanged(double)),this,SLOT(positionEdited(double)));
    QObject::connect(editPositionY,SIGNAL(valueChanged(double)),this,SLOT(positionEdited(double)));
    QObject::connect(editPositionZ,SIGNAL(valueChanged(double)),this,SLOT(positionEdited(double)));

    QObject::connect(editB1RotationX,SIGNAL(valueChanged(double)),this,SLOT(boneRotationEdited(double)));
    QObject::connect(editB1RotationY,SIGNAL(valueChanged(double)),this,SLOT(boneRotationEdited(double)));
    QObject::connect(editB1RotationZ,SIGNAL(valueChanged(double)),this,SLOT(boneRotationEdited(double)));

    QObject::connect(editB2RotationX,SIGNAL(valueChanged(double)),this,SLOT(boneRotationEdited(double)));
    QObject::connect(editB2RotationY,SIGNAL(valueChanged(double)),this,SLOT(boneRotationEdited(double)));
    QObject::connect(editB2RotationZ,SIGNAL(valueChanged(double)),this,SLOT(boneRotationEdited(double)));
}

void ModelInterface::destroyModel()
{
    m_asset->setToBeDestroyed(true);
    emit ObjectInterface::objectIsToBeDestroyed();
}


void ModelInterface::scaleEdited(double t_scale)
{
    m_asset->setScale(glm::vec3(editScaleX->value(), editScaleY->value(), editScaleZ->value()));
    emit ObjectInterface::propertiesHaveChanged();
}

void ModelInterface::rotationEdited(double t_rot)
{
    m_asset->setRotation(glm::vec3(editRotationX->value(), editRotationY->value(), editRotationZ->value()));
    emit ObjectInterface::propertiesHaveChanged();
}


void ModelInterface::positionEdited(double t_pos)
{
    m_asset->setTranslation(glm::vec3(editPositionX->value(), editPositionY->value(), editPositionZ->value()));
    emit ObjectInterface::propertiesHaveChanged();
}

ModelInterface::~ModelInterface()
{
    delete editScaleX;
    delete editScaleY;
    delete editScaleZ;
    delete editRotationX;
    delete editRotationY;
    delete editRotationZ;
    delete editPositionX;
    delete editPositionY;
    delete editPositionZ;
    delete destroyButton;
    delete positionLayout;
    delete scaleLayout;
    delete rotationLayout;
    delete mainLayout;
    m_asset->setSelected(false);
}



void ModelInterface::changeShader(int row) {
    m_asset->setShaderType(row ==0 ? Asset::ShaderType::OPAQUE :Asset::ShaderType::TRANSPARENT);
    emit ObjectInterface::propertiesHaveChanged();
}

void ModelInterface::boneRotationEdited(double t_rot) {
    m_asset->setWaitingToUpdate(true);
    (*bones)[0].setTransform(Transform(glm::vec3(1),glm::vec3(0),glm::vec3(editB1RotationX->value(),editB1RotationY->value(),editB1RotationZ->value())));
    (*bones)[1].setTransform(Transform(glm::vec3(1),glm::vec3(0),glm::vec3(editB2RotationX->value(),editB2RotationY->value(),editB2RotationZ->value())));
    emit ObjectInterface::propertiesHaveChanged();
}








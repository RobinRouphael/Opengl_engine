//
// Created by Robin on 06/03/2020.
//


#include "modelInterface.h"

ModelInterface::ModelInterface(const std::shared_ptr<Model> &t_asset):
        editScaleX(new QDoubleSpinBox()),
        editScaleY(new QDoubleSpinBox()),
        editScaleZ(new QDoubleSpinBox()),
        editPositionX(new QDoubleSpinBox()),
        editPositionY(new QDoubleSpinBox()),
        editPositionZ(new QDoubleSpinBox()),
        editRotationX(new QDoubleSpinBox()),
        editRotationY(new QDoubleSpinBox()),
        editRotationZ(new QDoubleSpinBox()),
        destroyButton(new QPushButton("Destroy Object")),
        scaleLayout(new QGridLayout()),
        rotationLayout(new QGridLayout()),
        positionLayout(new QGridLayout()),
        m_asset(t_asset),
        mainLayout(new QVBoxLayout())


{
    auto currentScale = m_asset->getScale();

    editScaleX->setValue(currentScale.x);
    editScaleY->setValue(currentScale.y);
    editScaleZ->setValue(currentScale.z);
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
    setLayout(mainLayout);
    QObject::connect(destroyButton,SIGNAL(clicked()),this,SLOT(destroyModel()));

    QObject::connect(editScaleX,SIGNAL(valueChanged(double)),this,SLOT(scaleEdited(double)));
    QObject::connect(editScaleY,SIGNAL(valueChanged(double)),this,SLOT(scaleEdited(double)));
    QObject::connect(editScaleZ,SIGNAL(valueChanged(double)),this,SLOT(scaleEdited(double)));

    QObject::connect(editRotationX,SIGNAL(valueChanged(double)),this,SLOT(rotationEdited(double)));
    QObject::connect(editRotationY,SIGNAL(valueChanged(double)),this,SLOT(rotationEdited(double)));
    QObject::connect(editRotationZ,SIGNAL(valueChanged(double)),this,SLOT(rotationEdited(double)));

    QObject::connect(editPositionX,SIGNAL(valueChanged(double)),this,SLOT(positionEdited(double)));
    QObject::connect(editPositionY,SIGNAL(valueChanged(double)),this,SLOT(positionEdited(double)));
    QObject::connect(editPositionZ,SIGNAL(valueChanged(double)),this,SLOT(positionEdited(double)));
}

void ModelInterface::destroyModel()
{
    emit objectIsToBeDestroyed();
}


void ModelInterface::scaleEdited(double t_scale)
{
    m_asset->setScale(glm::vec3(editScaleX->value(), editScaleY->value(), editScaleZ->value()));
    emit propertiesHaveChanged();
}

void ModelInterface::rotationEdited(double t_rot)
{
    m_asset->setRotation(glm::vec3(editRotationX->value(), editRotationY->value(), editRotationZ->value()));
    emit propertiesHaveChanged();
}


void ModelInterface::positionEdited(double t_pos)
{
    m_asset->setTranslation(glm::vec3(editPositionX->value(), editPositionY->value(), editPositionZ->value()));
    emit propertiesHaveChanged();
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
}






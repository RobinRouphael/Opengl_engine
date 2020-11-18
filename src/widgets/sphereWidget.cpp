//
// Created by Robin on 04/03/2020.
//



#include "sphereWidget.h"

SphereWidget::SphereWidget(const std::shared_ptr<Sphere> &sphere):
        SingleMeshModelWidget(sphere),
        _sphere(sphere),
        editStacks(new QSpinBox()),
        editSectors(new QSpinBox()),
        setDiffuseTexture(new QPushButton("Set diffuse texture"))

{
    editStacks->setValue(sphere->getNBStacks());
    editSectors->setValue(sphere->getNBSectors());
    mainLayout->addWidget(new QLabel("NbStacks : "));
    mainLayout->addWidget(editStacks);
    mainLayout->addWidget(new QLabel("NbSectors : "));
    mainLayout->addWidget(editSectors);
    mainLayout->addWidget(setDiffuseTexture);
    QObject::connect(editStacks,SIGNAL(valueChanged(int)),this,SLOT(stacksEdited(int)));
    QObject::connect(editSectors,SIGNAL(valueChanged(int)),this,SLOT(sectorsEdited(int)));
    QObject::connect(setDiffuseTexture,SIGNAL(clicked()),this,SLOT(setTextureFromFile() ));
}

void SphereWidget::sectorsEdited(int val)
{
    _sphere->setNbSectors(val);
    emit propertiesHaveChanged();
}

void SphereWidget::stacksEdited(int val)
{
    _sphere->setNbStacks(val);
    emit propertiesHaveChanged();
}


void SphereWidget::setTextureFromFile()
{
    QString filename = QFileDialog::getOpenFileName(
            this,
            "Open Image file",
            "../textures",
            tr("*.jpg"));
    if(!filename.isEmpty()){
        std::shared_ptr<Material> material = std::make_shared<Material>();
        material->addDiffuseMap(std::make_shared<Texture>(filename.toStdString(),Texture::TextureType::DIFFUSE));
        _sphere->setMaterial(material);
    }
}

SphereWidget::~SphereWidget()
{
    delete editStacks;
    delete editSectors;
    delete setDiffuseTexture;
}






//
// Created by Robin on 10/03/2020.
//



#include "lightInterface.h"

LightInterface::LightInterface() {

}



PointLightWidget::PointLightWidget(const std::shared_ptr<PointLight> &pointLight):
    _pointLight(pointLight),
    layout(new QVBoxLayout()),
    editConstant(new QDoubleSpinBox()),
    editQuadratic(new QDoubleSpinBox()),
    editLinear(new QDoubleSpinBox())
{
    editQuadratic->setValue(_pointLight->getQuad());
    editConstant->setValue(_pointLight->getConst());
    editLinear->setValue(_pointLight->getLin());
    layout->addWidget(new QLabel("Quadratic : "));
    layout->addWidget(editQuadratic);
    layout->addWidget(new QLabel("Constant : "));
    layout->addWidget(editConstant);
    layout->addWidget(new QLabel("Linear : "));
    layout->addWidget(editLinear);
    setLayout(layout);
    QObject::connect(editQuadratic,SIGNAL(valueChanged(double)),this,SLOT(quadraticEdited(double)));
    QObject::connect(editConstant,SIGNAL(valueChanged(double)),this,SLOT(constantEdited(double)));
    QObject::connect(editLinear,SIGNAL(valueChanged(double)),this,SLOT(linearEdited(double)));

}

void PointLightWidget::quadraticEdited(double val) {
    _pointLight->setQuadratic(val);
    emit propertiesHaveChanged();
}

void PointLightWidget::linearEdited(double val) {
    _pointLight->setLinear(val);
    emit propertiesHaveChanged();
}

void PointLightWidget::constantEdited(double val) {
    _pointLight->setConstant(val);
    emit propertiesHaveChanged();
}

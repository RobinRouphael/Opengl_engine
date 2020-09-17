//
// Created by Robin on 13/03/2020.
//


#include "icoSphereWidget.h"

IcoSphereWidget::IcoSphereWidget(const std::shared_ptr<Icosphere> &sphere):
        ModelInterface(sphere),
        _sphere(sphere),
        editSubdivisions(new QSpinBox())
{
    editSubdivisions->setValue(sphere->getNBSubdivisions());
    mainLayout->addWidget(new QLabel("NbSubdivisions : "));
    mainLayout->addWidget(editSubdivisions);
    setLayout(mainLayout);
    QObject::connect(editSubdivisions,SIGNAL(valueChanged(int)),this,SLOT(subdivisionsEdited(int)));
}

void IcoSphereWidget::subdivisionsEdited(int val)
{
    _sphere->setNBSubdivisions(val);
    emit propertiesHaveChanged();
}

IcoSphereWidget::~IcoSphereWidget()
{
    delete editSubdivisions;
}


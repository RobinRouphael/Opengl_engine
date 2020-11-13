//
// Created by Robin on 10/03/2020.
//

#ifndef ENGINE_LIGHTINTERFACE_H
#define ENGINE_LIGHTINTERFACE_H


#include <QtWidgets/QWidget>
#include <memory>
#include <QtWidgets/QDoubleSpinBox>
#include "lights/light.h"
#include "lights/pointLight.h"
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QLabel>
class LightInterface : public QWidget{
    Q_OBJECT
public:
    LightInterface();

    signals:
        void propertiesHaveChanged();
};


class PointLightWidget : public LightInterface{
    Q_OBJECT
public:
    PointLightWidget(const std::shared_ptr<PointLight> &pointLight);
public slots:
    void quadraticEdited(double val);
    void linearEdited(double val);
    void constantEdited(double val);
private:
    std::shared_ptr<PointLight> _pointLight;
    QLayout *layout;
    QDoubleSpinBox *editConstant;
    QDoubleSpinBox *editQuadratic;
    QDoubleSpinBox *editLinear;

};


#endif //ENGINE_LIGHTINTERFACE_H

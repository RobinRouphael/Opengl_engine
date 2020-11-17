//
// Created by Robin on 10/03/2020.
//

#ifndef ENGINE_LIGHTINTERFACE_H
#define ENGINE_LIGHTINTERFACE_H


#include <QtWidgets/QWidget>
#include <memory>
#include <QtWidgets/QDoubleSpinBox>
#include "lights/light.h"
#include "objectInterface.h"
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QColorDialog>
#include <src/lights/dirLight.h>
#include <src/lights/pointLight.h>
#include <src/lights/spotLight.h>

class LightInterface : public ObjectInterface{
    Q_OBJECT
public:
    explicit LightInterface(const std::shared_ptr<Light> &light);
    ~LightInterface() override;

public slots:
    /**
     * Position of light was edited
     * @param t_pos : unused
     */
    void positionEdited(double t_pos);
    void showAmbient(){editAmbient->setVisible(true);}
    void showDiffuse(){editDiffuse->setVisible(true);}
    void showSpecular(){editSpecular->setVisible(true);}
    void specularChanged(const QColor &color);
    void ambientChanged(const QColor &color);
    void diffuseChanged(const QColor &color);
    void destroy();


private:
    std::shared_ptr<Light> m_light;
    QPushButton *destroyButton;
    QDoubleSpinBox *editPositionX;
    QDoubleSpinBox *editPositionY;
    QDoubleSpinBox *editPositionZ;
    QPushButton *openAmbient;
    QPushButton *openDiffuse;
    QPushButton *openSpecular;
    QColorDialog *editAmbient;
    QColorDialog *editDiffuse;
    QColorDialog *editSpecular;
    QGridLayout *positionLayout;
    QGridLayout *colorLayout;
protected:
    QVBoxLayout *mainLayout;
};

class DirLightInterface : public LightInterface{
Q_OBJECT
public:
    explicit DirLightInterface(const std::shared_ptr<DirLight> &light,QWidget*parent=nullptr);
    ~DirLightInterface() override;

public slots:
    void directionEdited(double t_pos);



private:
    QGridLayout *directionLayout;
    std::shared_ptr<DirLight> m_light;
    QDoubleSpinBox *editDirX;
    QDoubleSpinBox *editDirY;
    QDoubleSpinBox *editDirZ;

};

class PointLightInterface : public LightInterface{
Q_OBJECT
public:
    explicit PointLightInterface(const std::shared_ptr<PointLight> &pointLight);
    ~PointLightInterface() override;
public slots:
    void quadraticEdited(double val);
    void linearEdited(double val);
    void constantEdited(double val);
private:
    std::shared_ptr<PointLight> m_pointLight;
    QLayout *layout;
    QDoubleSpinBox *editConstant;
    QDoubleSpinBox *editQuadratic;
    QDoubleSpinBox *editLinear;

};

class SpotLightInterface : public LightInterface{
    Q_OBJECT
public:
    explicit SpotLightInterface(const std::shared_ptr<SpotLight> &light);
    ~SpotLightInterface() override;
public slots:
    void quadraticEdited(double val);
    void linearEdited(double val);
    void constantEdited(double val);
    void icoEdited(double val);
    void ocoEdited(double val);
    void directionEdited(double t_pos);

private:
    std::shared_ptr<SpotLight> m_spotLight;
    QGridLayout *spotLayout;
    QDoubleSpinBox *editDirX;
    QDoubleSpinBox *editDirY;
    QDoubleSpinBox *editDirZ;
    QDoubleSpinBox *editICO;
    QDoubleSpinBox *editOCO;
    QDoubleSpinBox *editConstant;
    QDoubleSpinBox *editQuadratic;
    QDoubleSpinBox *editLinear;

};


#endif //ENGINE_LIGHTINTERFACE_H

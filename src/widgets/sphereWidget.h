//
// Created by Robin on 04/03/2020.
//

#ifndef ENGINE_SPHEREWIDGET_H
#define ENGINE_SPHEREWIDGET_H


#include "modelInterface.h"
#include "src/models/sphere.h"
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QFileDialog>
class SphereWidget : public ModelInterface {
    Q_OBJECT
/**
 * QT Widget to edit UV Sphere
 */

public:
    /**
     * Constructor
     * @param sphere
     */
    explicit SphereWidget(const std::shared_ptr<Sphere> &sphere);
    /**
     * Destructor
     */
    ~SphereWidget() override;

public slots:
    /**
     * Number of stacks was edited
     * @param val
     */
    void stacksEdited(int val);
    /**
     * Number of sectors was edited
     * @param val
     */
    void sectorsEdited(int val);
    /**
     * Set a diffuse texture from image file
     */
    void setTextureFromFile();

private:
    std::shared_ptr<Sphere>_sphere;
    QSpinBox *editStacks;
    QSpinBox *editSectors;
    QPushButton *setDiffuseTexture;


};


#endif //ENGINE_SPHEREWIDGET_H

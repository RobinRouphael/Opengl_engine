//
// Created by Robin on 06/03/2020.
//

#ifndef ENGINE_MODELINTERFACE_H
#define ENGINE_MODELINTERFACE_H


#include <QtWidgets/QWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QLabel>
#include "core/model.h"

class ModelInterface : public QWidget{
    Q_OBJECT
    /**
     * Base class for QT Widgets to edit Models
     */
public:
    explicit ModelInterface(const std::shared_ptr<Model> &t_asset);

    virtual ~ModelInterface();

public slots:
    /**
     * Delete the model
     */
    void destroyModel();
    /**
     * Scale of model was edited
     * @param t_scale : unused
     */
    void scaleEdited(double t_scale);
    /**
     * Position of model was edited
     * @param t_pos : unused
     */
    void positionEdited(double t_pos);
    /**
     * Rotation of model was edited
     * @param t_rot : unused
     */
    void rotationEdited(double t_rot);


signals:
    /**
     * Properties of the model have been modified
     */
    void propertiesHaveChanged();
    /**
     * Model must be deleted
     */
    void objectIsToBeDestroyed();

private:

    QDoubleSpinBox *editScaleX;
    QDoubleSpinBox *editScaleY;
    QDoubleSpinBox *editScaleZ;

    QDoubleSpinBox *editPositionX;
    QDoubleSpinBox *editPositionY;
    QDoubleSpinBox *editPositionZ;

    QDoubleSpinBox *editRotationX;
    QDoubleSpinBox *editRotationY;
    QDoubleSpinBox *editRotationZ;


    QPushButton *destroyButton;
    QGridLayout *scaleLayout;
    QGridLayout *rotationLayout;
    QGridLayout *positionLayout;
    std::shared_ptr<Model> m_asset;

protected:

    QVBoxLayout *mainLayout;

};


#endif //ENGINE_MODELINTERFACE_H

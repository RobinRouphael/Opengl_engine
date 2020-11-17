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
#include <QtWidgets/QColorDialog>
#include <QtWidgets/QComboBox>
#include "core/asset.h"
#include "objectInterface.h"

class ModelInterface : public ObjectInterface{
    Q_OBJECT
    /**
     * Base class for QT Widgets to edit Models
     */
public:
    explicit ModelInterface(const std::shared_ptr<Asset> &t_asset);

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

    void showDiffuse(){editDiffuse->setVisible(true);}
    void diffuseChanged(const QColor &color);
    void changeShader(int row);

private:

    QPushButton *openDiffuse;
    QColorDialog *editDiffuse;

    QDoubleSpinBox *editScaleX;
    QDoubleSpinBox *editScaleY;
    QDoubleSpinBox *editScaleZ;

    QDoubleSpinBox *editPositionX;
    QDoubleSpinBox *editPositionY;
    QDoubleSpinBox *editPositionZ;

    QDoubleSpinBox *editRotationX;
    QDoubleSpinBox *editRotationY;
    QDoubleSpinBox *editRotationZ;
    QComboBox *chooseShader;

    QPushButton *destroyButton;
    QGridLayout *scaleLayout;
    QGridLayout *rotationLayout;
    QGridLayout *positionLayout;
    std::shared_ptr<Asset> m_asset;

protected:

    QVBoxLayout *mainLayout;

};


#endif //ENGINE_MODELINTERFACE_H

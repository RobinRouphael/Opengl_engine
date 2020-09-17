//
// Created by Robin on 13/03/2020.
//

#ifndef ENGINE_ICOSPHEREWIDGET_H
#define ENGINE_ICOSPHEREWIDGET_H


#include <src/core/modelInterface.h>
#include <src/models/icosphere.h>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QLabel>
class IcoSphereWidget : public ModelInterface{
Q_OBJECT
/**
 * QT Widget to edit IcoSpheres
 */

public:
    /**
     * Constructor
     * @param sphere to be edited
     */
    explicit IcoSphereWidget(const std::shared_ptr<Icosphere> &sphere);
    /***
     * Destructor
     */
    ~IcoSphereWidget() override;

public slots:
    /**
     * Number of subdivisons was edited
     * @param val
     */
    void subdivisionsEdited(int val);


private:
    std::shared_ptr<Icosphere>_sphere;
    QSpinBox *editSubdivisions;
};


#endif //ENGINE_ICOSPHEREWIDGET_H

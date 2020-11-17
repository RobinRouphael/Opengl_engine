//
// Created by robin on 15/11/2020.
//

#ifndef ENGINE_METABALLWIDGET_H
#define ENGINE_METABALLWIDGET_H


#include <src/models/metaball.h>
#include <QtWidgets/QListWidget>
#include "modelInterface.h"

class MetaballWidget : public ModelInterface {
    Q_OBJECT
public:
    MetaballWidget(const std::shared_ptr<MetaBall> &t_metaball);
    ~MetaballWidget() override;

public slots:
    void ballPositionEdited(double t_pos);
    void ballRadiusEdited(double t_pos);
    void isoLevelEdited(double t_val);
    void cubeSizeEdited(double t_val);
    void addNewBall();
    void removeCurrentBall();
    void updateList();
    void updateSettings(int row);
private:
    QPushButton *addBall;
    QPushButton *removeBall;
    QListWidget *ballList;

    QDoubleSpinBox *editRadius;
    QDoubleSpinBox *editCubeSize;
    QDoubleSpinBox *editIsoLevel;
    QDoubleSpinBox *editBallPositionX;
    QDoubleSpinBox *editBallPositionY;
    QDoubleSpinBox *editBallPositionZ;
    QGridLayout *ballPositionLayout;
    std::shared_ptr<MetaBall> m_meta_ball;
};


#endif //ENGINE_METABALLWIDGET_H

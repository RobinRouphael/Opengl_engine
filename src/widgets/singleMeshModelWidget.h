//
// Created by robin on 18/11/2020.
//

#ifndef ENGINE_SINGLEMESHMODELWIDGET_H
#define ENGINE_SINGLEMESHMODELWIDGET_H


#include "modelInterface.h"

class SingleMeshModelWidget : public ModelInterface {
Q_OBJECT
public:
    explicit SingleMeshModelWidget(const std::shared_ptr<Asset> &t_asset);
    ~SingleMeshModelWidget() override;

public slots:

    void showDiffuse(){editDiffuse->setVisible(true);}

    void diffuseChanged(const QColor &color);

private:
    QPushButton *openDiffuse;
    QColorDialog *editDiffuse;
    std::shared_ptr<Asset> m_asset;
};


#endif //ENGINE_SINGLEMESHMODELWIDGET_H

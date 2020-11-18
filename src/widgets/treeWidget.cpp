//
// Created by robin on 13/11/2020.
//


#include "treeWidget.h"
void TreeWidget::setupTree(const std::shared_ptr<LightsManager> &t_lightManager,const std::shared_ptr<AssetManager> &t_assetManager) {
    auto standardModel = new QStandardItemModel();
    QStandardItem *rootNode = standardModel->invisibleRootItem();

    QStandardItem *spotlights =new QStandardItem(QString("Spot Lights"));
    QStandardItem *dirlights =new QStandardItem(QString("Dir Lights"));
    QStandardItem *pointlights =new QStandardItem(QString("Point Lights"));
    for(auto &spot : t_lightManager->getSpotList()){
        spotlights->appendRow(new QStandardItem(spot.c_str()));
    }
    for(auto &dir : t_lightManager->getDirList()){
        dirlights->appendRow(new QStandardItem(dir.c_str()));
    }
    for(auto &point : t_lightManager->getPointList()){
        pointlights->appendRow(new QStandardItem(point.c_str()));
    }
    spotlights->setSelectable(false);
    dirlights->setSelectable(false);
    pointlights->setSelectable(false);

    QStandardItem *lights =new QStandardItem(QString("Lights"));
    lights->appendRow(spotlights);
    lights->appendRow(dirlights);
    lights->appendRow(pointlights);
    lights->setSelectable(false);

    QStandardItem *spheres =new QStandardItem(QString("Spheres"));
    QStandardItem *icoSpheres =new QStandardItem(QString("IcoSpheres"));
    QStandardItem *metaballs =new QStandardItem(QString("MetaBalls"));
    QStandardItem *custom =new QStandardItem(QString("Custom"));
    for(auto &sphere : t_assetManager->getSphereList()){
        spheres->appendRow(new QStandardItem(sphere.c_str()));
    }
    for(auto &ico : t_assetManager->getIcoSphereList()){
        icoSpheres->appendRow(new QStandardItem(ico.c_str()));
    }
    for(auto &cust : t_assetManager->getCustomList()){
        custom->appendRow(new QStandardItem(cust.c_str()));
    }
    for(auto &meta : t_assetManager->getMetaBallList()){
        metaballs->appendRow(new QStandardItem(meta.c_str()));
    }
    spheres->setSelectable(false);
    icoSpheres->setSelectable(false);
    custom->setSelectable(false);
    metaballs->setSelectable(false);
    QStandardItem *assets =new QStandardItem(QString("Assets"));
    assets->appendRow(spheres);
    assets->appendRow(icoSpheres);
    assets->appendRow(custom);
    assets->appendRow(metaballs);
    assets->setSelectable(false);

    standardModel->setItem(0,0,lights);
    standardModel->setItem(1,0,assets);


    setModel(standardModel);
    expandAll();

}
//
// Created by robin on 13/11/2020.
//

#ifndef ENGINE_TREEWIDGET_H
#define ENGINE_TREEWIDGET_H


#include <QtWidgets/QTreeView>
#include <src/core/lightsManager.h>
#include <src/core/assetManager.h>
#include <QtGui/QStandardItem>
class TreeWidget : public QTreeView{
    Q_OBJECT
public:
    explicit TreeWidget(QWidget *parent = nullptr) :
    QTreeView(parent)

    {
        setEditTriggers(QAbstractItemView::NoEditTriggers);}
    void setupTree(const std::shared_ptr<LightsManager> &t_lightManager,const std::shared_ptr<AssetManager> &t_assetManager);

private:

};


#endif //ENGINE_TREEWIDGET_H

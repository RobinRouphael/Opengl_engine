//
// Created by Robin on 13/03/2020.
//

#ifndef ENGINE_IMPORTEDMODELWIDGET_H
#define ENGINE_IMPORTEDMODELWIDGET_H


#include "modelInterface.h"
#include "src/models/assimpmodel.h"

class ImportedModelWidget : public ModelInterface {
    Q_OBJECT
/**
 * QT Widget to edit Imported Model
 */

public:
    /**
     * Constructor
     * @param assimpMesh
     */
    explicit ImportedModelWidget(const std::shared_ptr<AssimpModel> &assimpMesh);
    /**
     * Destructor
     */
    ~ImportedModelWidget() override;


private:
    std::shared_ptr<AssimpModel>_assimpMesh;

};


#endif //ENGINE_IMPORTEDMODELWIDGET_H

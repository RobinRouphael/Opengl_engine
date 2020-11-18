//
// Created by Robin on 13/03/2020.
//

#include "importedModelWidget.h"

ImportedModelWidget::ImportedModelWidget(const std::shared_ptr<Asset> &assimpMesh):
        _assimpMesh(assimpMesh),
        SingleMeshModelWidget (assimpMesh)
    {

    }

ImportedModelWidget::~ImportedModelWidget()
{

}

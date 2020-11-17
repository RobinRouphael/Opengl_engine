//
// Created by Robin on 13/03/2020.
//

#include "importedModelWidget.h"

ImportedModelWidget::ImportedModelWidget(const std::shared_ptr<AssimpModel> &assimpMesh):
        _assimpMesh(assimpMesh),
        ModelInterface(assimpMesh)
    {

    }

ImportedModelWidget::~ImportedModelWidget()
{

}

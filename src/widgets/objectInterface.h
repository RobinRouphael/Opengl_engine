//
// Created by robin on 14/11/2020.
//

#ifndef ENGINE_OBJECTINTERFACE_H
#define ENGINE_OBJECTINTERFACE_H


#include <QtWidgets/QWidget>

class ObjectInterface : public QWidget {
    Q_OBJECT
public:

    signals:
            void propertiesHaveChanged();

            void objectIsToBeDestroyed();
};


#endif //ENGINE_OBJECTINTERFACE_H

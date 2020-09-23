/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QWidget>
#include "myopenglwidget.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionCreate_Sphere;
    QAction *actionCreate_IcoSphere;
    QAction *actionCreate_Mesh_from_file;
    QAction *actionPhong;
    QAction *actionBasic_Texture;
    QAction *actionApproximation_error;
    QWidget *centralwidget;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *mainLayout;
    MyOpenGLWidget *openGLWidget;
    QWidget *panelWidget;
    QMenuBar *menuBar;
    QMenu *SelectShader;
    QMenu *menuCreate_Asset;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1287, 674);
        actionCreate_Sphere = new QAction(MainWindow);
        actionCreate_Sphere->setObjectName(QStringLiteral("actionCreate_Sphere"));
        actionCreate_IcoSphere = new QAction(MainWindow);
        actionCreate_IcoSphere->setObjectName(QStringLiteral("actionCreate_IcoSphere"));
        actionCreate_Mesh_from_file = new QAction(MainWindow);
        actionCreate_Mesh_from_file->setObjectName(QStringLiteral("actionCreate_Mesh_from_file"));
        actionPhong = new QAction(MainWindow);
        actionPhong->setObjectName(QStringLiteral("actionPhong"));
        actionBasic_Texture = new QAction(MainWindow);
        actionBasic_Texture->setObjectName(QStringLiteral("actionBasic_Texture"));
        actionApproximation_error = new QAction(MainWindow);
        actionApproximation_error->setObjectName(QStringLiteral("actionApproximation_error"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        horizontalLayoutWidget = new QWidget(centralwidget);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(0, 0, 1281, 601));
        mainLayout = new QHBoxLayout(horizontalLayoutWidget);
        mainLayout->setObjectName(QStringLiteral("mainLayout"));
        mainLayout->setContentsMargins(0, 0, 0, 0);
        openGLWidget = new MyOpenGLWidget(horizontalLayoutWidget);
        openGLWidget->setObjectName(QStringLiteral("openGLWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(4);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(openGLWidget->sizePolicy().hasHeightForWidth());
        openGLWidget->setSizePolicy(sizePolicy);
        openGLWidget->setMouseTracking(false);

        mainLayout->addWidget(openGLWidget);

        panelWidget = new QWidget(horizontalLayoutWidget);
        panelWidget->setObjectName(QStringLiteral("panelWidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(1);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(panelWidget->sizePolicy().hasHeightForWidth());
        panelWidget->setSizePolicy(sizePolicy1);

        mainLayout->addWidget(panelWidget);

        MainWindow->setCentralWidget(centralwidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1287, 29));
        SelectShader = new QMenu(menuBar);
        SelectShader->setObjectName(QStringLiteral("SelectShader"));
        menuCreate_Asset = new QMenu(menuBar);
        menuCreate_Asset->setObjectName(QStringLiteral("menuCreate_Asset"));
        MainWindow->setMenuBar(menuBar);

        menuBar->addAction(SelectShader->menuAction());
        menuBar->addAction(menuCreate_Asset->menuAction());
        SelectShader->addAction(actionPhong);
        SelectShader->addAction(actionBasic_Texture);
        SelectShader->addAction(actionApproximation_error);
        menuCreate_Asset->addAction(actionCreate_Sphere);
        menuCreate_Asset->addAction(actionCreate_IcoSphere);
        menuCreate_Asset->addAction(actionCreate_Mesh_from_file);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        actionCreate_Sphere->setText(QApplication::translate("MainWindow", "Create Sphere", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionCreate_Sphere->setToolTip(QApplication::translate("MainWindow", "<html><head/><body><p>Create a new UV Sphere</p></body></html>", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionCreate_IcoSphere->setText(QApplication::translate("MainWindow", "Create IcoSphere", Q_NULLPTR));
        actionCreate_Mesh_from_file->setText(QApplication::translate("MainWindow", "Create Mesh from file", Q_NULLPTR));
        actionPhong->setText(QApplication::translate("MainWindow", "Phong", Q_NULLPTR));
        actionBasic_Texture->setText(QApplication::translate("MainWindow", "Basic Texture", Q_NULLPTR));
        actionApproximation_error->setText(QApplication::translate("MainWindow", "Approximation error", Q_NULLPTR));
        SelectShader->setTitle(QApplication::translate("MainWindow", "Select Shader", Q_NULLPTR));
        menuCreate_Asset->setTitle(QApplication::translate("MainWindow", "Create Model", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

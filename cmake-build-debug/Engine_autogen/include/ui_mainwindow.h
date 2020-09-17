/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
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
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1287, 674);
        actionCreate_Sphere = new QAction(MainWindow);
        actionCreate_Sphere->setObjectName(QString::fromUtf8("actionCreate_Sphere"));
        actionCreate_IcoSphere = new QAction(MainWindow);
        actionCreate_IcoSphere->setObjectName(QString::fromUtf8("actionCreate_IcoSphere"));
        actionCreate_Mesh_from_file = new QAction(MainWindow);
        actionCreate_Mesh_from_file->setObjectName(QString::fromUtf8("actionCreate_Mesh_from_file"));
        actionPhong = new QAction(MainWindow);
        actionPhong->setObjectName(QString::fromUtf8("actionPhong"));
        actionBasic_Texture = new QAction(MainWindow);
        actionBasic_Texture->setObjectName(QString::fromUtf8("actionBasic_Texture"));
        actionApproximation_error = new QAction(MainWindow);
        actionApproximation_error->setObjectName(QString::fromUtf8("actionApproximation_error"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        horizontalLayoutWidget = new QWidget(centralwidget);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(0, 0, 1281, 601));
        mainLayout = new QHBoxLayout(horizontalLayoutWidget);
        mainLayout->setObjectName(QString::fromUtf8("mainLayout"));
        mainLayout->setContentsMargins(0, 0, 0, 0);
        openGLWidget = new MyOpenGLWidget(horizontalLayoutWidget);
        openGLWidget->setObjectName(QString::fromUtf8("openGLWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(4);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(openGLWidget->sizePolicy().hasHeightForWidth());
        openGLWidget->setSizePolicy(sizePolicy);
        openGLWidget->setMouseTracking(false);

        mainLayout->addWidget(openGLWidget);

        panelWidget = new QWidget(horizontalLayoutWidget);
        panelWidget->setObjectName(QString::fromUtf8("panelWidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(1);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(panelWidget->sizePolicy().hasHeightForWidth());
        panelWidget->setSizePolicy(sizePolicy1);

        mainLayout->addWidget(panelWidget);

        MainWindow->setCentralWidget(centralwidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1287, 29));
        SelectShader = new QMenu(menuBar);
        SelectShader->setObjectName(QString::fromUtf8("SelectShader"));
        menuCreate_Asset = new QMenu(menuBar);
        menuCreate_Asset->setObjectName(QString::fromUtf8("menuCreate_Asset"));
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
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionCreate_Sphere->setText(QCoreApplication::translate("MainWindow", "Create Sphere", nullptr));
#if QT_CONFIG(tooltip)
        actionCreate_Sphere->setToolTip(QCoreApplication::translate("MainWindow", "<html><head/><body><p>Create a new UV Sphere</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        actionCreate_IcoSphere->setText(QCoreApplication::translate("MainWindow", "Create IcoSphere", nullptr));
        actionCreate_Mesh_from_file->setText(QCoreApplication::translate("MainWindow", "Create Mesh from file", nullptr));
        actionPhong->setText(QCoreApplication::translate("MainWindow", "Phong", nullptr));
        actionBasic_Texture->setText(QCoreApplication::translate("MainWindow", "Basic Texture", nullptr));
        actionApproximation_error->setText(QCoreApplication::translate("MainWindow", "Approximation error", nullptr));
        SelectShader->setTitle(QCoreApplication::translate("MainWindow", "Select Shader", nullptr));
        menuCreate_Asset->setTitle(QCoreApplication::translate("MainWindow", "Create Model", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

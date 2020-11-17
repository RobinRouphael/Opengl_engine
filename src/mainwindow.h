#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QFrame>
#include <iostream>
#include <sstream>
#include <iomanip>
#include "myopenglwidget.h"
#include <QPushButton>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QListWidgetItem>
#include <QActionGroup>
#include <src/widgets/mainWidget.h>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void on_actionCreate_Sphere_triggered();

    void on_actionCreate_IcoSphere_triggered();

    void on_actionCreate_Mesh_from_file_triggered();

    void on_actionPhong_triggered();

    void on_actionBasic_Texture_triggered();

    void on_actionApproximation_error_triggered();

    void on_actionSpot_Light_triggered();

    void on_actionDirectional_Light_triggered();

    void on_actionPoint_Light_triggered();

    void on_actionCreate_Metaball_triggered();

    void on_actionLaunch_Demo_triggered();

private:
    Ui::MainWindow *ui;
    QActionGroup *shaderSelection;


};

#endif // MAINWINDOW_H

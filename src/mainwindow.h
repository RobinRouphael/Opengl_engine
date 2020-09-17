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

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    /**
     * Reconnect Model properties widget with openGLWidget
     * @param interface : model properties widget
     */
    void reconnectInterface(ModelInterface *interface);
public slots:
    /**
     * Display the properties widget of the selected model
     * @param interface model properties widget
     */
    void objectSelected(ModelInterface *interface);
    /**
     * Remove the property widget
     */
    void noObjectSelected();

private slots:

    void on_actionCreate_Sphere_triggered();

    void on_actionCreate_IcoSphere_triggered();

    void on_actionCreate_Mesh_from_file_triggered();

    void on_actionPhong_triggered();

    void on_actionBasic_Texture_triggered();

    void on_actionApproximation_error_triggered();

private:
    Ui::MainWindow *ui;
    QActionGroup *shaderSelection;
    ModelInterface *panelWidget;


};

#endif // MAINWINDOW_H

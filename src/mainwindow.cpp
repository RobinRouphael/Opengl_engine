

#include "mainwindow.h"

#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{

    QSurfaceFormat format;
    format.setVersion(4, 1);
    format.setProfile(QSurfaceFormat::CoreProfile);
    format.setDepthBufferSize(24);
    QSurfaceFormat::setDefaultFormat(format);

    ui->setupUi(this);
    shaderSelection = new QActionGroup(this);

    ui->actionPhong->setCheckable(true);

    ui->actionBasic_Texture->setCheckable(true);

    ui->actionApproximation_error->setCheckable(true);

    shaderSelection->addAction(ui->actionPhong);
    shaderSelection->addAction(ui->actionBasic_Texture);
    shaderSelection->addAction(ui->actionApproximation_error);

    ui->actionPhong->setChecked(true);

    ui->centralwidget->getGLWidget()->setFocus();
    ui->centralwidget->getGLWidget()->setFormat(format);

}

MainWindow::~MainWindow()
{
    delete ui;
    delete shaderSelection;
}


void MainWindow::on_actionCreate_Sphere_triggered()
{
    ui->centralwidget->getGLWidget()->createNewSphere();


}

void MainWindow::on_actionCreate_IcoSphere_triggered()
{
    ui->centralwidget->getGLWidget()->createNewIcoSphere();


}

void MainWindow::on_actionCreate_Mesh_from_file_triggered()
{
    QString filename = QFileDialog::getOpenFileName(
            this,
            "Open Obj file",
            "../objects",
            tr("*.obj"));
    if(!filename.isEmpty())
        ui->centralwidget->getGLWidget()->createImportedModel(filename.toStdString());

}


void MainWindow::on_actionPhong_triggered()
{
    ui->centralwidget->getGLWidget()->setShader(tr("Phong"));
}

void MainWindow::on_actionBasic_Texture_triggered()
{
    ui->centralwidget->getGLWidget()->setShader(tr("Basic Texture"));
}

void MainWindow::on_actionApproximation_error_triggered()
{
    ui->centralwidget->getGLWidget()->setShader(tr("Approximation Error"));
}

void MainWindow::on_actionCreate_Metaball_triggered() {
    ui->centralwidget->getGLWidget()->createMetaBall();
}

void MainWindow::on_actionPoint_Light_triggered() {
    ui->centralwidget->getGLWidget()->createNewPointLight();
}

void MainWindow::on_actionDirectional_Light_triggered() {
    ui->centralwidget->getGLWidget()->createNewDirLight();
}

void MainWindow::on_actionSpot_Light_triggered() {
    ui->centralwidget->getGLWidget()->createNewSpotLight();
}

void MainWindow::on_actionLaunch_Demo_triggered() {
    ui->centralwidget->getGLWidget()->createDemo();
}



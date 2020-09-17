

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
    ui->mainLayout->removeWidget(ui->panelWidget);
    panelWidget = nullptr;


    shaderSelection = new QActionGroup(this);


    ui->actionPhong->setCheckable(true);

    ui->actionBasic_Texture->setCheckable(true);

    ui->actionApproximation_error->setCheckable(true);

    shaderSelection->addAction(ui->actionPhong);
    shaderSelection->addAction(ui->actionBasic_Texture);
    shaderSelection->addAction(ui->actionApproximation_error);

    ui->actionPhong->setChecked(true);

    ui->openGLWidget->setFocus();
    ui->openGLWidget->setFormat(format);
    ui->centralwidget->setLayout(ui->mainLayout);
    QObject::connect(ui->openGLWidget,&MyOpenGLWidget::objectSelectionChanged,this,&MainWindow::objectSelected);
    QObject::connect(ui->openGLWidget,&MyOpenGLWidget::noObjectSelected,this,&MainWindow::noObjectSelected);

}

MainWindow::~MainWindow()
{
    delete ui;
    if(panelWidget)
        delete panelWidget;
    delete shaderSelection;
}




void MainWindow::objectSelected(ModelInterface *interface)
{
    if(ui->panelWidget){
        ui->mainLayout->removeWidget(ui->panelWidget);
        delete ui->panelWidget;
    }
    ui->panelWidget = interface;
    ui->mainLayout->addWidget(ui->panelWidget);
    reconnectInterface(interface);
}

void MainWindow::noObjectSelected()
{
    ui->mainLayout->removeWidget(ui->panelWidget);
    delete ui->panelWidget;
    ui->panelWidget=nullptr;
}


void MainWindow::reconnectInterface(ModelInterface *interface)
{
    QObject::connect(interface, &ModelInterface::propertiesHaveChanged, ui->openGLWidget,
                     &MyOpenGLWidget::modelPropertiesChanged);
    QObject::connect(interface, &ModelInterface::objectIsToBeDestroyed, ui->openGLWidget, &MyOpenGLWidget::selectedIsToBeDestroyed);
}

void MainWindow::on_actionCreate_Sphere_triggered()
{
    ui->openGLWidget->createNewSphere();
    ui->openGLWidget->setFocus();
}

void MainWindow::on_actionCreate_IcoSphere_triggered()
{
    ui->openGLWidget->createNewIcoSphere();
    ui->openGLWidget->setFocus();
}

void MainWindow::on_actionCreate_Mesh_from_file_triggered()
{
    QString filename = QFileDialog::getOpenFileName(
            this,
            "Open Obj file",
            "../objects",
            tr("*.obj"));
    if(!filename.isEmpty())
        ui->openGLWidget->createImportedModel(filename.toStdString());
    ui->openGLWidget->setFocus();
}


void MainWindow::on_actionPhong_triggered()
{
    ui->openGLWidget->setShader(tr("Phong"));
}

void MainWindow::on_actionBasic_Texture_triggered()
{
    ui->openGLWidget->setShader(tr("Basic Texture"));
}

void MainWindow::on_actionApproximation_error_triggered()
{
    ui->openGLWidget->setShader(tr("Approximation Error"));
}

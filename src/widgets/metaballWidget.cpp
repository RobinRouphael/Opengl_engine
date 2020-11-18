//
// Created by robin on 15/11/2020.
//

#include "metaballWidget.h"

MetaballWidget::MetaballWidget(const std::shared_ptr<MetaBall> &t_metaball)
: SingleMeshModelWidget(t_metaball),
  m_meta_ball(t_metaball),
  ballList(new QListWidget),
  editBallPositionX(new QDoubleSpinBox()),
  editBallPositionY(new QDoubleSpinBox()),
  editBallPositionZ(new QDoubleSpinBox()),
  editRadius(new QDoubleSpinBox()),
  ballPositionLayout(new QGridLayout()),
  addBall(new QPushButton("Add ball")),
  removeBall(new QPushButton("Remove ball")),
  editCubeSize(new QDoubleSpinBox()),
  editIsoLevel(new QDoubleSpinBox())
{
    auto balls = t_metaball->getBalls();
    for(int i=0; i<balls.size();i++){
        ballList->addItem(QString(std::to_string(i).c_str()));
    }
    mainLayout->addWidget(new QLabel("Balls list"));
    mainLayout->addWidget(ballList);
    ballList->setCurrentRow(0);
    m_meta_ball->setSelectedBall(0);
    auto currentPosition = m_meta_ball->getBalls()[ballList->currentRow()].pos;
    auto currentRadius = m_meta_ball->getBalls()[ballList->currentRow()].rad;
    auto currentIsoLevel = m_meta_ball->getIsolevel();
    auto cubeSize = m_meta_ball->getCubeSize();
    editBallPositionX->setMinimum(-99);
    editBallPositionY->setMinimum(-99);
    editBallPositionZ->setMinimum(-99);
    editBallPositionX->setValue(currentPosition.x);
    editBallPositionY->setValue(currentPosition.y);
    editBallPositionZ->setValue(currentPosition.z);
    editIsoLevel->setValue(currentIsoLevel);
    editCubeSize->setValue(cubeSize);
    editIsoLevel->setSingleStep(0.01);
    editCubeSize->setSingleStep(0.01);
    editRadius->setValue(currentRadius);
    mainLayout->addWidget(addBall);
    mainLayout->addWidget(removeBall);
    ballPositionLayout->addWidget(new QLabel("X Ball Position"), 0, 0);
    ballPositionLayout->addWidget(new QLabel("Y Ball Position"), 0, 1);
    ballPositionLayout->addWidget(new QLabel("Z Ball Position"), 0, 2);
    ballPositionLayout->addWidget(editBallPositionX, 1, 0);
    ballPositionLayout->addWidget(editBallPositionY, 1, 1);
    ballPositionLayout->addWidget(editBallPositionZ, 1, 2);
    ballPositionLayout->addWidget(new QLabel("Ball Radius"),2,0);
    ballPositionLayout->addWidget(editRadius,3,0);
    ballPositionLayout->addWidget(new QLabel("Cube size"),2,1);
    ballPositionLayout->addWidget(editCubeSize,3,1);
    ballPositionLayout->addWidget(new QLabel("Iso level"),2,2);
    ballPositionLayout->addWidget(editIsoLevel,3,2);
    mainLayout->addLayout(ballPositionLayout);


    setLayout(mainLayout);

    QObject::connect(editBallPositionX, SIGNAL(valueChanged(double)), this, SLOT(ballPositionEdited(double)));
    QObject::connect(editBallPositionY, SIGNAL(valueChanged(double)), this, SLOT(ballPositionEdited(double)));
    QObject::connect(editBallPositionZ, SIGNAL(valueChanged(double)), this, SLOT(ballPositionEdited(double)));
    QObject::connect(editCubeSize, SIGNAL(valueChanged(double)), this, SLOT(cubeSizeEdited(double)));
    QObject::connect(editIsoLevel, SIGNAL(valueChanged(double)), this, SLOT(isoLevelEdited(double)));
    QObject::connect(editRadius, SIGNAL(valueChanged(double)), this, SLOT(ballRadiusEdited(double)));
    QObject::connect(addBall,SIGNAL(clicked()),this,SLOT(addNewBall()));
    QObject::connect(removeBall,SIGNAL(clicked()),this,SLOT(removeCurrentBall()));
    QObject::connect(ballList,SIGNAL(currentRowChanged(int)),this,SLOT(updateSettings(int)));
    emit propertiesHaveChanged();
}

MetaballWidget::~MetaballWidget() {
    delete editBallPositionX;
    delete editBallPositionY;
    delete editRadius;
    delete editBallPositionZ;
    delete addBall;
    delete removeBall;
    delete ballList;
}

void MetaballWidget::ballPositionEdited(double t_pos) {
    m_meta_ball->setBallPosition(glm::vec3(editBallPositionX->value(),editBallPositionY->value(),editBallPositionZ->value()));
    emit ObjectInterface::propertiesHaveChanged();
}

void MetaballWidget::ballRadiusEdited(double t_pos) {
    m_meta_ball->setBallRadius(t_pos);
    emit ObjectInterface::propertiesHaveChanged();
}

void MetaballWidget::addNewBall() {
    m_meta_ball->addBall();
    emit ObjectInterface::propertiesHaveChanged();
    updateList();
}

void MetaballWidget::removeCurrentBall() {
    m_meta_ball->removeBall();
    emit ObjectInterface::propertiesHaveChanged();
    updateList();
}

void MetaballWidget::updateList() {
    auto balls = m_meta_ball->getBalls();
    ballList->clear();
    for(int i=0; i<balls.size();i++){
        ballList->addItem(QString(std::to_string(i).c_str()));
    }
}

void MetaballWidget::updateSettings(int row) {
    if(ballList->currentRow()<m_meta_ball->getBalls().size()) {
        m_meta_ball->setSelectedBall(ballList->currentRow());
        auto currentPosition = m_meta_ball->getBalls()[ballList->currentRow()].pos;
        auto currentRadius = m_meta_ball->getBalls()[ballList->currentRow()].rad;
        editBallPositionX->setValue(currentPosition.x);
        editBallPositionY->setValue(currentPosition.y);
        editBallPositionZ->setValue(currentPosition.z);
        editRadius->setValue(currentRadius);
    }
}

void MetaballWidget::isoLevelEdited(double t_val) {
    m_meta_ball->setIsoLevel(t_val);
    emit ObjectInterface::propertiesHaveChanged();
}

void MetaballWidget::cubeSizeEdited(double t_val) {
    m_meta_ball->setCubeSize(t_val);
    emit ObjectInterface::propertiesHaveChanged();
}

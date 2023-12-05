#include "camera.h"
#include "ui_camera.h"
#include <QMainWindow>
#include <QDialog>
#include <QCamera>
#include <QCameraImageCapture>
#include <QMediaRecorder>
#include <QMediaService>
#include <QMediaRecorder>
#include <QCameraViewfinder>
#include <QCameraInfo>
#include <QMediaMetaData>
#include <QPalette>

camera::camera(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::camera)
{
    ui->setupUi(this);

    setCamera(QCameraInfo::defaultCamera()); //Camera devices:
}

camera::~camera()
{
    delete ui;
}

void camera::setCamera(const QCameraInfo &cameraInfo)
{
    Camera = new QCamera(cameraInfo);
    imageCapture = new QCameraImageCapture(Camera);
    Camera->setViewfinder(ui->viewfinder_2Client);
    connect(imageCapture, &QCameraImageCapture::readyForCaptureChanged, this, &camera::readyForCapture);
    Camera->start();
}


void camera::readyForCapture(bool ready)
{
    ui->takeImageButtonClient->setEnabled(ready);
}

void camera::on_takeImageButtonClient_clicked()
{
    isCapturingImage = true;
    imageCapture->capture();
}

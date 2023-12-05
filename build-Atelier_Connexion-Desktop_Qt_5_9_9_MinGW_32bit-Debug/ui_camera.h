/********************************************************************************
** Form generated from reading UI file 'camera.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CAMERA_H
#define UI_CAMERA_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>
#include "qcameraviewfinder.h"

QT_BEGIN_NAMESPACE

class Ui_camera
{
public:
    QWidget *centralwidget;
    QStackedWidget *stackedWidget;
    QWidget *viewfinderPage_2;
    QGridLayout *gridLayout_6;
    QCameraViewfinder *viewfinder_2Client;
    QWidget *previewPage_2;
    QGridLayout *gridLayout_7;
    QLabel *lastImagePreviewLabel_2;
    QPushButton *takeImageButtonClient;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *camera)
    {
        if (camera->objectName().isEmpty())
            camera->setObjectName(QStringLiteral("camera"));
        camera->resize(1141, 600);
        centralwidget = new QWidget(camera);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName(QStringLiteral("stackedWidget"));
        stackedWidget->setGeometry(QRect(120, 40, 901, 401));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(1);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(stackedWidget->sizePolicy().hasHeightForWidth());
        stackedWidget->setSizePolicy(sizePolicy);
        QPalette palette;
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Base, brush);
        QBrush brush1(QColor(145, 145, 145, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        stackedWidget->setPalette(palette);
        viewfinderPage_2 = new QWidget();
        viewfinderPage_2->setObjectName(QStringLiteral("viewfinderPage_2"));
        gridLayout_6 = new QGridLayout(viewfinderPage_2);
        gridLayout_6->setObjectName(QStringLiteral("gridLayout_6"));
        viewfinder_2Client = new QCameraViewfinder(viewfinderPage_2);
        viewfinder_2Client->setObjectName(QStringLiteral("viewfinder_2Client"));

        gridLayout_6->addWidget(viewfinder_2Client, 0, 0, 1, 1);

        stackedWidget->addWidget(viewfinderPage_2);
        previewPage_2 = new QWidget();
        previewPage_2->setObjectName(QStringLiteral("previewPage_2"));
        gridLayout_7 = new QGridLayout(previewPage_2);
        gridLayout_7->setObjectName(QStringLiteral("gridLayout_7"));
        lastImagePreviewLabel_2 = new QLabel(previewPage_2);
        lastImagePreviewLabel_2->setObjectName(QStringLiteral("lastImagePreviewLabel_2"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::MinimumExpanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(lastImagePreviewLabel_2->sizePolicy().hasHeightForWidth());
        lastImagePreviewLabel_2->setSizePolicy(sizePolicy1);
        lastImagePreviewLabel_2->setFrameShape(QFrame::Box);

        gridLayout_7->addWidget(lastImagePreviewLabel_2, 0, 0, 1, 1);

        stackedWidget->addWidget(previewPage_2);
        takeImageButtonClient = new QPushButton(centralwidget);
        takeImageButtonClient->setObjectName(QStringLiteral("takeImageButtonClient"));
        takeImageButtonClient->setEnabled(false);
        takeImageButtonClient->setGeometry(QRect(120, 450, 901, 28));
        camera->setCentralWidget(centralwidget);
        menubar = new QMenuBar(camera);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 1141, 26));
        camera->setMenuBar(menubar);
        statusbar = new QStatusBar(camera);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        camera->setStatusBar(statusbar);

        retranslateUi(camera);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(camera);
    } // setupUi

    void retranslateUi(QMainWindow *camera)
    {
        camera->setWindowTitle(QApplication::translate("camera", "MainWindow", Q_NULLPTR));
        lastImagePreviewLabel_2->setText(QString());
        takeImageButtonClient->setText(QApplication::translate("camera", "Capture Photo", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class camera: public Ui_camera {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CAMERA_H

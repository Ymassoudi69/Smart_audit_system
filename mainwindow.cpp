#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "client.h"
#include "smtp.h"
#include <QDebug>
#include <QSqlQuery>
#include<QSqlQueryModel>
#include<QTableView>
#include <QMessageBox>
#include <QTableWidget>
#include<QtDebug>
#include <QLineEdit>
#include <QValidator>
#include <QDialog>
#include <QtPrintSupport/QPrintDialog>
#include <QtPrintSupport/QPrinter>
#include <QFileDialog>
#include <QPdfWriter>
#include <QPainter>
#include <qcustomplot.h>
#include <QSqlRecord>
#include "camera.h"


class NoNumberValidator : public QValidator {
public:
    QValidator::State validate(QString &input, int &pos) const override {
        Q_UNUSED(pos);
        for (const QChar &ch : input) {
            if (ch.isDigit()) {
                return QValidator::Invalid;
            }
        }

        return QValidator::Acceptable;
    }
};

MainWindow::MainWindow(QWidget * parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    NoNumberValidator *validator = new NoNumberValidator;
         ui->Nom_3->setValidator(validator);
          ui->Prenom_3->setValidator(validator);
          ui->adresse_3->setValidator(validator);
          ui->Email_3->setValidator(new QRegularExpressionValidator(QRegularExpression(R"([a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})"), ui->Email_3));
          ui->idClient_3->setValidator(new QIntValidator(0,99999999,this));
          //ui->idProduit_3->setValidator(validator);
          ui->cin_3->setValidator(new QIntValidator(0,99999999,this));
          ui->num_3->setValidator(new QIntValidator(0,99999999,this));

          connect(ui->sendBtn, SIGNAL(clicked()),this, SLOT(sendMail()));
         // connect(ui->browseBtn, SIGNAL(clicked()), this, SLOT(browse()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_Ajouter_clicked()
{
     Client b;
     b.ajouter(ui);

}


void MainWindow::on_afficher3_clicked()
{
    Client b;
    b.AfficherTable(ui);
}

void MainWindow::on_Supprimer_clicked()
{
    Client b;
    b.supprimer(ui);
    b.AfficherTable(ui);
}
void MainWindow::on_Refrachir_2_clicked()
{
    Client b;
    b.AfficherTable(ui);

}

void MainWindow::on_viewclient3_activated(const QModelIndex &index)
{

    int selectedRow = index.row();
       int ID_CLIENT = ui->viewclient3->model()->data(ui->viewclient3->model()->index(selectedRow, 0)).toInt();
       QSqlQuery q;
       ui->id_clientD->setText(QString::number(ID_CLIENT));

       QMessageBox confirmationBox;
       confirmationBox.setText("Voulez-vous vraiment supprimer le client avec l'ID " + QString::number(ID_CLIENT) + " ?");
       confirmationBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
       confirmationBox.setDefaultButton(QMessageBox::No);

       int confirmationResult = confirmationBox.exec();

       if (confirmationResult == QMessageBox::Yes) {
           Client b;
           if (b.supprimer(ui)) {
               b.AfficherTable(ui);
               ui->id_clientD->clear();
           }
       }
}

void MainWindow::on_Modifier_clicked()
{
    Client b ;
    b.Modifier(ui);
}

void MainWindow::on_Refrachir_clicked()

{
    Client b;
    b.AfficherTable(ui);
        if (ui->viewclient2->model()->rowCount() > 0) {
            QModelIndex firstIndex = ui->viewclient2->model()->index(0, 0);
            ui->viewclient2->setCurrentIndex(firstIndex);
            on_viewclient2_clicked(firstIndex);
        }


}

void MainWindow::on_viewclient2_clicked(const QModelIndex &index)
{
       int selectedRow = index.row();
        int ID_CLIENT = ui->viewclient2->model()->data(ui->viewclient2->model()->index(selectedRow, 0)).toInt();

        QSqlQuery q;
        q.prepare("SELECT * FROM CLIENTS WHERE ID_CLIENT = :idClient");
        q.bindValue(":idClient", ID_CLIENT);

        if (q.exec() && q.first()) {
            ui->idClient->setText(q.value(0).toString());
            ui->Nom->setText(q.value(1).toString());
            ui->Prenom->setText(q.value(2).toString());
            ui->Email->setText(q.value(3).toString());
            ui->Adresse->setText(q.value(4).toString());
            ui->idProduit->setText(q.value(5).toString());
            ui->cin->setText(q.value(6).toString());
            ui->num->setText(q.value(7).toString());
        }
}

void MainWindow::on_Recherche_2_clicked()
{
    QString valeur = ui->id_clientR_2->text();
       Client *b = new Client();
       QSqlQueryModel *resultModel = b->rechercherClient(valeur);

       if (resultModel->rowCount() > 0) {
           ui->ViewClientRecherche->setModel(resultModel);
       } else {
           // Gérer le cas où le client n'a pas été trouvé
           QMessageBox msgBox;
           msgBox.setText("Client non trouvé.");
           msgBox.exec();
       }
}

void MainWindow::on_trier_clicked()
{
    Client *b= new Client();
    ui->triClient->setModel(b->trierClient());
}

void MainWindow::sendmail()
{
    smtp* smtp = new class smtp (ui->uname->text(), ui->paswd->text(), ui->server->text(),ui->port->text().toUShort());
        connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));

            smtp->sendMaile(ui->uname->text(), ui->rcpt->text() , ui->subject->text(),ui->msg->toPlainText());

}
void MainWindow::mailSent(QString status)
{
    if(status == "Message sent")
        QMessageBox::information( nullptr, tr( "Qt Simple SMTP client" ), tr( "Message sent!\n\n" ) );
}


void MainWindow::on_sendBtn_clicked()
{
    sendmail();
}


void MainWindow::on_ecxporter_en_pdf_clicked()
{

       QPrinter printer;
       QPrintDialog dialog(&printer, this);

       if (dialog.exec() == QDialog::Accepted) {

           printer.setPageSize(QPrinter::A4);
           printer.setOrientation(QPrinter::Landscape);

           QPainter painter(&printer);
           painter.begin(&printer);

           QRect pageRect = printer.pageRect();
           painter.setViewport(pageRect.x(), pageRect.y(), pageRect.width(), pageRect.height());
           painter.setWindow(pageRect);


           QString imagePath = QDir::homePath() + "c:/Users/chino info/Desktop/Projet/img/logo.png";
           QImage image(imagePath);
           if (!image.isNull()) {

               QSize imageSize(100, 100);
               QPoint imagePos(50, 50);
               QRect imageRect(imagePos, imageSize);
               painter.drawImage(imageRect, image);
           }

           QSqlQueryModel *model = qobject_cast<QSqlQueryModel *>(ui->triClient->model());

           const int margin = 180;
           const int headerHeight = 50;
           int rowHeight = 20;
           int columnWidth = 150;
           int y = margin + headerHeight;


           for (int col = 0; col < model->columnCount(); ++col) {
               QString headerText = model->headerData(col, Qt::Horizontal).toString();
               painter.drawText(margin + col * columnWidth, y, columnWidth, headerHeight, Qt::AlignCenter, headerText);
           }
           y += headerHeight;


           for (int row = 0; row < model->rowCount(); ++row) {
               for (int col = 0; col < model->columnCount(); ++col) {
                   QString cellValue = model->data(model->index(row, col)).toString();
                   painter.drawText(margin + col * columnWidth, y, columnWidth, rowHeight, Qt::AlignLeft | Qt::AlignVCenter, cellValue);
               }
               y += rowHeight;
           }

           painter.end();
       }
}


void MainWindow::on_camera_clicked()
{
    c= new camera();
    c->show();
}

void MainWindow::on_play_clicked()
{
    player= new QMediaPlayer;
    vw=new QVideoWidget;

    auto filename=QFileDialog::getOpenFileName(this,"import mp4 file",QDir::rootPath(),"Excel Files(*.JPG)");


    player->setVideoOutput(vw);
    player->setMedia(QUrl::fromLocalFile(filename));
    vw->setGeometry(100,100,300,400);
    vw->show();
    player->play();
}

void MainWindow::on_stop_clicked()
{
    player->stop();
    vw->close();
}

QVector<double> MainWindow::Statistique_type()
{
    QSqlQuery q;
    QVector<double> stat(2);
    stat[0]=0;
    stat[1]=0;

    q.prepare("SELECT CIN FROM CLIENTS WHERE CIN>10000000");
    q.exec();
    while (q.next())
    {
        stat[0]++;
    }
    q.prepare("SELECT CIN FROM CLIENTS WHERE CIN>20000000");
    q.exec();
    while (q.next())
    {
        stat[1]++;
    }

    return stat;
}
void MainWindow::makePlot_type()
{
    // prepare data:
    QVector<double> x3(2), y3(20);
    for (int i=0; i<x3.size(); ++i)
    {
      x3[i] = i+1;

    }
    for (int i=0; i<y3.size(); ++i)
    {
      y3[i] = i+1;

    }

    QCPBars *bars1 = new QCPBars(ui->customPlot->xAxis, ui->customPlot->yAxis);
    bars1->setWidth(2/(double)x3.size());
    bars1->setData(x3, MainWindow::Statistique_type());
    bars1->setPen(Qt::NoPen);
    bars1->setBrush(QColor(200, 40, 60, 170));
    ui->customPlot->replot();
    // move bars above graphs and grid below bars:
    ui->customPlot->addLayer("abovemain", ui->customPlot->layer("main"), QCustomPlot::limAbove);
    ui->customPlot->addLayer("belowmain", ui->customPlot->layer("main"), QCustomPlot::limBelow);
    ui->customPlot->xAxis->grid()->setLayer("belowmain");
    ui->customPlot->yAxis->grid()->setLayer("belowmain");

    // set some pens, brushes and backgrounds:
    QVector<double> Ticks;
    Ticks<<1<<2;
    QVector<QString> labels;
    labels<<"plus 30 ans " <<" moins 30 ans";
    QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
    textTicker->addTicks(Ticks,labels);
    ui->customPlot->xAxis->setTicker(textTicker);
    ui->customPlot->xAxis->setSubTicks(false);
    ui->customPlot->xAxis->setTickLength(0,4);
    ui->customPlot->xAxis->setBasePen(QPen(Qt::white, 1));
    ui->customPlot->yAxis->setBasePen(QPen(Qt::white, 1));
    ui->customPlot->xAxis->setTickPen(QPen(Qt::transparent, 1));
    ui->customPlot->yAxis->setTickPen(QPen(Qt::white, 1));
    ui->customPlot->xAxis->setSubTickPen(QPen(Qt::transparent, 1));
    ui->customPlot->yAxis->setSubTickPen(QPen(Qt::transparent, 1));
    ui->customPlot->xAxis->setTickLabelColor(Qt::white);
    ui->customPlot->yAxis->setTickLabelColor(Qt::white);
    ui->customPlot->xAxis->grid()->setPen(QPen(QColor(140, 140, 140), 1, Qt::DotLine));
    ui->customPlot->yAxis->grid()->setPen(QPen(QColor(140, 140, 140), 1, Qt::DotLine));
    ui->customPlot->xAxis->grid()->setSubGridPen(QPen(QColor(80, 80, 80), 1, Qt::DotLine));
    ui->customPlot->yAxis->grid()->setSubGridPen(QPen(QColor(80, 80, 80), 1, Qt::DotLine));
    ui->customPlot->xAxis->grid()->setSubGridVisible(true);
    ui->customPlot->yAxis->grid()->setSubGridVisible(true);
    ui->customPlot->xAxis->grid()->setZeroLinePen(Qt::NoPen);
    ui->customPlot->yAxis->grid()->setZeroLinePen(Qt::NoPen);
    ui->customPlot->xAxis->setUpperEnding(QCPLineEnding::esSpikeArrow);
    ui->customPlot->yAxis->setUpperEnding(QCPLineEnding::esSpikeArrow);
    QLinearGradient plotGradient;
    plotGradient.setStart(0, 0);
    plotGradient.setFinalStop(0, 350);
    plotGradient.setColorAt(0, QColor(10, 50, 80));
    plotGradient.setColorAt(1, QColor(10, 20, 50));
    ui->customPlot->setBackground(plotGradient);
    QLinearGradient axisRectGradient;
    axisRectGradient.setStart(0, 0);
    axisRectGradient.setFinalStop(0, 350);
    axisRectGradient.setColorAt(0, QColor(10, 50, 80));
    axisRectGradient.setColorAt(1, QColor(0, 0, 30));
    ui->customPlot->axisRect()->setBackground(axisRectGradient);
    ui->customPlot->rescaleAxes();
    ui->customPlot->xAxis->setRange(0, 7);
    ui->customPlot->yAxis->setRange(0, 10);


}

void MainWindow::on_stat_clicked()
{
  MainWindow::makePlot_type();
}



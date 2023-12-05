#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "client.h"
#include "camera.h"
#include "smtp.h"
#include<QtDebug>
#include <QDebug>
#include <QSqlQuery>
#include<QSqlQueryModel>
#include <QTableWidget>
#include<QTableView>
#include <QMessageBox>
#include <QLineEdit>
#include <QValidator>
#include <QDialog>
#include <QtPrintSupport/QPrintDialog>
#include <QtPrintSupport/QPrinter>
#include <QFileDialog>
#include <QPdfWriter>
#include <QPainter>



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


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    NoNumberValidator *validator = new NoNumberValidator;
          ui->NomClient_3->setValidator(validator);
          ui->PrenomClient_3->setValidator(validator);
          ui->adresseClient_3->setValidator(validator);
          ui->EmailClient_3->setValidator(new QRegularExpressionValidator(QRegularExpression(R"([a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})"), ui->EmailClient_3));
          ui->idClient_3->setValidator(new QIntValidator(0,99999999,this));
          ui->cinClient_3->setValidator(new QIntValidator(0,99999999,this));
          ui->numClient_3->setValidator(new QIntValidator(0,99999999,this));
}

MainWindow::~MainWindow()
{
    delete ui;
}

//l'ajout:
void MainWindow:: on_AjouterClient_clicked()
{
    Client b;
    b.AjouterClient(ui);
}

//l'affichage:
void MainWindow:: on_AfficherClient_clicked()
{
    Client b;
    b.AfficherClientTable(ui);
}

//modification:
void MainWindow::on_ModifierClient_clicked()
{
    Client b ;
    b.ModifierClient(ui);
}
void MainWindow:: on_RefrachirClientModifier_clicked()
{
    Client b;
    b.AfficherClientTable(ui);
        if (ui->ViewClientModifier->model()->rowCount() > 0) {
            QModelIndex firstIndex = ui->ViewClientModifier->model()->index(0, 0);
            ui->ViewClientModifier->setCurrentIndex(firstIndex);
            on_ViewClientModifier_clicked(firstIndex);
        }
}
void MainWindow::on_ViewClientModifier_clicked(const QModelIndex &index)
{
    int selectedRow = index.row();
     int ID_CLIENT = ui->ViewClientModifier->model()->data(ui->ViewClientModifier->model()->index(selectedRow, 0)).toInt();

     QSqlQuery q;
     q.prepare("SELECT * FROM CLIENTS WHERE ID_CLIENT = :idClient");
     q.bindValue(":idClient", ID_CLIENT);

     if (q.exec() && q.first()) {
         ui->idClient->setText(q.value(0).toString());
         ui->NomClient->setText(q.value(1).toString());
         ui->PrenomClient->setText(q.value(2).toString());
         ui->EmailClient->setText(q.value(3).toString());
         ui->AdresseClient->setText(q.value(4).toString());
         ui->idProduitClient->setText(q.value(5).toString());
         ui->cinClient->setText(q.value(6).toString());
         ui->numClient->setText(q.value(7).toString());
     }
}

//suppression:
 void MainWindow::on_SupprimerClient_clicked()
 {
     Client b;
     b.SupprimerClient(ui);
     b.AfficherClientTable(ui);
 }

void MainWindow::on_RefrachirClient_clicked()
{
    Client b;
    b.AfficherClientTable(ui);
}

void MainWindow::on_ViewClientSupprimer_activated(const QModelIndex &index)
{
    int selectedRow = index.row();
       int ID_CLIENT = ui->ViewClientSupprimer->model()->data(ui->ViewClientSupprimer->model()->index(selectedRow, 0)).toInt();
       QSqlQuery q;
       ui->id_clientD->setText(QString::number(ID_CLIENT));

       QMessageBox confirmationBox;
       confirmationBox.setText("Voulez-vous vraiment supprimer le client avec l'ID " + QString::number(ID_CLIENT) + " ?");
       confirmationBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
       confirmationBox.setDefaultButton(QMessageBox::No);

       int confirmationResult = confirmationBox.exec();

       if (confirmationResult == QMessageBox::Yes) {
           Client b;
           if (b.SupprimerClient(ui)) {
               b.AfficherClientTable(ui);
               ui->id_clientD->clear();
           }
       }
}

//recherche:
 void MainWindow::on_RechercheClient_clicked()
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

//tri et exportation on pdf:
void MainWindow:: on_trierClient_clicked()
{
    Client *b= new Client();
    ui->ViewTriClient->setModel(b->trierClient());
}

void MainWindow::on_ecxporter_en_pdf_client_clicked()
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


        QString imagePath = QDir::homePath() + "C:/Users/chino info/Desktop/Projet/img/logo.png";
        QImage image(imagePath);
        if (!image.isNull()) {

            QSize imageSize(100, 100);
            QPoint imagePos(50, 50);
            QRect imageRect(imagePos, imageSize);
            painter.drawImage(imageRect, image);
        }

        QSqlQueryModel *model = qobject_cast<QSqlQueryModel *>(ui->ViewTriClient->model());

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


//statistique:
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

void MainWindow::on_statClient_clicked()
{
 MainWindow::makePlot_type();
}


//image:
void MainWindow::on_cameraClient_clicked()
{
    c= new camera();
    c->show();
}

void MainWindow::on_playClient_clicked()
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

void MainWindow::on_stopClient_clicked()
{
    player->stop();
    vw->close();
}

//mailing:
void   MainWindow::sendMail()
{
    Smtp* smtp = new Smtp("amira.jmaiel@esprit.tn",ui->mail_passClient->text(), "smtp.gmail.com");
    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));

    if( !files.isEmpty() )
        smtp->sendMail("amira.jmaiel@esprit.tn", ui->rcptClient->text() , ui->subjectClient->text(),ui->msgClient->toPlainText(), files );
    else
        smtp->sendMail("amira.jmaiel.tn", ui->rcptClient->text() , ui->subjectClient->text(),ui->msgClient->toPlainText());
}
void   MainWindow::mailSent(QString status)
{

    if(status == "Message sent")
        QMessageBox::warning( nullptr, tr( "Qt Simple SMTP client" ), tr( "Message sent!\n\n" ) );
    ui->rcptClient->clear();
    ui->subjectClient->clear();
    ui->fileClient->clear();
    ui->msgClient->clear();
    ui->mail_passClient->clear();
}


void MainWindow::on_browseBtnClient_clicked()
{

    files.clear();
    QFileDialog dialog(this);
    dialog.setDirectory(QDir::homePath());
    dialog.setFileMode(QFileDialog::ExistingFiles);

    if (dialog.exec())
        files = dialog.selectedFiles();

    QString fileListString;
    foreach(QString file, files)
        fileListString.append( "\"" + QFileInfo(file).fileName() + "\" " );

    ui->fileClient->setText( fileListString );
}

void MainWindow::on_sendBtn_Client_clicked()
{
    sendMail();
}

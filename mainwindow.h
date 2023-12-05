#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "camera.h"
#include <QMainWindow>
#include <QMediaPlayer>
#include <QVideoWidget>



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    //l'ajout:
    void on_AjouterClient_clicked();

    //l'affichage:
    void on_AfficherClient_clicked();

    //modification:
    void on_RefrachirClientModifier_clicked();
    void on_ModifierClient_clicked();
    void on_ViewClientModifier_clicked(const QModelIndex &index);

    //suppression:
    void on_SupprimerClient_clicked();
    void on_RefrachirClient_clicked();
    void on_ViewClientSupprimer_activated(const QModelIndex &index);

    //recherche:
    void on_RechercheClient_clicked();

    //tri et exportation en pdf:
    void on_trierClient_clicked();
    void on_ecxporter_en_pdf_client_clicked();

    //statistique:
    void makePlot_type ();
    QVector<double> Statistique_type();
    void on_statClient_clicked();

    //mailing
    void sendMail();
    void mailSent(QString);
    void on_browseBtnClient_clicked();
    void on_sendBtn_Client_clicked();

    //image:
    void on_cameraClient_clicked();
    void on_playClient_clicked();
    void on_stopClient_clicked();




private:
    Ui::MainWindow *ui;
    QStringList files;
    camera *c;
    QMediaPlayer* player;
    QVideoWidget* vw;
    QString mail_pass="221JFT6377";
};

#endif // MAINWINDOW_H

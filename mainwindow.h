
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
    explicit MainWindow (QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pdf_clicked();

    void on_pushButton_clicked();

    void on_Ajouter_clicked();

    void on_afficher3_clicked();

    void on_Supprimer_clicked();

    void on_Modifier_clicked();

    void on_Recherche_2_clicked();

    void on_trier_clicked();

    void on_Refrachir_clicked();

    void on_viewclient2_clicked(const QModelIndex &index);

    void on_viewclient3_activated(const QModelIndex &index);

    void on_Refrachir_2_clicked();

    void sendMail();

    void mailSent(QString);

    void browse();

    void on_ecxporter_en_pdf_clicked();

    void on_sendBtn_clicked();

    void on_camera_clicked();

    void on_play_clicked();

    void on_stop_clicked();

    void on_customPlot_customContextMenuRequested(const QPoint &pos);
    void makePlot_type ();
    QVector<double> Statistique_type();
    void on_stat_clicked();

    void sendmail();

    //void on_stat_clicked();

private:
    QMediaPlayer* player;
    QVideoWidget* vw;
    Ui::MainWindow *ui;
    QStringList files;
    QString mail_pass="221JFT6377";
    camera *c;
};

#endif // MAINWINDOW_H

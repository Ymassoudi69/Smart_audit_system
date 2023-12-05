#ifndef CLIENT_H
#define CLIENT_H
#include <Qstring>
#include <iostream>
#include "ui_MainWindow.h"
#include "MainWindow.h"
#include <QtSql/QSqlQueryModel>

class Client
{
private:
    QString ID_CLIENT;
    QString NOM;
    QString PRENOM;
    QString EMAIL;
    QString ADRESSE;
    QString IDPRODUIT;
    int  CIN ;
    int NUM_TEL;

public:
    //Constructeurs
    Client();
    Client(QString, QString,QString,QString, QString,QString,int ,int );


    bool AjouterClient(Ui::MainWindow*ui);
    void AfficherClientTable(Ui::MainWindow *ui);
    bool ModifierClient(Ui::MainWindow *ui);
    bool SupprimerClient(Ui::MainWindow *ui);
    QSqlQueryModel * rechercherClient(QString ID_CLIENT);
    QSqlQueryModel * trierClient();
};

#endif // CLIENT_H

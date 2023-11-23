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


    bool ajouter(Ui::MainWindow*ui);
    bool supprimer(Ui::MainWindow *ui);
    void AfficherTable(Ui::MainWindow *ui);
    bool Modifier(Ui::MainWindow *ui);
    QSqlQueryModel * rechercherClient(QString ID_CLIENT);
    QSqlQueryModel * trierClient();


};

#endif // CLIENT_H

#include "client.h"
#include <QSqlQuery>
#include <QDebug>
#include<QSqlQueryModel>
#include <QMessageBox>
#include <QSqlError>
#include <QLineEdit>
#include <QValidator>

Client::Client()
{

    ID_CLIENT="";
    NOM="";
    PRENOM="";
    EMAIL="";
    ADRESSE="";
    IDPRODUIT="";
    CIN=0;
    NUM_TEL=0;

}

Client::Client(QString ID_CLIENT , QString NOM ,QString PRENOM ,QString EMAIL , QString ADRESSE ,QString IDPRODUIT ,int CIN  ,int NUM_TEL)
{
    this->ID_CLIENT=ID_CLIENT;
    this->NOM=NOM;
    this->PRENOM=PRENOM;
    this->EMAIL=EMAIL;
    this->ADRESSE=ADRESSE;
    this->IDPRODUIT=IDPRODUIT;
     this->CIN=CIN;
    this->NUM_TEL=NUM_TEL;
}

bool Client::ajouter(Ui::MainWindow *ui)
{
    QSqlQuery q;


        q.prepare("INSERT into CLIENTS(ID_CLIENT ,NOM ,PRENOM ,EMAIL ,ADRESSE ,IDPRODUIT ,CIN  , NUM_TEL) VALUES"
                  " (:idclients ,:noms,:prenoms, :emails , :adresses , :idproduits ,:cins ,:numtels)");

         q.bindValue(":idclients",ui->idClient_3->text());
         q.bindValue(":noms",ui->Nom_3->text());
         q.bindValue(":prenoms",ui->Prenom_3->text());
         q.bindValue(":emails",ui->Email_3->text());
         q.bindValue(":adresses",ui->adresse_3->text());
         q.bindValue(":idproduits",ui->idProduit_3->text());
         q.bindValue(":cins",ui->cin_3->text());
         q.bindValue(":numtels",ui->num_3->text());

         if (q.exec())
         {
             std::cout << "ca marche ! " << std::endl;

             QMessageBox msgBox ;
                     msgBox.setText("client ajouter ");
                     msgBox.exec();
              ui->idClient_3->clear();
              ui->Nom_3->clear();
              ui->Prenom_3->clear();
              ui->Email_3->clear();
              ui->adresse_3->clear();
              ui->cin_3->clear();
              ui->num_3->clear();
              ui->idProduit_3->clear();







             return true ;
         }
         else
         {
             std::cout<< "Ça marche pas ! :(" <<std::endl;

             QMessageBox msgBox ;
                     msgBox.setText("client n'est pas ajouté ");
                     msgBox.exec();
                     return false;
         }

    }


void Client::AfficherTable(Ui::MainWindow *ui)
{
    QSqlQuery q;
    QSqlQueryModel *modal=new QSqlQueryModel();
    q.prepare("select * from CLIENTS");
    q.exec();
    modal->setQuery(q);
    ui->viewClient->setModel(modal);
    ui->viewclient2->setModel(modal);
    ui->viewclient3->setModel(modal);
    ui->ViewClientRecherche->setModel(modal);
    ui->triClient->setModel(modal);
}

bool Client::supprimer(Ui::MainWindow *ui)
{

        QSqlQuery q;

        q.prepare("DELETE FROM CLIENTS WHERE ID_CLIENT = :idClient");
        q.bindValue(":idClient", ui->id_clientD->text());

        if (q.exec()) {
            if (q.numRowsAffected() > 0) {
                QMessageBox msgBox;
                msgBox.setText("Le client a été supprimé.");
                msgBox.exec();
                return true;
            } else {
                QMessageBox msgBox;
                msgBox.setText("Le client n'existe pas, il n'a pas été supprimé.");
                msgBox.exec();
                return false;
            }
        } else {
            QMessageBox msgBox;
            msgBox.setText("Une erreur s'est produite lors de la suppression du client.");
            msgBox.exec();
            return false;
        }


}

   bool Client::Modifier(Ui::MainWindow *ui)
{
    QSqlQuery q;
    q.prepare("UPDATE CLIENTS SET ID_CLIENT=:idClientt,NOM=:nomm ,PRENOM=:prenomm ,EMAIL=:emaill ,ADRESSE=:adressee ,IDPRODUIT=:idproduitt ,CIN=:cinn  , NUM_TEL=:numtell where ID_CLIENT=:idClientt" );
    q.bindValue(":idClientt",ui->idClient->text());
    q.bindValue(":nomm",ui->Nom->text());
    q.bindValue(":prenomm",ui->Prenom->text());
    q.bindValue(":emaill",ui->Email->text());
    q.bindValue(":adressee",ui->Adresse->text());
    q.bindValue(":idproduitt",ui->idProduit->text());
    q.bindValue(":cinn",ui->cin->text());
    q.bindValue(":numtell",ui->num->text());
    if(q.exec())
    {
       if (    q.exec())
        {
            std::cout << "Ça marche !" << std::endl;

            QMessageBox msgBox ;
                    msgBox.setText("les informations du client ont été modifié ");
                    msgBox.exec();
            return true ;
        }
        else
        {
            std::cout<< "Ça marche pas ! :(" <<std::endl;

            QMessageBox msgBox ;
                    msgBox.setText("Le client n'existe pas,les informations du client n'ont pas modifié ");
                    msgBox.exec();
                    return false;
        }

}
   }


QSqlQueryModel * Client::rechercherClient(QString ID_CLIENT)
{
        QSqlQueryModel *model = new QSqlQueryModel();
            QSqlQuery query;
            query.prepare("SELECT * FROM CLIENTS WHERE ID_CLIENT = :idClient");
            query.bindValue(":idClient", ID_CLIENT);
            query.exec();
            model->setQuery(query);
            return model;
}


QSqlQueryModel *Client::trierClient()
{
  QSqlQueryModel *model= new QSqlQueryModel() ;
  model->setQuery("select * from CLIENTS order by NOM ASC");
  return model ;
}


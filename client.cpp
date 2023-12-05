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

//l'ajout:
bool Client::AjouterClient(Ui::MainWindow *ui)
{
    QSqlQuery q;

        q.prepare("INSERT into CLIENTS(ID_CLIENT ,NOM ,PRENOM ,EMAIL ,ADRESSE ,IDPRODUIT ,CIN  , NUM_TEL) VALUES"
                  " (:idclients ,:noms,:prenoms, :emails , :adresses , :idproduits ,:cins ,:numtels)");

         q.bindValue(":idclients",ui->idClient_3->text());
         q.bindValue(":nomsclients",ui->NomClient_3->text());
         q.bindValue(":prenomsclients",ui->PrenomClient_3->text());
         q.bindValue(":emailsclients",ui->EmailClient_3->text());
         q.bindValue(":adressesclients",ui->adresseClient_3->text());
         q.bindValue(":idproduitsclients",ui->idProduitClient_3->text());
         q.bindValue(":cinsclients",ui->cinClient_3->text());
         q.bindValue(":numtelsclients",ui->numClient_3->text());

         if (q.exec())
         {
             std::cout << "ca marche ! " << std::endl;

             QMessageBox msgBox ;
                     msgBox.setText("client ajouter ");
                     msgBox.exec();
              ui->idClient_3->clear();
              ui->NomClient_3->clear();
              ui->PrenomClient_3->clear();
              ui->EmailClient_3->clear();
              ui->adresseClient_3->clear();
              ui->cinClient_3->clear();
              ui->numClient_3->clear();
              ui->idProduitClient_3->clear();

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

//l'affichage:
void Client::AfficherClientTable(Ui::MainWindow *ui)
{
    QSqlQuery q;
    QSqlQueryModel *modal=new QSqlQueryModel();
    q.prepare("select * from CLIENTS");
    q.exec();
    modal->setQuery(q);
    ui->ViewClientAfficher->setModel(modal);
    ui->ViewClientModifier->setModel(modal);
    ui->ViewClientSupprimer->setModel(modal);
    ui->ViewClientRecherche->setModel(modal);
    ui->ViewTriClient->setModel(modal);
}

//recherche:
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

//modification:
bool Client::ModifierClient(Ui::MainWindow *ui)
{
 QSqlQuery q;
 q.prepare("UPDATE CLIENTS SET ID_CLIENT=:idClientt,NOM=:nommClient ,PRENOM=:prenommClient ,EMAIL=:emaillClient ,ADRESSE=:adresseeClient ,IDPRODUIT=:idproduittClient ,CIN=:cinnClient  , NUM_TEL=:numtellClient where ID_CLIENT=:idClientt" );
 q.bindValue(":idClientt",ui->idClient->text());
 q.bindValue(":nommClient",ui->NomClient->text());
 q.bindValue(":prenommClient",ui->PrenomClient->text());
 q.bindValue(":emaillClient",ui->EmailClient->text());
 q.bindValue(":adresseeClient",ui->AdresseClient->text());
 q.bindValue(":idproduittClient",ui->idProduitClient->text());
 q.bindValue(":cinnClient",ui->cinClient->text());
 q.bindValue(":numtellClient",ui->numClient->text());
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

//suppression:
bool Client::SupprimerClient(Ui::MainWindow *ui)
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


//tri:
QSqlQueryModel *Client::trierClient()
{
  QSqlQueryModel *model= new QSqlQueryModel() ;
  model->setQuery("select * from CLIENTS order by NOM ASC");
  return model ;
}

//recherche:
QSqlQueryModel *rechercherClient(QString ID_CLIENT)
{
        QSqlQueryModel *model = new QSqlQueryModel();
            QSqlQuery query;
            query.prepare("SELECT * FROM CLIENTS WHERE ID_CLIENT = :idClient");
            query.bindValue(":idClient", ID_CLIENT);
            query.exec();
            model->setQuery(query);
            return model;
}

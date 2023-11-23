#include "connection.h"
#include <QDebug>

Connection::Connection()
{

}

bool Connection::createconnect()
{bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("projet2A30");
db.setUserName("amira1");//inserer nom de l'utilisateur
db.setPassword("amira");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;

    return  test;
}

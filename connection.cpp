#include "connection.h"
#include <QDebug>


Connection::Connection()
{

}

bool Connection::createconnect()
{bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("projet2A30");
db.setUserName("amira1");
db.setPassword("amira");

if (db.open())
test=true;

    return  test;
}

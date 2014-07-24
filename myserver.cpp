#include "myserver.h"
#include <QDebug>

MyServer::MyServer(QObject *parent) :
        QObject(parent)
{
    server = new QTcpServer(this);

    if(!server->listen(QHostAddress::Any, 30000))
    {
        qDebug() << "Server could not start!";
    }
    else
    {
        qDebug() << "Server started";
    }
}

void MyServer::DoServerResponse(seaobject* sm, seaobject* tgt)
{
    QTcpSocket *socket = server->nextPendingConnection();

    socket->waitForReadyRead(1000);

    QByteArray requestWord = socket->readAll();

    double dataMarker = ConvertQByteArray2Double(requestWord);

    double outData;

    if(dataMarker == 1) // the socket has requested tgt bearing
    {
        outData = tgt->GetCurrentBearing();
    }
    if(dataMarker == 2) //the socket has requested sm heading
    {
        outData = sm->GetCurrentHdg();
    }

    if (dataMarker == 3)//the socket has requested sm speed
    {
        outData = sm->GetCurrentSpd();
    }

    QByteArray txWord = ConvertDouble2QByteArray(outData);

    socket->write(txWord);

    socket->waitForBytesWritten(3000);

    socket->close();
}

QByteArray MyServer::ConvertDouble2QByteArray(double outData)
{
        QString tempString;

        tempString.setNum(outData);

        return tempString.toUtf8();

}

double MyServer::ConvertQByteArray2Double(QByteArray rxWord)
{
    bool arg2;

    return rxWord.toDouble(&arg2);
}


#include "myudp.h"
#include <QDebug>

MyUDP::MyUDP(QObject* parent):QObject (parent)
{
    socket = new QUdpSocket(this);

    socket->bind(QHostAddress::LocalHost,5678);

    connect(socket,SIGNAL(readyRead()),this,SLOT(ReadData()));

}

void MyUDP::WriteData()
{
    QByteArray msg;

    msg.append("Hello");

    socket->writeDatagram(msg,QHostAddress::LocalHost,5678);

}

void MyUDP::ReadData()
{
    QByteArray buffer;

    buffer.resize(socket->pendingDatagramSize());

    QHostAddress sender;

    quint16 port;

    socket->readDatagram(buffer.data(),
                         buffer.size(),
                         &sender,
                         &port);

    qDebug() << "Message From" << sender.toString();

    qDebug() << "With Port No:" << port;

    qDebug() << "Message" << buffer;
}

#ifndef MYSERVER_H
#define MYSERVER_H

#include <QObject>
#include <QDebug>
#include <QTcpServer>
#include <QTcpSocket>
#include "seaobject.h"


class MyServer : public QObject
{
    Q_OBJECT
public:
    explicit MyServer(QObject *parent = 0);

    QTcpServer *server;
    void DoServerResponse(seaobject*, seaobject*);

public slots:



private:


    QByteArray ConvertDouble2QByteArray(double);

    double ConvertQByteArray2Double(QByteArray);

};

#endif // MYSERVER_H

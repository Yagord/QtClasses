#ifndef SOCKETTEST_H
#define SOCKETTEST_H

#include <QObject>
#include <QTcpSocket>
#include <QDebug>

class SocketTest : public QObject
{
public:
    SocketTest();

    double QueryServer(int dataMarker);

private:

    QTcpSocket *sonarSocket1;

    QByteArray ConvertDouble2QByteArray(double);

    double ConvertQByteArray2Double(QByteArray);

};

#endif // SOCKETTEST_H

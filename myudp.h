#ifndef MYUDP_H
#define MYUDP_H

#include <QObject>
#include <QUdpSocket>

class MyUDP: public QObject
{
    Q_OBJECT

public:
    MyUDP(QObject *parent = 0);
    void SetPortnumber(qunit)

    void WriteData();

public slots:
    void ReadData();
private:
    QUdpSocket *socket;

};

#endif // MYUDP_H

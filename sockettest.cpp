#include "sockettest.h"

SocketTest::SocketTest()
{
}

double SocketTest::QueryServer(int dataMarker)
{
    //connect

    sonarSocket1 = new QTcpSocket(this);

    sonarSocket1->connectToHost("localhost",30000);

    if (sonarSocket1->waitForConnected(3000))
    {
        //follow actions for connected...

        qDebug() << "Connected....";

        //send a number....

        //double dataNeeded = 1; // target bearing is needed

        //convert QString to char*

        QByteArray txWord = ConvertDouble2QByteArray(dataMarker);

        sonarSocket1->write(txWord);

        sonarSocket1->waitForBytesWritten(1000);

        sonarSocket1->waitForReadyRead(1000);

        QByteArray rxedData = sonarSocket1->readAll();

        double valueRxed = ConvertQByteArray2Double(rxedData);

        sonarSocket1->close();

        return valueRxed;

    }
    else
    {
        qDebug() << "Not Connected...";

        return -1;
    }

}


QByteArray SocketTest::ConvertDouble2QByteArray(double outData)
{
        QString tempString;

        tempString.setNum(outData);

        return tempString.toUtf8();

}

double SocketTest::ConvertQByteArray2Double(QByteArray rxWord)
{
    bool arg2;

    return rxWord.toDouble(&arg2);
}

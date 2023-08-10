#include "client.h"
#include "ui_client.h"
Client::Client(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Client)
{
    ui->setupUi(this);
    socket = new QTcpSocket();

}

Client::~Client()
{
    delete ui;
}


void Client::on_pushButton_clicked()
{
    socket->connectToHost("127.0.0.1", 8080);
    QRandomGenerator gen;
    id=gen.bounded(1, 65535);
    socket->open(QIODevice::WriteOnly);
    if (socket->isOpen())
    {
        QMessageBox::information(this, "connection info", "success");
     connect(socket, SIGNAL(readyRead()), SLOT(slotreadyRead()));
    }
    else
    {
         QMessageBox::information(this, "connection info", "unsuccess");
    }

}

void Client::slotreadyRead()
{
    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_5_15);
    if (in.status()==QDataStream::Ok){
    QString str;
    in>>str;
    ui->textBrowser->append(str);
    }
    else
      ui->textBrowser->append("Error");


}
void Client::on_lineEdit_returnPressed()
{
    sendToServer(ui->lineEdit->text());
}

void Client::sendToServer(QString str)
{
//    if (socket->isOpen())
//        socket->write(str.toStdString().c_str());
//    else
//        QMessageBox::information(this, "Send information", "can't send");
//    data.clear();
//    QDataStream out(&data, QIODevice::WriteOnly);
//    out.setVersion(QDataStream::Qt_5_15);
//    out<<qint16(0)<<str;
//    socket->write(data);
//    ui->lineEdit->clear();
    QByteArray arr;
    arr.append(str);
    socket->write(arr);
}

void Client::on_pushButton_2_clicked()
{
    sendToServer(ui->lineEdit->text());
}


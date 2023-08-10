#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    server=new QTcpServer(this);
    if (server->listen(QHostAddress::Any, 8080))
    {
        QMessageBox::information(this,"server info", "Server start!");
        QObject::connect(server, SIGNAL(newConnection()), SLOT(client_connect()));
    }
    else
        QMessageBox::information(this, "server info","Server is not start!");

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::client_connect()
{

    while(server->hasPendingConnections())
    {
        socket=server->nextPendingConnection();
        newClient(socket);
    }
}

void MainWindow::newClient(QTcpSocket *socket)
{

    sockets_list.push_back(socket);
    QObject::connect(socket, SIGNAL(readyRead()), SLOT(readData()));
    QString descriptor = "Client descriptor: "+ QString::number(socket->socketDescriptor());
    ui->textEdit->append(descriptor);
}

void MainWindow::readData()
{
//    socket=(QTcpSocket*)sender();
    QDataStream in(socket);
    QString str="";
    in.setVersion(QDataStream::Version::Qt_5_15);
   if(in.status()==QDataStream::Ok){
       qDebug()<<"Read...\n";
       in >> str;
    ui->textEdit->append(str);
    qDebug()<<str;
   }
   else
       qDebug()<<"Error read";

//    QString server_message=QString(socket->readAll());
//    QString message="Client "+QString::number(socket->socketDescriptor())+"::"+QString::fromStdString(server_message.toStdString());
//    ui->textEdit->append(server_message);
}
void MainWindow::on_pushButton_3_clicked()
{
    QString message=ui->lineEdit->text();
    QString reciver=ui->comboBox->currentText();
    if(ui->comboBox_2->currentText()=="ALL")
    {
        foreach(QTcpSocket *socket, sockets_list)
        {
          socket->write(message.toStdString().c_str());
        }
    }
    else
    {
        foreach(QTcpSocket *socket, sockets_list)
        {
            if(socket->socketDescriptor()==reciver.toLongLong())
            {
                socket->write(message.toStdString().c_str());
            }
        }

    }
}


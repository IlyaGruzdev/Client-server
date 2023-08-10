#ifndef CLIENT_H
#define CLIENT_H

#include <QWidget>
#include <QTcpSocket>
#include <QRandomGenerator>
#include <QMessageBox>
QT_BEGIN_NAMESPACE
namespace Ui { class Client; }
QT_END_NAMESPACE

class Client : public QWidget
{
    Q_OBJECT

public:
    Client(QWidget *parent = nullptr);
    ~Client();

private slots:
    void on_pushButton_clicked();
    void slotreadyRead();
    void on_lineEdit_returnPressed();
    void sendToServer(QString str);
    void on_pushButton_2_clicked();

private:
    Ui::Client *ui;
    QTcpSocket *socket;
    QByteArray data;
    qint16 id;
};
#endif // CLIENT_H

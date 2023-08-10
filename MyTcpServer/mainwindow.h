#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>
#include <QByteArray>
#include <QList>
#include <QString>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void client_connect();
    void on_pushButton_3_clicked();
    void readData();
private:
    Ui::MainWindow *ui;
    QTcpServer *server;
    QTcpSocket *socket;
    QList <QTcpSocket *> sockets_list;
    void newClient(QTcpSocket *socket);
};
#endif // MAINWINDOW_H

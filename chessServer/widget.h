#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>
#include <QSqlDatabase>
QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void get_tcpsocket();//获取socket
    void connect_database();//连接数据库
    void remove_disSocket(QTcpSocket*);//删除以删除的socket通讯
    void write_information(QString,QString);
    void marry_rival_slot(QTcpSocket*);
    void close_start_slot(QTcpSocket*);
    void over_game_slot(QTcpSocket*);
    void pieces_move_slot(QTcpSocket*,QVector<QString> vs);
    void down_over_slot(QTcpSocket*,QString);
signals:
    void startGame();

private slots:
    void on_startServerbutton_clicked();

    void on_closeServerButton_clicked();

private:
    //QQueue<>
    QTcpServer* m_server;
    QSqlDatabase db;
    QList<QTcpSocket*>lt;
    QMap<QTcpSocket*,QTcpSocket*> m_pair_socket;//用于记录通讯配对
    QTcpSocket* tmp_socket;
    unsigned int count;
    Ui::Widget *ui;
};
#endif // WIDGET_H

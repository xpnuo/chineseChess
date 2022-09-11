#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QObject>
#include <QThread>
#include <QTcpSocket>
#include <QSqlDatabase>
class MyThread : public QThread
{
    Q_OBJECT
public:
    explicit MyThread(QTcpSocket*,QSqlDatabase*,QString,QObject * parent = nullptr);
    void get_data();//解析数据
    void ifrememberpassword();//查看该ip是否记住密码
    void data_dispose(QVector<QString>&);//数据处理函数
    void dispose_rememberPassword(QVector<QString> &);//记住密码处理函数
    void dispose_createUser(QVector<QString>&);//创建用户处理函数
    void dispose_reception(QVector<QString>&);//确保以登入处理函数
    void dispose_changeImage(QVector<QString>&);//修改头像处理函数
    bool confirmAccount(QVector<QString> & vs);//登入确认处理函数
    void sand_data(QString);//发送信息
    void close_socket();//关闭socket通讯

protected:
    void run() override;

signals:
    void socket_disconnect(QTcpSocket*);//用户断开连接
    void data_information(QString,QString);//信息发送
    void marry_rival(QTcpSocket*);//用户申请匹配对手
    void over_game(QTcpSocket*);//游戏结束
    void close_start(QTcpSocket*);
    void pieces_move(QTcpSocket*,QVector<QString> vs);
    void dowm_over(QTcpSocket*,QString);
private:
    QTcpSocket* m_socket;
    QSqlDatabase* db;
    QString ip;
};

#endif // MYTHREAD_H

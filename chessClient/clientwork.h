#ifndef CLIENTWORK_H
#define CLIENTWORK_H
#define IP "192.168.30.1"
#include <QObject>
#include <QTcpSocket>
class clientWork : public QObject
{
    Q_OBJECT
public:
    clientWork(QTcpSocket*,QObject* parent = nullptr);
    ~clientWork();
    void get_data();
    void marryRival_slot();
    void data_dispose(QVector<QString>&);
    void connect_server();//连接服务器
    void sand_data(QString);//发送数据
    void createUser_slot(QString);//创建一个用户
    void rememberPassword_slot(QString);//记住密码槽函数
    void confirmAccount_slot(QString,QString);//验证账号
    void changeImagePath_slot(QString);//改变用户的头像
    void move_slot(QString);
    void closeStart_slot();
signals:
    void existUser();
    void rememberPassword(QString,QString);
    void marryOk(QString);
    void userInformation(QString,QString,QString,QString);
    void movePieces(QString,QString,QString,QString);
    void disSocket();//敌方退出游戏
    void dowmOver();
private:
    QTcpSocket* m_socket;
};

#endif // CLIENTWORK_H

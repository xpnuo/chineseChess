#include "widget.h"
#include "ui_widget.h"
#include "mythread.h"
#include <QDateTime>
#include <QHostAddress>
#include <QSqlError>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->closeServerButton->setDisabled(true);
    this->count = 0;
    connect_database();
}

Widget::~Widget()
{

    delete ui;
}

void Widget::get_tcpsocket()
{
    QDateTime current_date_time =QDateTime::currentDateTime();
    QString current_date =current_date_time.toString("yyyy.MM.dd hh:mm:ss.zzz ddd");
    QTcpSocket* socket = new QTcpSocket();
    socket = m_server->nextPendingConnection();
    this->lt.append(socket);
    QString ip = socket->peerAddress().toString();
    MyThread* thread = new MyThread(socket,&db,ip);//启动一个线程  把连接来的socket与ip传给线程
    connect(thread,&MyThread::socket_disconnect,this,&Widget::remove_disSocket);//断开连接槽
    connect(thread,&MyThread::data_information,this,&Widget::write_information);//发送个人信息
    connect(thread,&MyThread::marry_rival,this,&Widget::marry_rival_slot);//准备槽函数
    connect(thread,&MyThread::over_game,this,&Widget::over_game_slot);//游戏结束槽函数
    connect(thread,&MyThread::close_start,this,&Widget::close_start_slot);//关闭匹配槽函数
    connect(thread,&MyThread::pieces_move,this,&Widget::pieces_move_slot);//发送棋子移动槽函数
    connect(thread,&MyThread::dowm_over,this,&Widget::down_over_slot);
    this->ui->userIpEdit->append("用户"+ip+"连接\n"+current_date);
    thread->start();
    return;
}

void Widget::connect_database()
{
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setUserName("root");
    db.setPassword("XPeng888");
    db.setDatabaseName("chinacheesserver");
    db.open();
    return;
}

void Widget::remove_disSocket(QTcpSocket* socket)
{
    qDebug()<<"用户断开连接";
    this->lt.removeOne(socket);
    if(m_pair_socket[socket]!=nullptr){//如果该用户不等于空则表示他正在游戏中
        qDebug()<<"xxxx";
        QByteArray s = "disSocket";
        this->m_pair_socket[socket]->write(s.data(),s.size());
        m_pair_socket.remove(m_pair_socket[socket]);
        m_pair_socket.remove(socket);
    }
    return;
}

void Widget::write_information(QString ip,QString data)
{
    this->ui->informationEdit->append("用户"+ip+"\n发送"+data);
    return;
}

void Widget::marry_rival_slot(QTcpSocket* socket)
{
    if(this->count==0){
        this->count = 1;
        this->tmp_socket = socket;
    }
    else{
        m_pair_socket[tmp_socket] = socket;
        m_pair_socket[socket] = tmp_socket;
        QByteArray data = {"startGame"};
        QByteArray data_1 = data;
        data.push_back('|');
        data_1.push_back('|');
        data+="false";
        data_1+="true";
        char* da = data.data();
        char* da_1 = data_1.data();
        socket->write(da,data.size());
        tmp_socket->write(da_1,data_1.size());
        qDebug()<<da<<da_1;
        tmp_socket = nullptr;
        this->count = 0;
    }
}

void Widget::close_start_slot(QTcpSocket * socket)
{
    if(tmp_socket == socket){
        tmp_socket = nullptr;//将类中的指针置为空
        count = 0;
    }
}

void Widget::over_game_slot(QTcpSocket * socket)
{
    m_pair_socket.remove(socket);
    return;
}

void Widget::pieces_move_slot(QTcpSocket* socket, QVector<QString> vs)
{
    /*内容为move|X1|Y1|X2|Y2*/
    QByteArray s;
    for(auto i : vs){
        s+=i;
        s.push_back('|');
    }
    s.chop(1);
    qDebug()<<s;
    m_pair_socket[socket]->write(s.data(),s.size());
}

void Widget::down_over_slot(QTcpSocket * socket, QString data)
{
    QByteArray s;
    s+=data;
    m_pair_socket[socket]->write(s.data(),data.size());
    return;
}

void Widget::on_startServerbutton_clicked()
{
    this->m_server = new QTcpServer(this);
    m_server->listen(QHostAddress::Any,6666);
    ui->userIpEdit->append("服务器监听中");
    ui->startServerbutton->setDisabled(true);
    ui->closeServerButton->setEnabled(true);
    connect(this->m_server,&QTcpServer::newConnection,this,&Widget::get_tcpsocket);
    return;
}

void Widget::on_closeServerButton_clicked()
{
    this->lt.clear();
    m_server->close();
    ui->startServerbutton->setEnabled(true);
    ui->closeServerButton->setDisabled(true);
    ui->userIpEdit->setText("");
    ui->informationEdit->setText("");
    return;
}

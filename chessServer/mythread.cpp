#include "mythread.h"
#include<QTcpSocket>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QDebug>
MyThread::MyThread(QTcpSocket * socket, QSqlDatabase * db, QString ip,QObject *parent) : QThread(parent = nullptr)
{
    this->m_socket = socket;
    this->db = db;
    this->ip = ip;
    ifrememberpassword();
}

void MyThread::get_data()
{
    QString data = this->m_socket->readAll();
    emit data_information(this->ip,data);
    QVector<QString> vs_data;
    QString s;
    for(int i=0;i<data.size();i++){
        for(;i<data.size();i++){
            if(data[i]=='|'){
                vs_data.push_back(s);
                s.clear();
                break;
            }
            else{
                s.push_back(data[i]);
            }
        }
    }
    vs_data.push_back(s);
    data_dispose(vs_data);
}

void MyThread::ifrememberpassword()
{
    QSqlQuery query(*this->db);
    query.exec(tr("select * from `userstate` where ip = '%1'").arg(this->ip));
    bool if_exist = query.next();
    if(if_exist){
        QString remember = "rememberPassword";
        QString data_1 = query.value(1).toString();
        QString data_2 = query.value(2).toString();
        remember.push_back('|');
        remember+=data_1;
        remember.push_back('|');
        remember+=data_2;
        sand_data(remember);
    }
}

void MyThread::data_dispose(QVector<QString> & vs)
{
    if(vs[0]=="createUser"){
        dispose_createUser(vs);
        return;
    }
    if(vs[0]=="rememberPassword"){
        dispose_rememberPassword(vs);
        return;
    }
    if(vs[0]=="confirmAccount"){
        if(confirmAccount(vs)){
            sand_data(tr("confirmAccount|true"));
        }
        else{
            sand_data(tr("confirmAccount|false"));
        }
        return;
    }
    if(vs[0]=="marryRival"){
        emit marry_rival(this->m_socket);
        return;
    }
    if(vs[0]=="overGame"){
        emit over_game(this->m_socket);
        return;
    }
    if(vs[0]=="reception"){
        dispose_reception(vs);
        return;
    }
    if(vs[0] == "changeImage"){
        dispose_changeImage(vs);
        return;
    }
    if(vs[0] == "closeStart"){
        emit close_start(this->m_socket);
        return;
    }
    if(vs[0] == "move"){
        emit pieces_move(this->m_socket,vs);
    }
    if(vs[0] == "dowmOver"){
        emit dowm_over(this->m_socket,vs[0]);
    }
}

void MyThread::dispose_rememberPassword(QVector<QString> &vs)
{
    //首先查询是否有该用户
    QSqlQuery query(*this->db);
    if(confirmAccount(vs)){
        sand_data(tr("confirmAccount|true"));
        query.exec(tr("SELECT * FROM `userstate` WHERE ip = '%1'").arg(this->ip));
        if(query.next()){
            query.exec(tr("UPDATE `userstate` SET `userName` = '%1',`password` = '%2',`ifrememberPassword` = '%3' WHERE ip = '%4'")
                       .arg(vs[1]).arg(vs[2]).arg(true).arg(this->ip));
        }
        else{
            query.prepare(tr("INSERT INTO `userstate` (ip,username,PASSWORD,ifrememberPassword) VALUES (:ip,:username,:password,:ifrememberPassword)"));
            query.bindValue(":ip",this->ip);
            query.bindValue(":username",vs[1]);
            query.bindValue(":password",vs[2]);
            query.bindValue(":ifrememberPassword",true);
            query.exec();
        }
    }
    else{
        sand_data(tr("confirmAccount|false"));
    }
    return;
}

void MyThread::dispose_createUser(QVector<QString> & vs)
{
    QSqlQuery query(*this->db);
    query.prepare("INSERT INTO `logintable` (ip,accountNumber,password) VALUES (:ip,:accountNumber,:password)");
    query.bindValue(":ip",this->ip);
    query.bindValue(":accountNumber",vs[1]);
    query.bindValue(":password",vs[2]);
    query.exec();
    query.prepare("INSERT INTO `informationtable` (ip) VALUES (:ip)");
    query.bindValue(":ip",this->ip);
    query.exec();
    return;
}

void MyThread::dispose_reception(QVector<QString> &)
{
    QSqlQuery query(*this->db);
    query.exec(tr("select * from `informationtable` where ip = '%1'").arg(this->ip));
    query.next();
    QString gameNumber = query.value(1).toString();
    QString winrate = query.value(2).toString();
    QString userName = query.value(3).toString();
    QString imagePath = query.value(4).toString();
    qDebug()<<imagePath;
    QString data = "information";
    data.push_back('|');
    data+=gameNumber;
    data.push_back('|');
    data+=winrate;
    data.push_back('|');
    data+=userName;
    data.push_back('|');
    data+=imagePath;
    sand_data(data);
}

void MyThread::dispose_changeImage(QVector<QString> & vs)
{
    QSqlQuery query(*this->db);
    query.exec(tr("UPDATE `informationtable` SET `imagePath` = '%1' WHERE  ip = '%2'").arg(vs[1],this->ip));
    return;
}

bool MyThread::confirmAccount(QVector<QString> & vs)
{
    QSqlQuery query(*this->db);
    query.exec(tr("SELECT * from `logintable` WHERE (accountNumber = '%1' AND password = '%2')").arg(vs[1],vs[2]));
    bool flag = query.next();
    return flag;
}

void MyThread::sand_data(QString data)
{
    QByteArray da = data.toLatin1();
    char* tmp = da.data();
    m_socket->write(tmp,data.size());
}

void MyThread::close_socket()
{
    emit socket_disconnect(m_socket);
    this->quit();
    this->wait();
    m_socket->deleteLater();
}


void MyThread::run()
{
    connect(m_socket,&QTcpSocket::readyRead,this,&MyThread::get_data);
    connect(m_socket,&QTcpSocket::disconnected,this,&MyThread::close_socket);
}

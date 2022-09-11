#include "clientwork.h"
#include <QHostAddress>
#include <QMessageBox>
#include <QDebug>
clientWork::clientWork(QTcpSocket* socket,QObject* parent) : QObject (parent)
{
    this->m_socket = socket;
    connect(m_socket,&QTcpSocket::readyRead,this,&clientWork::get_data);
}
clientWork::~clientWork(){
    m_socket->close();
    m_socket->deleteLater();
}

void clientWork::get_data()//对数据进行解码
{
    QString data = this->m_socket->readAll();
    qDebug()<<data;
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

void clientWork::data_dispose(QVector<QString>& vs)
{
    if(vs[0]=="confirmAccount"){
        if(vs[1]=="true"){
            emit existUser();
        }
        else{
            QMessageBox::information(nullptr,"登入错误","用户名或密码错误");
        }
    }
    else if(vs[0]=="rememberPassword"){
        emit rememberPassword(vs[1],vs[2]);
        sand_data("reception");
    }
    else if(vs[0]=="startGame"){
        emit marryOk(vs[1]);
    }
    else if(vs[0]=="information"){
        emit userInformation(vs[1],vs[2],vs[3],vs[4]);
    }
    else if(vs[0]=="move"){//棋子移动//谁|x|y;
        emit movePieces(vs[1],vs[2],vs[3],vs[4]);
    }
    else if(vs[0]=="disSocket"){
        emit disSocket();
    }
    else if(vs[0]=="dowmOver"){
        emit dowmOver();
    }
}

void clientWork::connect_server()
{
   this->m_socket->connectToHost(QHostAddress(IP),6666);
   qDebug()<<"xxx";
}

void clientWork::sand_data(QString data)
{
    QByteArray da = data.toLatin1();
    char* tmp = da.data();
    m_socket->write(tmp,data.size());
}

void clientWork::createUser_slot(QString data)
{
    sand_data(data);
}

void clientWork::marryRival_slot()
{
    QString data = "marryRival";
    sand_data(data);
}

void clientWork::rememberPassword_slot(QString data)
{
    sand_data(data);
}

void clientWork::confirmAccount_slot(QString accountNumber,QString passWord)
{
    QString data = "confirmAccount";
    data.push_back('|');
    data += accountNumber;
    data.push_back('|');
    data += passWord;
    sand_data(data);
}

void clientWork::changeImagePath_slot(QString imagePath)
{
    QByteArray data = "changeImage";
    data.push_back('|');
    data += imagePath;
    m_socket->write(data,data.size());
    return;
}

void clientWork::move_slot(QString pieces)
{
    QByteArray data = "move";
    data.push_back('|');
    data += pieces;
    qDebug()<<data;
    m_socket->write(data,data.size());
//    m_socket->
    return;
}

void clientWork::closeStart_slot()
{
    m_socket->write("closeStart");
    return;
}

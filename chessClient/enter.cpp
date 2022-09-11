#include "enter.h"
#include "ui_enter.h"
#include <QLineEdit>
#include <QMessageBox>
#include <QDebug>
#include <QTime>
Enter::Enter(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Enter)
{
    ui->setupUi(this);
    setBackground();//初始化桌面背景
    this->show();
}

Enter::~Enter()
{
    delete ui;
}

void Enter::setBackground(){
    this->resize(450,300);
    this->setWindowFlag(Qt::FramelessWindowHint);
    QPalette pa(this->palette());
    QImage img = QImage(":/C:/Users/xupeng/Desktop/ChinaChees/image/enter_backgrond.jpg");
    img = img.scaled(this->size());
    QBrush *pic = new QBrush(img);
    pa.setBrush(QPalette::Window,*pic);
    this->setAutoFillBackground(true);
    this->setPalette(pa);
    ui->stackedWidget->setCurrentWidget(ui->enterPage);//初始化登入界面
    ui->passwordEdit->setEchoMode(QLineEdit::Password);//将输入密码隐藏
    ui->setPassWord->setEchoMode(QLineEdit::Password);
    ui->affirmPassWord->setEchoMode(QLineEdit::Password);
}
void Enter::serUsernameAndPassword(QString userName, QString passWord)
{
    this->ui->bankEdit->setText(userName);
    this->ui->passwordEdit->setText(passWord);
    return;
}

void Enter::rememberPassword_slot(QString username, QString password)
{
    this->ui->bankEdit->setText(username);
    this->ui->passwordEdit->setText(password);
    return;
}

void Enter::mouseMoveEvent(QMouseEvent *event)
{
    if(this->z==QPoint()){
        return;
    }
    QPoint y = event->globalPos();//globa全局的//获取全局点坐标
    this->move(y-(this->z));
}

void Enter::mousePressEvent(QMouseEvent *event)
{
    //获取当前鼠标位置 向量的形式进行加减
    QPoint y = event->globalPos();//globa全局的//获取全局点坐标
    QPoint x = this->geometry().topLeft();//获取左上角的点坐标
    this->z = y - x;
}

void Enter::on_login_released()
{
    ui->stackedWidget->setCurrentWidget(ui->loginPage);
}

void Enter::on_affirm_clicked()//用户注册确认按键
{
    QString password = ui->setPassWord->text();
    QString userName = ui->userName->text();
    QString data = "createUser";
    data.push_back('|');
    data += userName;
    data.push_back('|');
    data += password;
    emit createUser(data);
    this->ui->stackedWidget->setCurrentWidget(ui->enterPage);
}


void Enter::on_enterClose_clicked()
{
    this->close();
}


void Enter::on_returnButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->enterPage);
}

void Enter::on_login_clicked()
{
    this->ui->stackedWidget->setCurrentWidget(ui->loginPage);
    return;
}

void Enter::on_enter_clicked()
{
    QString passsword = ui->passwordEdit->text();
    QString bankEdit = ui->bankEdit->text();
    if(ui->rememberPassword->isChecked()){
        //发送给服务器  让服务器记录她的ip和对应的账号和密码  并发送个客户端
        QString re = "rememberPassword";
        re.push_back('|');
        re += bankEdit;
        re.push_back('|');
        re += passsword;
        emit rememberPassword(re);
    }
    else emit confirmAccount(bankEdit,passsword);
}

#include "widget.h"
#include "ui_widget.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QBrush>
#include <QGraphicsPixmapItem>
#include "cimagebutton.h"
#include "clientwork.h"
#include "piecesfactory.h"
#include "widget.h"
bool m_find(QVector<PiecesBase*>& map,CimageButton* button);
//connectread——ready
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    this->ui->setupUi(this);
    this->dowmOk = false;
    this->button_licke = nullptr;
    m_chess_map = QVector<QVector<PiecesBase*>>(10,QVector<PiecesBase*>(9,nullptr));//棋盘存储初始化
    this->pieces = nullptr;
    setBackgrount();
    this->enter = new Enter();
    this->m_socket = new QTcpSocket(this);
    this->chilet = new clientWork(m_socket,this);
    this->chilet->connect_server();
    this->m_cretorPieces = new cretor(ui->checkerboard);
    this->ui->label_image->installEventFilter(this);//安装事件过滤器
    connect_signal_slot();
}

Widget::~Widget()
{
    this->enter->deleteLater();
    this->m_socket->deleteLater();
    this->chilet->deleteLater();
    this->m_cretorPieces->deleteLater();
    delete ui;
}

void Widget::connect_signal_slot()
{
    connect(enter,&Enter::createUser,chilet,&clientWork::createUser_slot);
    connect(enter,&Enter::confirmAccount,chilet,&clientWork::confirmAccount_slot);
    connect(enter,&Enter::rememberPassword,chilet,&clientWork::rememberPassword_slot);
    connect(chilet,&clientWork::existUser,this,&Widget::this_show);
    connect(chilet,&clientWork::userInformation,this,&Widget::show_this_information);
    connect(chilet,&clientWork::movePieces,this,&Widget::move_slot);
    connect(this,&Widget::move_pieces,chilet,&clientWork::move_slot);
    connect(chilet,&clientWork::rememberPassword,enter,&Enter::rememberPassword_slot);
    connect(this,&Widget::marryRival,chilet,&clientWork::marryRival_slot);
    connect(this,&Widget::closeStart,chilet,&clientWork::closeStart_slot);
    connect(chilet,&clientWork::marryOk,this,&Widget::marryOk_slot);
    connect(this,&Widget::changeImage,chilet,&clientWork::changeImagePath_slot);
    connect(m_cretorPieces,&cretor::label_clicked,this,&Widget::label_clicked_slot);
    connect(chilet,&clientWork::disSocket,this,&Widget::disSocket_slot);
    connect(chilet,&clientWork::dowmOver,this,&Widget::dowmOver_slot);
}

void Widget::clicked_slot(CimageButton* button)
{
    if(!dowmOk){//没有权利落棋 则跳过
        return;
    }
    bool tmp_1 = m_find(this->m_chess_map_enemy,button);
    if(button_licke == nullptr && tmp_1){//判断此棋子是否是对方的
        return;
    }
    if(button_licke == button){
        return;
    }
    int x = button->pos().x();
    int y = button->pos().y();
    if(button_licke!=nullptr&&tmp_1&&this->pieces->move_rules(x,y,this->m_chess_map)){//敌方该位置由棋子  可吃掉它
        m_chess_map[(button_licke->pos().y()-10)/70][(button_licke->pos().x()-30)/60] = nullptr;
        QString data = QString::number(button_licke->pos().x(),10);
        data.push_back('|');
        data += QString::number(button_licke->pos().y(),10);
        data.push_back('|');
        data += QString::number(x,10);
        data.push_back('|');
        data+= QString::number(y,10);
        emit move_pieces(data);
        button_licke->move(x,y);
        this->m_chess_map[(y-10)/70][(x-30)/60]->deleteLater();
        this->m_chess_map[(y-10)/70][(x-30)/60] = pieces;
        button_licke = nullptr;
        pieces = nullptr;
        dowmOk = false;
    }
    else if(button_licke!=nullptr&&tmp_1){
        return;
    }
    else{
        this->pieces = nullptr;
        this->button_licke = button;
        qDebug()<<button_licke->pos().y()<<button_licke->pos().x();
        this->pieces = m_chess_map[(button_licke->pos().y()-10)/70][(button_licke->pos().x()-30)/60];
    }
    return;
}

void Widget::label_clicked_slot(QLabel* label)
{
    if(!dowmOk){//没有权利落棋 则跳过
        return;
    }
    if(this->button_licke != nullptr){
        int x = label->pos().x();
        int y = label->pos().y();
        if(this->pieces->move_rules(x,y,m_chess_map)){
            m_chess_map[(button_licke->pos().y()-10)/70][(button_licke->pos().x()-30)/60] = nullptr;
            QString data = QString::number(button_licke->pos().x(),10);
            data.push_back('|');
            data += QString::number(button_licke->pos().y(),10);
            data.push_back('|');
            data += QString::number(x,10);
            data.push_back('|');
            data+= QString::number(y,10);
            qDebug()<<data;
            emit move_pieces(data);
            button_licke->move(x,y);
            this->m_chess_map[(y-10)/70][(x-30)/60] = pieces;
            button_licke = nullptr;
            pieces = nullptr;
            dowmOk = false;
            //int i = 0;
            //m_socket->write("dowmOver",9);
        }
    }
}

void Widget::this_show()
{
    ui->checkerboard->hide();
    ui->timeoverWidget->hide();
    this->show();
    enter->hide();
    return;
}

void Widget::show_this_information(QString gamenumber, QString winrate, QString username,QString imagePath)
{
    this->ui->label_number->setText(gamenumber);
    this->ui->label_winrate->setText(winrate);
    this->ui->label_userName->setText(username);
    if(!imagePath.isEmpty()){
        change_imagePath(imagePath);
    }
}

void Widget::disSocket_slot()//用户正在游戏进行时退出游戏
{
    this->ui->startGame->setEnabled(true);
    this->ui->closeStart->setDisabled(true);
    this->ui->checkerboard->hide();
    this->playIng = false;
    qDebug()<<"*****************";
    for(auto& it : m_chess_map){
        for(auto& i : it){
            if(i != nullptr){
                i->deleteLater();
                i = nullptr;
            }
        }
    }
        qDebug()<<"*****************";
    for(auto& it : m_piecesHash){
        for(auto & i : it){
            i = nullptr;
        }
    }
        qDebug()<<"*****************";
    this->ui->checkerboard->hide();
    this->ui->title->setText("");
    //this->
    /*
    显示胜利页面
    */
    return;
}

void Widget::dowmOver_slot()
{
    this->dowmOk = true;
    return;
}

void Widget::overGame_slot(CimageButton* button)
{
    //this->m_socket->write()
    if(this->playIng){
        if(m_find(this->m_chess_map_enemy,button)){
            QMessageBox::information(this,"victory","胜利");
        }
        else{
            QMessageBox::information(this,"defeated","失败");
        }
        disSocket_slot();
    }
    return;
}

void Widget::marryOk_slot(QString data)
{
    this->playIng = true;
    this->ui->title->setText("匹配成功");
    if(data == "false"){//判断谁获得哪方棋子//false 红色//true 黑色
        this->m_cretorPieces->cretorAll(false);
        dowmOk = true;
    }
    else{
        this->m_cretorPieces->cretorAll(true);
        dowmOk = false;
    }
    /*匹配成功后开始画棋盘*/
    this->m_piecesHash = m_cretorPieces->get_piecesHash();
    for(auto it : m_piecesHash){
        for(PiecesBase* p : it){
           connect(p,&PiecesBase::button_ip,this,&Widget::clicked_slot);
           connect(p,&PiecesBase::over_game,this,&Widget::overGame_slot);
           int x = p->get_button_location().first-30;
           int y = p->get_button_location().second-10;
           x/=60;
           y/=70;
           if(m_chess_map[y][x]!=nullptr){
               m_chess_map[y][x]->deleteLater();
           }
           this->m_chess_map[y][x] = p;
        }
    }
    for(int i=0;i<m_chess_map.size()/2;i++){
        for(int j=0;j<m_chess_map[0].size();j++){
            this->m_chess_map_enemy.push_back(m_chess_map[i][j]);//将敌方的棋子录入其中
        }
    }
    this->label = m_cretorPieces->get_label();
    ui->timeoverWidget->show();
    ui->checkerboard->show();
    return;
}

void Widget::setBackgrount()
{
    QPalette pa(this->palette());
    this->resize(840,740);
    this->ui->checkerboard->resize(540,650);
    ui->closeStart->setDisabled(true);
    QImage img = QImage(":/C:/Users/xupeng/Desktop/ChinaChees/image/enter_backgrond.jpg");
    img = img.scaled(this->size());
    QBrush *pic = new QBrush(img);
    pa.setBrush(QPalette::Window,*pic);
    this->setAutoFillBackground(true);
    this->setPalette(pa);
    return;
}

void Widget::change_imagePath(QString image_path)
{
    QPixmap p;
    p.load(image_path);
    p.scaled(ui->label_image->size(), Qt::KeepAspectRatio);
    ui->label_image->setScaledContents(true);
    this->ui->label_image->setPixmap(image_path);
    return;
}

void Widget::move_slot(QString x,QString y,QString move_x,QString move_y)
{
    this->dowmOk = true;
    if(m_chess_map[(650-move_y.toInt())/70][(540-move_x.toInt())/60]!=nullptr){
        m_chess_map[(650-move_y.toInt())/70][(540-move_x.toInt())/60]->get_button()->deleteLater();//删除移动位置的棋子
        m_chess_map[(650-move_y.toInt())/70][(540-move_x.toInt())/60]=nullptr;
    }
    CimageButton* button = this->m_chess_map[(650-y.toInt())/70][(540-x.toInt())/60]->get_button();
    m_chess_map[((button->pos().y()+(y.toInt()-move_y.toInt()))-10)/70][((button->pos().x()+(x.toInt()-move_x.toInt()))-30)/60]\
            = this->m_chess_map[(650-y.toInt())/70][(540-x.toInt())/60];
    this->m_chess_map[(650-y.toInt())/70][(540-x.toInt())/60] = nullptr;
    button->move(button->pos().x()+(x.toInt()-move_x.toInt())\
                 ,button->pos().y()+(y.toInt()-move_y.toInt()));
    this->m_chess_map[(650-y.toInt())/70][(540-x.toInt())/60] = nullptr;
    return;
}
void Widget::on_startGame_clicked()
{
    emit marryRival();
    this->ui->closeStart->setEnabled(true);
    this->ui->startGame->setDisabled(true);
    this->ui->title->setText("用户等待连接");
    return;
}

void Widget::on_closeStart_clicked()
{
    this->ui->title->setText("");
    this->ui->startGame->setEnabled(true);
    this->ui->closeStart->setDisabled(true);
    emit closeStart();
}

bool Widget::eventFilter(QObject *object, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonPress) //鼠标点击
    {
        if(object == this->ui->label_image){
            QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event); // 事件转
            if(mouseEvent->button() == Qt::LeftButton)
            {
                QString imagePath = QFileDialog::getOpenFileName(this,tr("头像对话框"),tr("C:"),(tr("*.jpg;*.png")));
                if(imagePath==nullptr){
                    return true;
                }
                change_imagePath(imagePath);
                emit changeImage(imagePath);
                return true;
            }
            else{
                return false;
            }
        }
    }
    else
    {
        return false;
    }
    return false;
}


bool m_find(QVector<PiecesBase*>& map,CimageButton* button){
    for(int i=0;i<map.size();i++){
        if(map[i]!=nullptr&&map[i]->get_button()==button){
            return true;
        }
    }
    return false;
}

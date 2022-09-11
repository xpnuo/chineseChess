#include "officerspieces.h"
officersPieces::officersPieces(QWidget *parent) : PiecesBase(parent)
{
    button = new CimageButton(90,510,parent);
    button->installEventFilter(this);
}

officersPieces::~officersPieces()
{
    this->button->deleteLater();
    return;
}

bool officersPieces::move_rules(int x,int y,QVector<QVector<PiecesBase*>> chess_map)
{
    if(x<170||x>350||y<450){
        return false;
    }
    if(abs(this->button->pos().x()-x)==60&&abs(this->button->pos().y()-y)==70){
        return true;
    }
    return false;
}

void officersPieces::pieces_style(QString imagePath)
{
    qDebug()<<imagePath;
}

void officersPieces::set_location(int x, int y)
{
    qDebug()<<x<<y;
}

void officersPieces::can_location()
{

}

void officersPieces::set_color(bool color,int x,int y)
{
    if(color == false){
        button->setStyleSheet(tr("QPushButton{border-style:solid;"
                                 "border-image:url(:/C:/Users/xupeng/Desktop/ChinaChees/image/blackShi.png);"
                                 "border-radius:30px;}"
                                 "QPushButton:pressed{"
                                 "border-image:url(:/C:/Users/xupeng/Desktop/ChinaChees/image/blackShi.png)"
                                 "}"));
    }
    else{
        button->setStyleSheet(tr("QPushButton{border-style:solid;"
                                 "border-image:url(:/C:/Users/xupeng/Desktop/ChinaChees/image/redShi.png);"
                                 "border-radius:30px;}"
                                 "QPushButton:pressed{"
                                 "border-image:url(:/C:/Users/xupeng/Desktop/ChinaChees/image/redShi.png)"
                                 "}"));
    }
    button ->move(x,y);
}

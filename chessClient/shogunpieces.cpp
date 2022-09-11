#include "shogunpieces.h"
shogunPieces::shogunPieces(QWidget* parent) : PiecesBase (parent)
{
    this->button = new CimageButton(20,10,parent);
    button->installEventFilter(this);
}

shogunPieces::~shogunPieces()
{
    this->button->deleteLater();
    emit over_game(this->button);
    return;
}

bool shogunPieces::move_rules(int x,int y,QVector<QVector<PiecesBase*>> chess_map)
{
    if(x<170||x>350||y<450){
        return false;
    }
    if((abs(this->button->pos().x()-x)==60&&(this->button->pos().y()==y))||((this->button->pos().x()==x)&&abs(this->button->pos().y()-y)==70))return true;
    return false;
}

void shogunPieces::pieces_style(QString imagePath)
{
    qDebug()<<imagePath;
}

void shogunPieces::set_location(int x, int y)
{
    qDebug()<<x<<y;
}

void shogunPieces::can_location()
{

}

void shogunPieces::set_color(bool color,int x,int y)
{
    if(color == false){
        button->setStyleSheet(tr("QPushButton{border-style:solid;"
                                 "border-image:url(:/C:/Users/xupeng/Desktop/ChinaChees/image/blackJiang.png);"
                                 "border-radius:30px;}"
                                 "QPushButton:pressed{"
                                 "border-image:url(:/C:/Users/xupeng/Desktop/ChinaChees/image/blackMa.png)"
                                 "}"));
    }
    else{
        button->setStyleSheet(tr("QPushButton{border-style:solid;"
                                 "border-image:url(:/C:/Users/xupeng/Desktop/ChinaChees/image/redJiang.png);"
                                 "border-radius:30px;}"
                                 "QPushButton:pressed{"
                                 "border-image:url(:/C:/Users/xupeng/Desktop/ChinaChees/image/redMa.png)"
                                 "}"));
    }
    button ->move(x,y);
}

#include "soldierpieces.h"

soldierPieces::soldierPieces(QWidget* parent) : PiecesBase (parent)
{
    this->button = new CimageButton(20,10,parent);
    button->installEventFilter(this);
    //int tmp = button->pos().x();
}

soldierPieces::~soldierPieces()
{
    this->button->deleteLater();
    return;
}
bool soldierPieces::move_rules(int x,int y,QVector<QVector<PiecesBase*>> chess_map)
{
   qDebug()<<x<<this->button->pos().x()<<y<<this->button->pos().y();
   if(this->button->y()>330){
        if(x==this->button->pos().x()&&y==this->button->pos().y()-70) return true;
   }
   else{
       if((abs(this->button->pos().x()-x)==60&&y==this->button->pos().y())||(this->button->pos().x()==x&&y==this->button->pos().y()-70)){
           return true;
       }
   }
    return false;
}

void soldierPieces::pieces_style(QString imagePath)
{
    qDebug()<<imagePath;
}

void soldierPieces::set_location(int x, int y)
{
    if(this->button->pos().x()<300){
        qDebug()<<x<<y;
    }
    else{
    }
}

void soldierPieces::can_location()
{

}

void soldierPieces::set_color(bool color,int x,int y)
{
    if(color == false){
        button->setStyleSheet(tr("QPushButton{border-style:solid;"
                                 "border-image:url(:/C:/Users/xupeng/Desktop/ChinaChees/image/blackZu.png);"
                                 "border-radius:30px;}"
                                 "QPushButton:pressed{"
                                 "border-image:url(:/C:/Users/xupeng/Desktop/ChinaChees/image/blackZu.png)"
                                 "}"));
    }
    else{
        button->setStyleSheet(tr("QPushButton{border-style:solid;"
                                 "border-image:url(:/C:/Users/xupeng/Desktop/ChinaChees/image/redBing.png);"
                                 "border-radius:30px;}"
                                 "QPushButton:pressed{"
                                 "border-image:url(:/C:/Users/xupeng/Desktop/ChinaChees/image/redBing.png)"
                                 "}"));
    }
    button ->move(x,y);
}

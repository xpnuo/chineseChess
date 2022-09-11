#include "carpieces.h"

carPieces::carPieces(QWidget *parent) : PiecesBase(parent)
{
    button = new CimageButton(150,640,parent);
    button->installEventFilter(this);
}

carPieces::~carPieces()
{
    this->button->deleteLater();
    return;
}

bool carPieces::move_rules(int x,int y,QVector<QVector<PiecesBase*>> chess_map)
{
    if(this->button->pos().x()==x||this->button->pos().y()==y){
        if(this->button->pos().x()!=x){
            for(int i=(qMin(this->button->pos().x(),x)-30)/60+1;i<(qMax(this->button->pos().x(),x)-30)/60;i++){
                if(chess_map[(y-10)/70][i]!=nullptr){
                    return false;
                }
            }
        }
        else{
            for(int i=(qMin(this->button->pos().y(),y)-10)/70+1;i<(qMax(this->button->pos().y(),y)-10)/70;i++){
                if(chess_map[i][(x-30)/60]!=nullptr){
                    return false;
                }
            }
        }
    }
    else{
        return false;
    }
    return true;
}

void carPieces::pieces_style(QString imagePath)
{
    qDebug()<<imagePath;
}

void carPieces::set_location(int x, int y)
{
    qDebug()<<x<<y;
}

void carPieces::can_location()
{

}

void carPieces::set_color(bool color,int x,int y)
{
    if(color == false){
        button ->setStyleSheet(tr("QPushButton{border-style:solid;"
                                 "border-image:url(:/C:/Users/xupeng/Desktop/ChinaChees/image/blackZhu.png);"
                                 "border-radius:30px;}"
                                 "QPushButton:pressed{"
                                 "border-image:url(:/C:/Users/xupeng/Desktop/ChinaChees/image/blackZhu.png)"
                                 "}"));
    }
    else{
        button ->setStyleSheet(tr("QPushButton{border-style:solid;"
                                 "border-image:url(:/C:/Users/xupeng/Desktop/ChinaChees/image/redZhu.png);"
                                 "border-radius:30px;}"
                                 "QPushButton:pressed{"
                                 "border-image:url(:/C:/Users/xupeng/Desktop/ChinaChees/image/redZhu.png)"
                                 "}"));
    }
    button->move(x,y);
}

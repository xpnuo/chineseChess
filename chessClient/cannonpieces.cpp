#include "cannonpieces.h"

cannonPieces::cannonPieces(QWidget *parent) : PiecesBase(parent)
{
    button = new CimageButton(150,640,parent);
    button->installEventFilter(this);
}

cannonPieces::~cannonPieces()
{
    this->button->deleteLater();
    return;
}
bool cannonPieces::move_rules(int x,int y,QVector<QVector<PiecesBase*>> chess_map)
{
    /*点击的位置是否是其他的按键
    点击的位置与原有位置之间是否有棋子*/
    qDebug()<<"触发";
    int sum = 0;
    if(this->button->pos().x()==x||this->button->pos().y()==y){
        if(this->button->pos().x()!=x){
            for(int i=(qMin(this->button->pos().x(),x)-30)/60+1;i<(qMax(this->button->pos().x(),x)-30)/60;i++){
                if(chess_map[(y-10)/70][i]!=nullptr){
                    sum++;
                }
            }
            if(sum==1&&chess_map[(y-10)/70][(x-30)/60]!=nullptr){
                return true;
            }
            if(sum==0&&chess_map[(y-10)/70][(x-30)/60]==nullptr){
                return true;
            }
        }
        else{
            for(int i=(qMin(this->button->pos().y(),y)-10)/70+1;i<(qMax(this->button->pos().y(),y)-10)/70;i++){
                if(chess_map[i][(x-30)/60]!=nullptr){
                    sum++;
                }
            }
            if(sum==1&&chess_map[(y-10)/70][(x-30)/60]!=nullptr){
                return true;
            }
            if(sum==0&&chess_map[(y-10)/70][(x-30)/60]==nullptr){
                return true;
            }
        }
    }
    return false;
}

void cannonPieces::pieces_style(QString imagePath)
{
    qDebug()<<imagePath;
}

void cannonPieces::set_location(int x, int y)
{
    qDebug()<<x<<y;
}

void cannonPieces::can_location()
{

}

void cannonPieces::set_color(bool color,int x,int y)
{
    if(color == false){
        button ->setStyleSheet(tr("QPushButton{border-style:solid;"
                                 "border-image:url(:/C:/Users/xupeng/Desktop/ChinaChees/image/blackPao.png);"
                                 "border-radius:30px;}"
                                 "QPushButton:pressed{"
                                 "border-image:url(:/C:/Users/xupeng/Desktop/ChinaChees/image/blackPao.png)"
                                 "}"));
    }
    else{
        button ->setStyleSheet(tr("QPushButton{border-style:solid;"
                                 "border-image:url(:/C:/Users/xupeng/Desktop/ChinaChees/image/redPao.png);"
                                 "border-radius:30px;}"
                                 "QPushButton:pressed{"
                                 "border-image:url(:/C:/Users/xupeng/Desktop/ChinaChees/image/redPao.png)"
                                 "}"));
    }
    button->move(x,y);
}

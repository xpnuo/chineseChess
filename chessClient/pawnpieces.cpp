#include "pawnpieces.h"
pawnpieces::pawnpieces(QWidget* parent)  : PiecesBase (parent)
{
    button = new CimageButton(90,510,parent);
    button->installEventFilter(this);
}


pawnpieces::~pawnpieces()
{
    this->button->deleteLater();
    return;
}

bool pawnpieces::move_rules(int x,int y,QVector<QVector<PiecesBase*>> chess_map)
{
    if(!((abs(this->button->pos().x()-x)==60&&abs(this->button->pos().y()-y)==140)||(abs(this->button->pos().x()-x)==120&&abs(this->button->pos().y()-y)==70))){
        return false;
    }
    if(abs(this->button->pos().x()-x)==60&&abs(this->button->pos().y()-y)==140){//竖直移动
        if(chess_map[(y-10)/70+(this->button->pos().y()-y)/140][(this->button->pos().x()-30)/60]!=nullptr){//如果此处不等于nullptr则表示该处无法下棋
            return false;
        }//(this->button->pos().y()-y)/140得到一个向上或向下的相对位置
    }
    else if(abs(this->button->pos().x()-x)==120&&abs(this->button->pos().y()-y)==70){//水平移动
        if(chess_map[(this->button->pos().y()-10)/70][(x-30)/60+(this->button->pos().x()-x)/120]!=nullptr){//如果此处不等于nullptr则表示该处无法下棋
            return false;
        }//(this->button->pos().y()-y)/140得到一个向上或向下的相对位置
    }
    return true;
}

void pawnpieces::pieces_style(QString imagePath)
{
    qDebug()<<imagePath;
}

void pawnpieces::set_location(int x, int y)
{
    qDebug()<<x<<y;
}

void pawnpieces::can_location()
{
    this->button->deleteLater();
}

void pawnpieces::set_color(bool color,int x,int y)
{
    if(color == false){
        button->setStyleSheet(tr("QPushButton{border-style:solid;"
                                 "border-image:url(:/C:/Users/xupeng/Desktop/ChinaChees/image/blackMa.png);"
                                 "border-radius:30px;}"
                                 "QPushButton:pressed{"
                                 "border-image:url(:/C:/Users/xupeng/Desktop/ChinaChees/image/blackMa.png)"
                                 "}"));
    }
    else{
        button->setStyleSheet(tr("QPushButton{border-style:solid;"
                                 "border-image:url(:/C:/Users/xupeng/Desktop/ChinaChees/image/redMa.png);"
                                 "border-radius:30px;}"
                                 "QPushButton:pressed{"
                                 "border-image:url(:/C:/Users/xupeng/Desktop/ChinaChees/image/redMa.png)"
                                 "}"));
    }
    button ->move(x,y);
}

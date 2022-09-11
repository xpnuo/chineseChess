#include "elephantpieces.h"
elephantPieces::elephantPieces(QWidget* parent)  : PiecesBase (parent)
{
    button = new CimageButton(150,640,parent);
    button->installEventFilter(this);
}

elephantPieces::~elephantPieces()
{
    this->button->deleteLater();
    return;
}


bool elephantPieces::move_rules(int x,int y,QVector<QVector<PiecesBase*>> chess_map)
{
    if(y<330){
        return false;
    }
    if(abs(y-this->button->pos().y())!=140||abs(x-this->button->pos().x())!=120){
        return false;
    }
    else{
        if(chess_map[this->button->pos().y()/70-(this->button->pos().y()-y)/140][this->button->pos().x()/60-(this->button->pos().x()-x)/120]!=nullptr)
        {
            return false;
        }
    }
    return true;
}

void elephantPieces::pieces_style(QString imagePath)
{
    qDebug()<<imagePath;
}

void elephantPieces::set_location(int x, int y)
{
    qDebug()<<x<<y;
}

void elephantPieces::can_location()
{

}

void elephantPieces::set_color(bool color,int x,int y)
{
    if(color == false){
        button ->setStyleSheet(tr("QPushButton{border-style:solid;"
                                 "border-image:url(:/C:/Users/xupeng/Desktop/ChinaChees/image/blackXiang.png);"
                                 "border-radius:30px;}"
                                 "QPushButton:pressed{"
                                 "border-image:url(:/C:/Users/xupeng/Desktop/ChinaChees/image/blackXiang.png)"
                                 "}"));
    }
    else{
        button ->setStyleSheet(tr("QPushButton{border-style:solid;"
                                 "border-image:url(:/C:/Users/xupeng/Desktop/ChinaChees/image/redXiang.png);"
                                 "border-radius:30px;}"
                                 "QPushButton:pressed{"
                                 "border-image:url(:/C:/Users/xupeng/Desktop/ChinaChees/image/redMa.png)"
                                 "}"));
    }
    button->move(x,y);
}

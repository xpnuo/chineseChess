#include "piecesbase.h"
int wight = 10;
int height = 10;
PiecesBase::PiecesBase(QWidget* parent) : QWidget (parent)
{
    button = nullptr;
}

QPushButton *PiecesBase::create_pussButton()
{
   // QPushButton* pushButton = new QPushButton();

    return nullptr;
}

QPair<int, int> PiecesBase::get_button_location()
{
    return {this->button->pos().x(),this->button->pos().y()};
}

CimageButton *PiecesBase::get_button()
{
    return this->button;
}

bool PiecesBase::eventFilter(QObject *object, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonPress){//鼠标点击
        if(object == this->button){
            emit button_ip(this->button);//发送选中的棋子
            return true;
        }
    }
    return false;
}

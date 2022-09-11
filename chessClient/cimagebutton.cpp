#include "cimagebutton.h"
#include <QUrl>
/*竖着每个格子70像素点，横着每个格子60像素点*/
CimageButton::CimageButton(int x,int y,QWidget *parent) : QPushButton(parent)
{
    this->setGeometry(x,y,60,60);
}

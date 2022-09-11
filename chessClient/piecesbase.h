#ifndef PIECESBASE_H
#define PIECESBASE_H
#include <QObject>
#include "cimagebutton.h"
#include <QPushButton>
#include <QMouseEvent>
#include <QDebug>
extern int width;
extern int height;
class PiecesBase : public QWidget
{
    Q_OBJECT
public:
    PiecesBase(QWidget* parent = nullptr);
public:
    virtual bool move_rules(int,int,QVector<QVector<PiecesBase*>>) = 0;//移动的规则
    virtual void pieces_style(QString imagePath) = 0;//传入的图片地址
    virtual void set_location(int,int) = 0;//设置初始位置
    virtual void can_location() = 0;//能走的位置
    virtual void set_color(bool,int,int) = 0;//设置棋子的颜色
    QPushButton* create_pussButton(); //创建棋子
    QPair<int,int> get_button_location();
    CimageButton *get_button();
    bool eventFilter(QObject* object,QEvent* event);

signals:
    void button_ip(CimageButton* );
    void over_game(CimageButton*);

protected://修饰的对象  派生类可以访问外部类不能访问
    CimageButton* button;
};
#endif // PIECESBASE_H

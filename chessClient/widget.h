#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTcpSocket>
#include <QMouseEvent>
#include "piecesbase.h"
#include "enter.h"
#include "clientwork.h"
#include "cretor.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void connect_signal_slot();
    void clicked_slot(CimageButton*);
    void label_clicked_slot(QLabel*);
    void this_show();
    void show_this_information(QString,QString,QString,QString);
    void marryOk_slot(QString);
    void setBackgrount();
    void change_imagePath(QString);
    void move_slot(QString,QString,QString,QString);
    bool eventFilter(QObject* object,QEvent* event);
    void disSocket_slot();
    void dowmOver_slot();
    void overGame_slot(CimageButton*);
    //void mousePressEvent(QMouseEvent *event) override();
//    bool e
private slots:
    void on_startGame_clicked();

    void on_closeStart_clicked();

signals:
    void marryRival();
    void changeImage(QString);
    void closeStart();
    void move_pieces(QString s);
    void delete_pieces(QString);
private:
    bool dowmOk;
    bool playIng;
    PiecesBase* pieces;
    CimageButton* button_licke;
    Ui::Widget *ui;
    QTcpSocket* m_socket;
    Enter* enter;
    clientWork* chilet;
    cretor* m_cretorPieces;//创建棋子
    QVector<QLabel*> label;//存储棋盘上所有位置
    QVector<PiecesBase*> m_chess_map_enemy;//存储敌方的棋子
    QVector<QVector<PiecesBase*>> m_chess_map;//存储棋盘上的棋子所在位置//且是否被消除
    QMap<QString, QVector<PiecesBase *> > m_piecesHash;//存储棋盘所有棋子
};
#endif // WIDGET_H

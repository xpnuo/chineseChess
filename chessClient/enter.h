#ifndef ENTER_H
#define ENTER_H

#include <QWidget>
#include <QTcpSocket>
#include <QTime>
#include <QMouseEvent>
namespace Ui {
class Enter;
}

class Enter : public QWidget
{
    Q_OBJECT

public:
    explicit Enter(QWidget *parent = nullptr);
    ~Enter();

    void setBackground();

    void insertData_userId(QString& userName,QString& password);

    void serUsernameAndPassword(QString,QString);

    void rememberPassword_slot(QString,QString);

protected:
    void mouseMoveEvent(QMouseEvent* event) override;//鼠标移动事件 虚函数需要重写
    void mousePressEvent(QMouseEvent* event) override;//鼠标点击事件 虚函数需要重新


private slots:

    void on_login_released();

    void on_affirm_clicked();

    void on_enterClose_clicked();

    void on_returnButton_clicked();

    void on_login_clicked();

    void on_enter_clicked();

signals:
    void rememberPassword(QString);
    void createUser(QString);
    void confirmAccount(QString,QString);
private:
    QPoint z;

    Ui::Enter *ui;
};

#endif // ENTER_H

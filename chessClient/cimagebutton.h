#ifndef CIMAGEBUTTON_H
#define CIMAGEBUTTON_H

#include <QObject>
#include <QPushButton>
class CimageButton : public QPushButton
{
    Q_OBJECT
public:
    explicit CimageButton(int x,int y,QWidget *parent = nullptr);

signals:

private:
    QString imagePath;

};

#endif // CIMAGEBUTTON_H

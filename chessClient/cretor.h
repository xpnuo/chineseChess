#ifndef CRETOR_H
#define CRETOR_H

#include <QWidget>
#include <QMap>
#include <QLabel>
#include <QMouseEvent>
#include "piecesfactory.h"
#include "piecesbase.h"
class cretor : public QWidget
{
    Q_OBJECT
public:
    cretor(QWidget* parent = nullptr);
    ~cretor();
public:
    void cretorAll(bool);
    bool eventFilter(QObject* object,QEvent* event);
    QMap<QString, QVector<PiecesBase *> > &get_piecesHash();
    QVector<QLabel *> &get_label();
signals:
    void label_clicked(QLabel*);
private:
    piecesFactory* pieces;
    QWidget* parent;
    QVector<QLabel*> label;
    QMap<QString,QVector<PiecesBase*>> piecesHash;
};

#endif // CRETOR_H

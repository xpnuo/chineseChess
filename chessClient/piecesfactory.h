#ifndef PIECESFACTORY_H
#define PIECESFACTORY_H

#include "piecesbase.h"
class piecesFactory : public QWidget
{
    Q_OBJECT
public:
    piecesFactory(QWidget* preson = nullptr);

public:
    enum PIECES_TYPE{
        PAWM_RED = 1,
        PAWM_BLACK,
        ELEPHANT_RED,
        ELEPHANT_BLACK,
        SHOGUN_RED,
        SHOGUN_BLACK,
        OFFICERS_RED,
        OFFICERS_BLACK,
        CAR_RED,
        CAR_BLACK,
        SOLDIER_RED,
        SOLDIER_BLACK,
        CANNON_RED,
        CANNON_BLACK
    };
    PiecesBase* cretorPieces(piecesFactory::PIECES_TYPE);
private:
    QWidget* preson;
};

#endif // PIECESFACTORY_H

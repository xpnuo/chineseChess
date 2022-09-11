#include "piecesfactory.h"
#include "pawnpieces.h"
#include "elephantpieces.h"
#include "shogunpieces.h"
#include "officerspieces.h"
#include "carpieces.h"
#include "soldierpieces.h"
#include "cannonpieces.h"
piecesFactory::piecesFactory(QWidget* parent)
{
    preson = parent;
}

PiecesBase *piecesFactory::cretorPieces(piecesFactory::PIECES_TYPE TYPE)
{
    switch (TYPE) {
    case piecesFactory::PAWM_RED:
        return new pawnpieces(preson);
        break;
    case piecesFactory::PAWM_BLACK:{
        return new pawnpieces(preson);
        break;
    }
    case piecesFactory::ELEPHANT_RED:{
        return new elephantPieces(preson);
        break;
    }
    case piecesFactory::ELEPHANT_BLACK:{
        return new elephantPieces(preson);
        break;
    }
    case piecesFactory::SHOGUN_RED:{
        return new shogunPieces(preson);
        break;
    }
    case piecesFactory::SHOGUN_BLACK:{
        return new shogunPieces(preson);
        break;
    }
    case piecesFactory::OFFICERS_RED:{
        return new officersPieces(preson);
        break;
    }
    case piecesFactory::OFFICERS_BLACK:{
        return new officersPieces(preson);
        break;
    }
    case piecesFactory::CAR_RED:{
        return new carPieces(preson);
        break;
    }
    case piecesFactory::CAR_BLACK:{
        return new carPieces(preson);
        break;
    }
    case piecesFactory::SOLDIER_RED:{
        return new soldierPieces(preson);
        break;
    }
    case piecesFactory::SOLDIER_BLACK:{
        return new soldierPieces(preson);
        break;
    }
    case piecesFactory::CANNON_RED:{
        return new cannonPieces(preson);
    }
    case piecesFactory::CANNON_BLACK:{
        return new cannonPieces(preson);
    }
    default:
        return nullptr;
        break;
    }
    return nullptr;
}

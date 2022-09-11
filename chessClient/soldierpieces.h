#ifndef SOLDIERPIECES_H
#define SOLDIERPIECES_H

#include "piecesbase.h"

class soldierPieces : public PiecesBase
{
    Q_OBJECT
public:
    soldierPieces(QWidget* parson = nullptr);
    ~soldierPieces();
protected:
    bool move_rules(int ,int , QVector<QVector<PiecesBase*>>) override;
    void pieces_style(QString imagePath) override;
    void set_location(int,int) override;
    void can_location() override;
    void set_color(bool,int,int) override;
private:
    //CimageButton* button;
};

#endif // SOLDIERPIECES_H

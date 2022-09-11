#ifndef ELEPHANTPAWN_H
#define ELEPHANTPAWN_H

#include "piecesbase.h"
class elephantPieces : public PiecesBase
{
    Q_OBJECT
public:
    explicit elephantPieces(QWidget* parent = nullptr);
    ~elephantPieces();
    bool move_rules(int ,int , QVector<QVector<PiecesBase*>>) override;
    void pieces_style(QString imagePath) override;
    void set_location(int,int) override;
    void can_location() override;
    void set_color(bool,int,int) override;
private:
    //CimageButton* button;
};

#endif // ELEPHANTPAWN_H

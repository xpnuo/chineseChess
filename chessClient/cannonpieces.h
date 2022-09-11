#ifndef CANNONPIECES_H
#define CANNONPIECES_H

#include "piecesbase.h"

class cannonPieces : public PiecesBase
{
    Q_OBJECT
public:
    explicit cannonPieces(QWidget *parent = nullptr);
    ~cannonPieces();
protected:
    bool move_rules(int ,int , QVector<QVector<PiecesBase*>>) override;
    void pieces_style(QString imagePath) override;
    void set_location(int,int) override;
    void can_location() override;
    void set_color(bool,int,int) override;
private:
    //CimageButton* button;
};

#endif // CANNONPIECES_H

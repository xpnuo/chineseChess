#ifndef PAWNPIECES_H
#define PAWNPIECES_H
#include "piecesbase.h"
class pawnpieces : public PiecesBase
{
    Q_OBJECT
public:
    pawnpieces(QWidget* parent = nullptr);
    ~pawnpieces();
protected:
    bool move_rules(int ,int , QVector<QVector<PiecesBase*>>) override;
    void pieces_style(QString imagePath) override;
    void set_location(int,int) override;
    void can_location() override;
    void set_color(bool,int,int) override;
private:
    //CimageButton* button;

};

#endif // PAWNPIECES_H

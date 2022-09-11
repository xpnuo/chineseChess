#ifndef SHOGUNPIECES_H
#define SHOGUNPIECES_H

#include "piecesbase.h"
class shogunPieces : public PiecesBase
{
    Q_OBJECT
public:
    shogunPieces(QWidget* parson = nullptr);
    ~shogunPieces();
public:
    bool move_rules(int ,int , QVector<QVector<PiecesBase*>>) override;
    void pieces_style(QString imagePath) override;
    void set_location(int,int) override;
    void can_location() override;
    void set_color(bool,int,int) override;
signals:
private:
    //CimageButton* button;
};

#endif // SHOGUNPIECES_H

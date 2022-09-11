#ifndef CARPIECES_H
#define CARPIECES_H

#include "piecesbase.h"

class carPieces : public PiecesBase
{
    Q_OBJECT
public:
    explicit carPieces(QWidget *parent = nullptr);
    ~carPieces();
protected:
    bool move_rules(int ,int , QVector<QVector<PiecesBase*>>) override;
    void pieces_style(QString imagePath) override;
    void set_location(int,int) override;
    void can_location() override;
    void set_color(bool,int,int) override;
private:
    //CimageButton* button;

};

#endif // CARPIECES_H

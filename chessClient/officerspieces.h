#ifndef OFFICERSPIECES_H
#define OFFICERSPIECES_H
#include "piecesbase.h"

class officersPieces : public PiecesBase
{
    Q_OBJECT
public:
    explicit officersPieces(QWidget *parent = nullptr);
    ~officersPieces();
protected:
    bool move_rules(int ,int , QVector<QVector<PiecesBase*>>) override;
    void pieces_style(QString imagePath) override;
    void set_location(int,int) override;
    void can_location() override;
    void set_color(bool,int,int) override;
private:
    //CimageButton* button;
};

#endif // OFFICERSPIECES_H

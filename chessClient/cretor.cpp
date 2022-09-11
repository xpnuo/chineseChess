#include "cretor.h"
cretor::cretor(QWidget* parent) : QWidget(parent)
{
    this->pieces = new piecesFactory(parent);
    this->parent = parent;
}

cretor::~cretor()
{
    this->pieces->deleteLater();
    for(auto it = piecesHash.begin();it!=piecesHash.end();it++){
        for(auto i : it.value()){
            i->deleteLater();
        }
    }
}

void cretor::cretorAll(bool flag)
{
    for(int i=0;i<10;i++){
        for(int j=0;j<9;j++){
            QLabel* le = new QLabel("",this->parent);
            qDebug()<<le;
            le->resize(60,60);
            le->move(30+60*j,10+70*i);
            le->setAttribute(Qt::WA_TranslucentBackground);
            le->setStyleSheet("background:transparent");
            this->label.push_back(le);
            le->installEventFilter(this);
            le = nullptr;
        }
    }
    PiecesBase* tmp = nullptr;
    /******CAR_RED*****/
    tmp = pieces->cretorPieces(piecesFactory::CAR_RED);
    this->piecesHash["CAR_RED"].push_back(tmp);
    this->piecesHash["CAR_RED"].back()->set_color(flag ? true : false,30,10);
    tmp = pieces->cretorPieces(piecesFactory::CAR_RED);
    this->piecesHash["CAR_RED"].push_back(tmp);
    this->piecesHash["CAR_RED"].back()->set_color(flag ? true : false,510,10);
    tmp = pieces->cretorPieces(piecesFactory::CAR_BLACK);
    this->piecesHash["CAR_BLACK"].push_back(tmp);
    this->piecesHash["CAR_BLACK"].back()->set_color(flag ? false : true,30,640);
    tmp = pieces->cretorPieces(piecesFactory::CAR_BLACK);
    this->piecesHash["CAR_BLACK"].push_back(tmp);
    this->piecesHash["CAR_BLACK"].back()->set_color(flag ? false : true,510,640);
    /********PAWM_RED********/
    tmp = pieces->cretorPieces(piecesFactory::PAWM_RED);
    this->piecesHash["PAWM_RED"].push_back(tmp);
    this->piecesHash["PAWM_RED"].back()->set_color(flag ? true : false,90,10);
    tmp = pieces->cretorPieces(piecesFactory::PAWM_RED);
    this->piecesHash["PAWM_RED"].push_back(tmp);
    this->piecesHash["PAWM_RED"].back()->set_color(flag ? true : false,450,10);
    tmp = pieces->cretorPieces(piecesFactory::PAWM_BLACK);
    this->piecesHash["PAWM_BLACK"].push_back(tmp);
    this->piecesHash["PAWM_BLACK"].back()->set_color(flag ? false : true,90,640);
    tmp = pieces->cretorPieces(piecesFactory::PAWM_BLACK);
    this->piecesHash["PAWM_BLACK"].push_back(tmp);
    this->piecesHash["PAWM_BLACK"].back()->set_color(flag ? false : true,450,640);
    /*****ELEPHANT_RED*****/
    tmp = pieces->cretorPieces(piecesFactory::ELEPHANT_RED);
    this->piecesHash["ELEPHANT_RED"].push_back(tmp);
    this->piecesHash["ELEPHANT_RED"].back()->set_color(flag ? true : false,150,10);
    tmp = pieces->cretorPieces(piecesFactory::ELEPHANT_RED);
    this->piecesHash["ELEPHANT_RED"].push_back(tmp);
    this->piecesHash["ELEPHANT_RED"].back()->set_color(flag ? true : false,390,10);
    tmp = pieces->cretorPieces(piecesFactory::ELEPHANT_BLACK);
    this->piecesHash["ELEPHANT_BLACK"].push_back(tmp);
    this->piecesHash["ELEPHANT_BLACK"].back()->set_color(flag ? false : true,150,640);
    tmp = pieces->cretorPieces(piecesFactory::ELEPHANT_BLACK);
    this->piecesHash["ELEPHANT_BLACK"].push_back(tmp);
    this->piecesHash["ELEPHANT_BLACK"].back()->set_color(flag ? false : true,390,640);
    /******OFFICERS_RED*****/
    tmp = pieces->cretorPieces(piecesFactory::OFFICERS_RED);
    this->piecesHash["OFFICERS_RED"].push_back(tmp);
    this->piecesHash["OFFICERS_RED"].back()->set_color(flag ? true : false,210,10);
    tmp = pieces->cretorPieces(piecesFactory::OFFICERS_RED);
    this->piecesHash["OFFICERS_RED"].push_back(tmp);
    this->piecesHash["OFFICERS_RED"].back()->set_color(flag ? true : false,330,10);
    tmp = pieces->cretorPieces(piecesFactory::OFFICERS_BLACK);
    this->piecesHash["OFFICERS_BLACK"].push_back(tmp);
    this->piecesHash["OFFICERS_BLACK"].back()->set_color(flag ? false : true,210,640);
    tmp = pieces->cretorPieces(piecesFactory::OFFICERS_BLACK);
    this->piecesHash["OFFICERS_BLACK"].push_back(tmp);
    this->piecesHash["OFFICERS_BLACK"].back()->set_color(flag ? false : true,330,640);
    /*****SHOGUN_RED********/
    tmp = pieces->cretorPieces(piecesFactory::SHOGUN_RED);
    this->piecesHash["SHOGUN_RED"].push_back(tmp);
    this->piecesHash["SHOGUN_RED"].back()->set_color(flag ? true : false,270,10);
    tmp = pieces->cretorPieces(piecesFactory::SHOGUN_BLACK);
    this->piecesHash["SHOGUN_BLACK"].push_back(tmp);
    this->piecesHash["SHOGUN_BLACK"].back()->set_color(flag ? false : true,270,640);
    /******CANNON_RED*****/
    tmp = pieces->cretorPieces(piecesFactory::CANNON_RED);
    this->piecesHash["CANNON_RED"].push_back(tmp);
    this->piecesHash["CANNON_RED"].back()->set_color(flag ? true : false,90,150);
    tmp = pieces->cretorPieces(piecesFactory::CANNON_RED);
    this->piecesHash["CANNON_RED"].push_back(tmp);
    this->piecesHash["CANNON_RED"].back()->set_color(flag ? true : false,450,150);
    tmp = pieces->cretorPieces(piecesFactory::CANNON_BLACK);
    this->piecesHash["CANNON_BLACK"].push_back(tmp);
    this->piecesHash["CANNON_BLACK"].back()->set_color(flag ? false : true,90,500);
    tmp = pieces->cretorPieces(piecesFactory::CANNON_BLACK);
    this->piecesHash["CANNON_BLACK"].push_back(tmp);
    this->piecesHash["CANNON_BLACK"].back()->set_color(flag ? false : true,450,500);
    /******SOLDIER_RED*****/
    for(int i = 0,j = 30;i < 5; i++, j+=120){
        tmp = pieces->cretorPieces(piecesFactory::SOLDIER_RED);
        this->piecesHash["SOLDIER_RED"].push_back(tmp);
        this->piecesHash["SOLDIER_RED"].back()->set_color(flag ? true : false,j,220);
        tmp = pieces->cretorPieces(piecesFactory::SOLDIER_BLACK);
        this->piecesHash["SOLDIER_BLACK"].push_back(tmp);
        this->piecesHash["SOLDIER_BLACK"].back()->set_color(flag ? false : true,j,430);
    }
    tmp = nullptr;
}

bool cretor::eventFilter(QObject *object, QEvent *event)//鼠标点击移动事件的位置
{
    if (event->type() == QEvent::MouseButtonPress) //鼠标点击
    {
        qDebug()<<object<<"被按下";
        emit label_clicked((QLabel*)object);
        return true;
    }
    return false;
}

QMap<QString, QVector<PiecesBase *> > &cretor::get_piecesHash()
{
    return this->piecesHash;
}

QVector<QLabel *> &cretor::get_label()
{
    return this->label;
}


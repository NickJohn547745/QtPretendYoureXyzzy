#ifndef CARDCASTDECK_H
#define CARDCASTDECK_H

#include <QString>
#include <QList>
//#include </src/data/CardSet.h>
#include "src/cardcast/cardcastblackcard.h"
#include "src/cardcast/cardcastwhitecard.h"

class CardcastDeck //: public CardSet
{
private:
    QString name;
    QString code;
    QString description;
    QList<CardcastBlackCard*> *blackCards = new QList<CardcastBlackCard*>();
    QList<CardcastWhiteCard*> *whiteCards = new QList<CardcastWhiteCard*>();

public:
    CardcastDeck(const QString name, const QString code, const QString description);
    int getId();
    QString getName();
    QString getDescription();
    bool isActive();
    bool isBaseDeck();
    int getWeight();
    QList<CardcastBlackCard*>* getBlackCards();
    QList<CardcastWhiteCard*>* getWhiteCards();

};

#endif // CARDCASTDECK_H

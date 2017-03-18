#ifndef CARDCASTBLACKCARD_H
#define CARDCASTBLACKCARD_H

#include <QString>
//#include </src/data/BlackCard.h>

class CardcastBlackCard //: public BlackCard
{
private:
    int id;
    QString text;
    int draw;
    int pick;
    QString deckId;

public:
    CardcastBlackCard(const int passId, const QString passText, const int passDraw, const int passPick, const QString passDeckId);
    int getId();
    QString getText();
    QString getWatermark();
    int getDraw();
    int getPick();
};

#endif // CARDCASTBLACKCARD_H

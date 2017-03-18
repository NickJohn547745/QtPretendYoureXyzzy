#ifndef CARDCASTWHITECARD_H
#define CARDCASTWHITECARD_H

#include <QString>
//#include </src/data/WhiteCard.h>

class CardcastWhiteCard //: public WhiteCard
{
private:
    int id;
    QString text;
    QString deckId;

public:
    CardcastWhiteCard(const int id, const QString text, const QString deckId);
    int getId();
    QString getText();
    QString getWatermark();
    bool isWriteIn();
};

#endif // CARDCASTWHITECARD_H

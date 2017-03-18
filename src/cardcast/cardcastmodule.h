#ifndef CARDCASTMODULE_H
#define CARDCASTMODULE_H

#include <QAtomicInteger>

class CardcastModule
{
private:
    QAtomicInteger<int> *cardId = new QAtomicInteger<int>(-(GameOptions.MAX_BLANK_CARD_LIMIT + 1));

protected:
    void configure();
};

#endif // CARDCASTMODULE_H

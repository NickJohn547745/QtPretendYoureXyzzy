#ifndef CARDCASTCACHEENTRY_H
#define CARDCASTCACHEENTRY_H

#include "src/cardcast/cardcastdeck.h"

class CardcastCacheEntry
{
public:
    long expires;
    CardcastDeck* deck;
    CardcastCacheEntry(const long cacheLifetime, CardcastDeck *deck);
};

#endif // CARDCASTCACHEENTRY_H

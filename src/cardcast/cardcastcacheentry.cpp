#include "cardcastcacheentry.h"
#include <QTime>

CardcastCacheEntry::CardcastCacheEntry(const long cacheLifetime, CardcastDeck *deck)
{
    this->expires = QTime::currentTime().msec() + cacheLifetime;
    this->deck = deck;
}

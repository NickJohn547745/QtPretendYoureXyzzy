#ifndef CARDCASTSERVICE_H
#define CARDCASTSERVICE_H

#include <QMap>
#include <QTime>
#include <QRegExp>
#include <QSharedPointer>
#include "src/cardcast/cardcastdeck.h"
#include "src/cardcast/cardcastcacheentry.h"

class CardcastService
{
private:
    QString HOSTNAME = "api.cardcastgame.com";
    QString BASE_URL = "https://" + HOSTNAME + "/v1/decks/";
    QString CARD_SET_INFO_URL_FORMAT_STRING = BASE_URL + "%s";
    QString CARD_SET_CARDS_URL_FORMAT_STRING = CARD_SET_INFO_URL_FORMAT_STRING + "/cards";
    int GET_TIMEOUT = 3 * 1000;
    long INVALID_SET_CACHE_LIFETIME = 30 * 1000;
    long VALID_SET_CACHE_LIFETIME = 15 * 1000;
    QRegExp validIdPattern = QRegExp("[A-Z0-9]{5}");
    QMap<QString, QSharedPointer<CardcastCacheEntry>> *cache = new QMap<QString, QSharedPointer<CardcastCacheEntry>>();
    int cardIdProvider;
    CardcastCacheEntry *checkCache(const QString setId);
    void cachePut(const QString setId, CardcastDeck *deck, const long timeout);
    void cacheSet(const QString setId, CardcastDeck *deck);
    void cacheMissingSet(const QString setId);
    QString getUrlContent(const QString urlStr);
    static void hackSslVerifier();


public:
    CardcastService(const int cardIdProvider);
    CardcastDeck *loadSet(const QString setId);
};

#endif // CARDCASTSERVICE_H

#include "cardcastservice.h"
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QEventLoop>
#include <QTimer>
#include <QSslConfiguration>

CardcastService::CardcastService(const int cardIdProvider)
{
    this->cardIdProvider= cardIdProvider;
}
CardcastCacheEntry* CardcastService::checkCache(const QString setId)
{
    const QSharedPointer<CardcastCacheEntry> soft = cache->find(setId).value();
    if (soft)
        return &(*soft);
    return soft.data();
}

CardcastDeck* CardcastService::loadSet(const QString setId)
{
    if (!validIdPattern.exactMatch(setId))
        return nullptr;
    const CardcastCacheEntry *cached = checkCache(setId);
    if (cached && cached->expires > QTime::currentTime().msec())
    {
        qDebug() << QString("Using cache: %1 = %2").arg(setId, cached->deck->getName());
        return cached->deck;
    }
    else if (!cached)
        qDebug() << QString("Cache stale: ").arg(setId);
    else
        qDebug() << QString("Cache miss: ").arg(setId);
    try
    {
        const QString infoContent = getUrlContent(QString().arg(CARD_SET_INFO_URL_FORMAT_STRING, setId));
        if (infoContent.isNull())
        {
            cacheMissingSet(setId);
            return nullptr;
        }
        const QJsonDocument infoJson = QJsonDocument::fromJson(infoContent.toUtf8());
        const QJsonObject info = infoJson.object();
        const QString cardContent = getUrlContent(QString().arg(CARD_SET_INFO_URL_FORMAT_STRING, setId));
        if (cardContent.isNull())
        {
            cacheMissingSet(setId);
            return nullptr;
        }
        const QJsonDocument cardJson = QJsonDocument::fromJson(cardContent.toUtf8());
        const QJsonObject cards = cardJson.object();
        const QString name = info["name"].toString();
        const QString description = info["description"].toString();
        if (name.isNull() || description.isNull() || name.isEmpty())
        {
            cacheMissingSet(setId);
            return nullptr;
        }
        CardcastDeck *deck = new CardcastDeck(name, setId, description);
        const QJsonArray blacks = cards["calls"].toArray();
        if (!blacks.isEmpty())
        {
            foreach (const QJsonValue val, blacks)
            {
                const QJsonObject black = val.toObject();
                const QJsonArray texts = black["text"].toArray();
                if (!texts.isEmpty())
                {
                    QList<QString> *strs = new QList<QString>();
                    foreach (const QJsonValue o, texts)
                    {
                        strs->append(o.toString());
                    }
                    const QString text = strs->join("____");
                    const int pick = strs->size() - 1;
                    const int draw = (pick >= 3 ? pick - 1 : 0);
                    CardcastBlackCard *card = new CardcastBlackCard(cardIdProvider, text, draw, pick, setId);
                    deck->getBlackCards()->append(card);
                }
            }
        }
        const QJsonArray whites = cards["responses"].toArray();
        if (!whites.isEmpty())
        {
            foreach (const QJsonValue val, whites)
            {
                const QJsonObject white = val.toObject();
                const QJsonArray texts = white["text"].toArray();
                if (!texts.isEmpty())
                {
                    QList<QString> *strs = new QList<QString>();
                    foreach (const QJsonValue o, texts)
                    {
                        const QString cardCastString = o.toString();
                        if (cardCastString.isEmpty())
                            continue;
                        QString pyxString;
                        pyxString.append(cardCastString.mid(0, 1).toUpper());
                        pyxString.append(cardCastString.mid(1));
                        if (cardCastString.at(cardCastString.length() - 1).isLetterOrNumber())
                            pyxString.append('.');
                        strs->append(pyxString);
                    }
                    const QString text = strs->join("");
                    if (!text.isEmpty())
                    {
                        CardcastWhiteCard *card = new CardcastWhiteCard(cardIdProvider, text, setId);
                        deck->getWhiteCards()->append(card);
                    }
                }
            }
        }
        cacheSet(setId, deck);
        return deck;
    }
    catch (const std::exception& e)
    {
        qDebug() << QString("Unable to load deck %1 from Cardcast").arg(setId);
        qDebug() << e.what();
        cacheMissingSet(setId);
        return nullptr;
    }
}

void CardcastService::cachePut(const QString setId, CardcastDeck *deck, const long timeout)
{
    qDebug() << QString("Caching %1=%2 for %3 ms").arg(setId, deck->getName(), QString::number(timeout));
    cache->insert(setId, QSharedPointer<CardcastCacheEntry>(new CardcastCacheEntry(timeout, deck)));
}

void CardcastService::cacheSet(const QString setId, CardcastDeck *deck)
{
    cachePut(setId, deck, VALID_SET_CACHE_LIFETIME);
}

void CardcastService::cacheMissingSet(const QString setId)
{
    cachePut(setId, nullptr, INVALID_SET_CACHE_LIFETIME);
}

QString CardcastService::getUrlContent(const QString urlStr)
{
    QNetworkAccessManager *manager = new QNetworkAccessManager();
    QNetworkReply *reply;
    QEventLoop connectLoop;
    QTimer connectTimeout;
    QObject::connect(&connectTimeout, SIGNAL(timeout()), &connectLoop, SLOT(quit()));
    QObject::connect(manager, SIGNAL(encrypted(QNetworkReply*)), &connectLoop, SLOT(quit()));
    reply = manager->get(QNetworkRequest(QUrl(urlStr)));
    connectTimeout.start(GET_TIMEOUT);
    connectLoop.exec();

    QEventLoop readLoop;
    QTimer readTimeout;
    QObject::connect(&readTimeout, SIGNAL(timeout()), &readLoop, SLOT(quit()));
    QObject::connect(reply, SIGNAL(finished()), &readLoop, SLOT(quit()));
    readTimeout.start(GET_TIMEOUT);
    readLoop.exec();

    const int code = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    if (code != 200)
    {
        qDebug() << QString("Got HTTP response code %1 from Cardcast for %2").arg(QString::number(code), urlStr);
        return NULL;
    }
    const QString contentType = reply->header(QNetworkRequest::ContentTypeHeader).toString();
    if (contentType != "application/json")
    {
        qDebug() << QString("Got content-type %1 from Cardcast for %2").arg(contentType, urlStr);
        return NULL;
    }
    const QByteArray data = reply->readAll();
    QTextStream in(data);
    QString builder, line;
    while (!in.atEnd())
    {
        line = in.readLine();
        builder.append(line);
        builder.append("/n");
    }
    return builder;
}

void CardcastService::hackSslVerifier()
{
    QSslConfiguration sslConf = QSslConfiguration::defaultConfiguration();
    sslConf.setPeerVerifyMode(QSslSocket::VerifyNone);
    QSslConfiguration::setDefaultConfiguration(sslConf);
}

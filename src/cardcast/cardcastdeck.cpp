#include "cardcastdeck.h"

CardcastDeck::CardcastDeck(const QString name, const QString code, const QString description)
{
    this->name = name;
    this->code = code;
    this->description = description;
}

int CardcastDeck::getId()
{
    bool ok;
    return -code.toInt(&ok, 36);
}

QString CardcastDeck::getName()
{
    return name;
}

QString CardcastDeck::getDescription()
{
    return description;
}

bool CardcastDeck::isActive()
{
    return true;
}

bool CardcastDeck::isBaseDeck()
{
    return false;
}

int CardcastDeck::getWeight()
{
    return INT_MAX;
}

QList<CardcastBlackCard*>* CardcastDeck::getBlackCards()
{
    return blackCards;
}

QList<CardcastWhiteCard*>* CardcastDeck::getWhiteCards()
{
    return whiteCards;
}

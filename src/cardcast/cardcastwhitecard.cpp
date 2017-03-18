#include "cardcastwhitecard.h"

CardcastWhiteCard::CardcastWhiteCard(const int id, const QString text, const QString deckId)
{
    this->id = id;
    this->text = text;
    this->deckId = deckId;
}

int CardcastWhiteCard::getId()
{
    return id;
}

QString CardcastWhiteCard::getText()
{
    return text;
}

QString CardcastWhiteCard::getWatermark()
{
    return deckId;
}

bool CardcastWhiteCard::isWriteIn()
{
    return false;
}

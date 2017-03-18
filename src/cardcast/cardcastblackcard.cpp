#include "cardcastblackcard.h"

CardcastBlackCard::CardcastBlackCard(const int id, const QString text, const int draw, const int pick, const QString deckId)
{
    this->id = id;
    this->text = text;
    this->draw = draw;
    this->pick = pick;
    this->deckId = deckId;
}

int CardcastBlackCard::getId()
{
    return id;
}

QString CardcastBlackCard::getText()
{
    return text;
}

QString CardcastBlackCard::getWatermark()
{
    return deckId;
}

int CardcastBlackCard::getDraw()
{
    return draw;
}

int CardcastBlackCard::getPick()
{
    return pick;
}


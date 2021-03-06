#include "pyxblackcard.h"

int PyxBlackCard::getId()
{
    return id;
}

void PyxBlackCard::setId(const int id)
{
    this->id = id;
}

QString PyxBlackCard::getText()
{
    return text;
}

void PyxBlackCard::setText(const QString text)
{
    this->text = text;
}

int PyxBlackCard::getDraw()
{
    return draw;
}

void PyxBlackCard::setDraw(const int draw)
{
    this->draw = draw;
}

int PyxBlackCard::getPick()
{
    return pick;
}

void PyxBlackCard::setPick(const int pick)
{
    this->pick = pick;
}

QString PyxBlackCard::getWatermark()
{
    return watermark;
}

void PyxBlackCard::setWatermark(const QString watermark)
{
    this->watermark = watermark;
}

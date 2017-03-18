#ifndef PYXBLACKCARD_H
#define PYXBLACKCARD_H

//#include "./src/cardcast/BlackCard.h"
#include <QString>

class PyxBlackCard : public BlackCard
{
private:
    int id;
    QString text;
    int pick;
    QString watermark;

public:
    int getId();
    void setId(const int id);
    QString getText();
    void setText(const QString text);
    int getDraw();
    void setDraw(const int draw);
    int getPick();
    void setPick(const int pick);
    QString getWatermark();
    void setWatermark(const QString watermark);
};

#endif // PYXBLACKCARD_H

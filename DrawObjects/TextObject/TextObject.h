//
// Created by spp16 on 21.07.2026.
//

#ifndef SIMPLE_WINDOW_TEXTOBJECT_H
#define SIMPLE_WINDOW_TEXTOBJECT_H
#include <qpen.h>

#include "../BaseDraw.h"


class TextObject : public BaseDraw {
public:
    TextObject();
    TextObject(QPen _pen, std::string _text, QPoint _pos);
    void Draw(QPainter& painter) const override;

private:
    std::string text;
    QPoint pos;
    QPen pen;

};


#endif //SIMPLE_WINDOW_TEXTOBJECT_H

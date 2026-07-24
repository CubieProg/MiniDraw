//
// Created by spp16 on 21.07.2026.
//

#ifndef SIMPLE_WINDOW_CIRCLEOBJECT_H
#define SIMPLE_WINDOW_CIRCLEOBJECT_H
#include "../BaseDraw.h"


class CircleObject : public BaseDraw {
public:
    CircleObject();
    CircleObject(QPen _pen, QPoint& _atopLeft, QPoint& _abottomRight);
    void Draw(QPainter& painter) const override;

private:
    QPen pen;
    QPoint atopLeft;
    QPoint abottomRight;
};


#endif //SIMPLE_WINDOW_CIRCLEOBJECT_H

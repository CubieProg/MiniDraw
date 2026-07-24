//
// Created by spp16 on 21.07.2026.
//

#ifndef SIMPLE_WINDOW_LINEOBJECT_H
#define SIMPLE_WINDOW_LINEOBJECT_H
#include <qpen.h>
#include <vector>

#include "../BaseDraw.h"


class LineObject : public BaseDraw {
public:
    LineObject() = default;
    LineObject(std::vector<QPoint>& _points, QPen _pen, QPoint& atopLeft, QPoint& abottomRight);

    void Draw(QPainter& painter) const override;

private:
    QPen pen;
    std::vector<QPoint> points;
};


#endif //SIMPLE_WINDOW_LINEOBJECT_H

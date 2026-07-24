#ifndef SIMPLE_WINDOW_ARROWOBJECT_H
#define SIMPLE_WINDOW_ARROWOBJECT_H
#include <qpen.h>

#include "../BaseDraw.h"


class ArrowObject : public BaseDraw {

public:
    ArrowObject();
    ArrowObject(QPen _pen, QPoint& _startPoint, QPoint& _endPoint);
    void Draw(QPainter& painter) const override;

private:
    QPen pen;
    QPoint startPoint;
    QPoint endPoint;
};


#endif //SIMPLE_WINDOW_ARROWOBJECT_H

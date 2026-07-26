#ifndef MINIDRAW_ARROWOBJECT_H
#define MINIDRAW_ARROWOBJECT_H
#include <qpen.h>

#include "../BaseDraw.h"


class ArrowObject : public BaseDraw {

public:
    ArrowObject();
    ArrowObject(QPen _pen, QPoint& _startPoint, QPoint& _endPoint);
    void Draw(QPainter& painter) const override;
    rapidjson::Value JSONRepr(rapidjson::MemoryPoolAllocator<> allocator) const override;

private:
    // QPen pen;
    QPoint startPoint;
    QPoint endPoint;
};


#endif //MINIDRAW_ARROWOBJECT_H

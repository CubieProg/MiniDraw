//
// Created by spp16 on 21.07.2026.
//

#ifndef MINIDRAW_RECTOBJECT_H
#define MINIDRAW_RECTOBJECT_H
#include <qpen.h>

#include "../BaseDraw.h"


class RectObject : public BaseDraw {
public:
    RectObject();
    RectObject(QPen _pen, QPoint& _atopLeft, QPoint& _abottomRight);
    void Draw(QPainter& painter) const override;
    rapidjson::Value JSONRepr(rapidjson::MemoryPoolAllocator<> allocator) const override;

private:
    // QPen pen;
    QPoint atopLeft;
    QPoint abottomRight;
};


#endif //MINIDRAW_RECTOBJECT_H

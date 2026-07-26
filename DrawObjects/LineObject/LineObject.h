//
// Created by spp16 on 21.07.2026.
//

#ifndef MINIDRAW_LINEOBJECT_H
#define MINIDRAW_LINEOBJECT_H
#include <qpen.h>
#include <vector>

#include "../BaseDraw.h"


class LineObject : public BaseDraw {
public:
    LineObject() = default;
    LineObject(std::vector<QPoint>& _points, QPen _pen, QPoint& atopLeft, QPoint& abottomRight);

    void Draw(QPainter& painter) const override;
    rapidjson::Value JSONRepr(rapidjson::MemoryPoolAllocator<> allocator) const override;

    static shared_ptr<LineObject> FromJSON(const rapidjson::Value& json);

private:
    // QPen pen;
    std::vector<QPoint> points;
};


#endif //MINIDRAW_LINEOBJECT_H

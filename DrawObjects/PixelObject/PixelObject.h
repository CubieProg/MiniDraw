//
// Created by spp16 on 21.07.2026.
//

#ifndef MINIDRAW_PIXELOBJECT_H
#define MINIDRAW_PIXELOBJECT_H
#include "../BaseDraw.h"

class PixelObject : public BaseDraw {
public:
    // PixelObject();
    PixelObject(QImage& image, QRect& boundingRect);
    PixelObject(QImage& image, QPoint& atopLeft, QPoint& abottomRight);
    void Draw(QPainter& painter) const override;
    rapidjson::Value JSONRepr(rapidjson::MemoryPoolAllocator<> allocator) const override;
};


#endif //MINIDRAW_PIXELOBJECT_H

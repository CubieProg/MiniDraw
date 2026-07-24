//
// Created by spp16 on 21.07.2026.
//

#ifndef SIMPLE_WINDOW_PIXELOBJECT_H
#define SIMPLE_WINDOW_PIXELOBJECT_H
#include "../BaseDraw.h"

class PixelObject : public BaseDraw {
public:
    PixelObject();
    PixelObject(QImage& image, QRect& boundingRect);
    PixelObject(QImage& image, QPoint& atopLeft, QPoint& abottomRight);
    void Draw(QPainter& painter) const override;
};


#endif //SIMPLE_WINDOW_PIXELOBJECT_H

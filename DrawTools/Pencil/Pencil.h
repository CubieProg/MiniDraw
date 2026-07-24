//
// Created by spp16 on 21.07.2026.
//

#ifndef SIMPLE_WINDOW_PENCIL_H
#define SIMPLE_WINDOW_PENCIL_H
#include "../BaseTool.h"
#include "../../DrawObjects/PixelObject/PixelObject.h"


class Pencil : public BaseTool {
public:
    Pencil();
    ~Pencil() override = default;

    ToolMessage OnPress(const QMouseEvent* event) override;
    ToolMessage OnRelease(const QMouseEvent* event) override;
    ToolMessage OnMove(const QMouseEvent* event) override;

    shared_ptr<BaseDraw> ProduceDrawObject(QImage& image, QPoint atopLeft, QPoint abottomRight) override;

private:
    QPoint position;
    QPoint lastPosition;
};


#endif //SIMPLE_WINDOW_PENCIL_H

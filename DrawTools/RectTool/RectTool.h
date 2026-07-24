//
// Created by spp16 on 21.07.2026.
//

#ifndef SIMPLE_WINDOW_RECTTOOL_H
#define SIMPLE_WINDOW_RECTTOOL_H
#include "../BaseTool.h"


class RectTool : public BaseTool {
public:
    RectTool();
    ~RectTool() = default;

    ToolMessage OnPress(const QMouseEvent* event) override;
    ToolMessage OnRelease(const QMouseEvent* event) override;
    ToolMessage OnMove(const QMouseEvent* event) override;

    shared_ptr<BaseDraw> ProduceDrawObject(QImage& image, QPoint atopLeft, QPoint abottomRight) override;

private:
    QPoint atopLeft;
    QPoint abottomRight;
};


#endif //SIMPLE_WINDOW_RECTTOOL_H

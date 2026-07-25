//
// Created by spp16 on 21.07.2026.
//

#ifndef MINIDRAW_ARROWTOOL_H
#define MINIDRAW_ARROWTOOL_H
#include "../BaseTool.h"


class ArrowTool : public BaseTool {
public:
    ArrowTool();
    ~ArrowTool() = default;

    ToolMessage OnPress(const QMouseEvent* event) override;
    ToolMessage OnRelease(const QMouseEvent* event) override;
    ToolMessage OnMove(const QMouseEvent* event) override;

    shared_ptr<BaseDraw> ProduceDrawObject(QImage& image, QPoint atopLeft, QPoint abottomRight) override;
private:
    QPoint startPoint;
    QPoint endPoint;
};


#endif //MINIDRAW_ARROWTOOL_H

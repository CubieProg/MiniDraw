//
// Created by spp16 on 21.07.2026.
//

#ifndef MiniDraw_SELECTTOOL_H
#define MiniDraw_SELECTTOOL_H
#include "../BaseTool.h"


class SelectTool : public BaseTool {
public:
    SelectTool();
    ~SelectTool() = default;

    ToolMessage OnPress(const QMouseEvent* event) override;
    ToolMessage OnRelease(const QMouseEvent* event) override;
    ToolMessage OnMove(const QMouseEvent* event) override;

    shared_ptr<BaseDraw> ProduceDrawObject(QImage& image, QPoint atopLeft, QPoint abottomRight) override;
};


#endif //MiniDraw_SELECTTOOL_H

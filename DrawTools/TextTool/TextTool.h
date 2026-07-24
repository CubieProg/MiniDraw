//
// Created by spp16 on 21.07.2026.
//

#ifndef SIMPLE_WINDOW_TEXTTOOL_H
#define SIMPLE_WINDOW_TEXTTOOL_H
#include "../BaseTool.h"


class TextTool : public BaseTool {
public:
    TextTool();
    ~TextTool() = default;

    ToolMessage OnPress(const QMouseEvent* event) override;
    ToolMessage OnRelease(const QMouseEvent* event) override;
    ToolMessage OnMove(const QMouseEvent* event) override;

    shared_ptr<BaseDraw> ProduceDrawObject(QImage& image, QPoint atopLeft, QPoint abottomRight) override;

    ToolMessage ProcessModalResponse(bool& ok, QString response);

private:
    std::string text;
    QPoint pos;

};


#endif //SIMPLE_WINDOW_TEXTTOOL_H

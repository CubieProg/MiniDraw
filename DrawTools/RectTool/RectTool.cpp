//
// Created by spp16 on 21.07.2026.
//

#include "RectTool.h"

#include <QPainter>

#include "../../DrawObjects/RectObject/RectObject.h"

RectTool::RectTool() : BaseTool() {
    toolType = ToolType::RectTool;
    toolName = "RectTool";
}

ToolMessage RectTool::OnPress(const QMouseEvent* event) {
    if (event->button() != Qt::LeftButton) return ToolMessage::NOTHING;

    atopLeft = event->pos();
    abottomRight = event->pos();

    state = ToolState::ACTIVE;
    return ToolMessage::ENTER;
};



ToolMessage RectTool::OnRelease(const QMouseEvent* event) {
    if (event->button() != Qt::LeftButton) return ToolMessage::NOTHING;

    state = ToolState::DISABLED;
    return ToolMessage::QUIT;
};

ToolMessage RectTool::OnMove(const QMouseEvent* event) {
    if (state == ToolState::DISABLED) return ToolMessage::NOTHING;

    QPainter painter(paintSurface);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(pen);

    paintSurface->fill(Qt::transparent);

    QRect ellipseRect = QRect(atopLeft, abottomRight);
    painter.drawRect(ellipseRect);

    abottomRight = event->pos();

    return ToolMessage::CONTINUE;
};


shared_ptr<BaseDraw> RectTool::ProduceDrawObject(QImage& image, QPoint atopLeft, QPoint abottomRight) {
    auto new_object = std::make_shared<RectObject>(pen, this->atopLeft, this->abottomRight);
    return new_object;
}
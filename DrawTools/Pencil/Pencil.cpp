#include "Pencil.h"
#include <QPainter>

#include "../../DrawObjects/PixelObject/PixelObject.h"

Pencil::Pencil() : BaseTool() {
    toolName = "Pencil";
    toolType = ToolType::Pencil;
}


ToolMessage Pencil::OnPress(const QMouseEvent* event) {
    if (event->button() != Qt::LeftButton) return ToolMessage::NOTHING;

    position = event->pos();
    lastPosition = position;

    state = ToolState::ACTIVE;
    return ToolMessage::ENTER;
};


ToolMessage Pencil::OnRelease(const QMouseEvent* event) {
    if (event->button() != Qt::LeftButton) return ToolMessage::NOTHING;

    state = ToolState::DISABLED;
    return ToolMessage::QUIT;
};

ToolMessage Pencil::OnMove(const QMouseEvent* event) {
    if (state == ToolState::DISABLED) return ToolMessage::NOTHING;

    QPainter painter(paintSurface);
    painter.setRenderHint(QPainter::Antialiasing);

    position = event->pos();

    painter.setPen(pen);
    painter.drawLine(lastPosition, position);
    lastPosition = event->pos();

    return ToolMessage::CONTINUE;
};


shared_ptr<BaseDraw> Pencil::ProduceDrawObject(QImage& image, QPoint atopLeft, QPoint abottomRight) {
    auto new_object = std::make_shared<PixelObject>(image, atopLeft, abottomRight);
    return new_object;
}
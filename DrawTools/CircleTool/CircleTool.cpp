//
// Created by spp16 on 21.07.2026.
//

#include "CircleTool.h"

#include <QPainter>

#include "../BaseTool.h"
#include "../../DrawObjects/CircleObject/CircleObject.h"


CircleTool::CircleTool() : BaseTool() {
    toolType = ToolType::CircleTool;
    toolName = "CircleTool";
}



ToolMessage CircleTool::OnPress(const QMouseEvent* event) {
    if (event->button() != Qt::LeftButton) return ToolMessage::NOTHING;

    atopLeft = event->pos();
    abottomRight = event->pos();

    state = ToolState::ACTIVE;
    return ToolMessage::ENTER;
};



ToolMessage CircleTool::OnRelease(const QMouseEvent* event) {
    if (event->button() != Qt::LeftButton) return ToolMessage::NOTHING;

    state = ToolState::DISABLED;
    return ToolMessage::QUIT;
};

ToolMessage CircleTool::OnMove(const QMouseEvent* event) {
    if (state == ToolState::DISABLED) return ToolMessage::NOTHING;

    QPainter painter(paintSurface);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(pen);

    paintSurface->fill(Qt::transparent);

    QRect ellipseRect = QRect(atopLeft, abottomRight);
    painter.drawEllipse(ellipseRect);

    abottomRight = event->pos();

    return ToolMessage::CONTINUE;
};


shared_ptr<BaseDraw> CircleTool::ProduceDrawObject(QImage& image, QPoint atopLeft, QPoint abottomRight) {
    auto new_object = std::make_shared<CircleObject>(pen, this->atopLeft, this->abottomRight);

    return new_object;
}
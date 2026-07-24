//
// Created by spp16 on 21.07.2026.
//

#include "ArrowTool.h"

#include <QPainter>

#include "../BaseTool.h"
#include "../../DrawObjects/ArrowObject/ArrowObject.h"

using namespace std;

ArrowTool::ArrowTool() : BaseTool() {
    toolType = ToolType::ArrowTool;
    toolName = "ArrowTool";
}



ToolMessage ArrowTool::OnPress(const QMouseEvent* event) {
    if (event->button() != Qt::LeftButton) return ToolMessage::NOTHING;

    startPoint = event->pos();
    endPoint = event->pos();

    state = ToolState::ACTIVE;
    return ToolMessage::ENTER;
};



ToolMessage ArrowTool::OnRelease(const QMouseEvent* event) {
    if (event->button() != Qt::LeftButton) return ToolMessage::NOTHING;

    state = ToolState::DISABLED;
    return ToolMessage::QUIT;
};

ToolMessage ArrowTool::OnMove(const QMouseEvent* event) {
    if (state == ToolState::DISABLED) return ToolMessage::NOTHING;

    QPainter painter(paintSurface);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(pen);
    painter.setBrush(QBrush(pen.color()));

    paintSurface->fill(Qt::transparent);


    qreal arrowSize = pen.width()*2;
    QLineF line(startPoint, endPoint);

    double angle = std::atan2(-line.dy(), line.dx());
    auto add_angle = M_PI / 3;

    QPointF arrowP1 = line.p2() - QPointF(
        sin(angle + add_angle),
        cos(angle + add_angle)
        ) * arrowSize;

    QPointF arrowP2 = line.p2() - QPointF(
        sin(angle + M_PI - add_angle),
        cos(angle + M_PI - add_angle)
        ) * arrowSize;

    QPolygonF arrowHead;
    arrowHead << line.p2() << arrowP1 << arrowP2;


    painter.drawLine(line);
    painter.drawPolygon(arrowHead);


    endPoint = event->pos();

    return ToolMessage::CONTINUE;
};


shared_ptr<BaseDraw> ArrowTool::ProduceDrawObject(QImage& image, QPoint atopLeft, QPoint abottomRight) {
    auto new_object = std::make_shared<ArrowObject>(pen, this->startPoint, this->endPoint);
    return new_object;
}
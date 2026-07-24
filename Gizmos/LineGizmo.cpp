//
// Created by spp16 on 24.07.2026.
//

#include "LineGizmo.h"

#include <QPainter>


LineGizmo::LineGizmo() : BaseGizmo() {
    type = GizmoType::Line;
}

LineGizmo::LineGizmo(QPoint _start, QPoint _end) : BaseGizmo() {
    start = _start;
    end = _end;
    type = GizmoType::Line;
}

void LineGizmo::MovePosition(const QPoint& delta) {
    start += delta;
    end += delta;
}

void LineGizmo::Draw(QPainter& painter) const {
    auto last_pen = painter.pen();

    QPen pen(Qt::blue, 1);
    painter.setPen(pen);


    painter.drawLine(start, end);

    painter.setPen(last_pen);
}

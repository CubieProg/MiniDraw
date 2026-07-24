//
// Created by spp16 on 24.07.2026.
//

#include "DotGizmo.h"

#include <QPainter>


DotGizmo::DotGizmo() : BaseGizmo() {
    type = GizmoType::Dot;
}

DotGizmo::DotGizmo(QPoint _point) : BaseGizmo() {
    point = _point;
    type = GizmoType::Dot;
}

void DotGizmo::MovePosition(const QPoint& delta) {
    point += delta;
}

void DotGizmo::Draw(QPainter& painter) const {
    auto last_pen = painter.pen();

    QPen pen(Qt::blue, 1);
    painter.setPen(pen);

    QRect dotRect = QRect(
        point.x() - dotGizmoWidth,
        point.y() - dotGizmoWidth,
        2*dotGizmoWidth,
        2*dotGizmoWidth
    );

    painter.drawRect(dotRect);

    painter.setPen(last_pen);
}

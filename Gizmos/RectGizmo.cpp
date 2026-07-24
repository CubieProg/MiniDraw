//
// Created by spp16 on 24.07.2026.
//

#include "RectGizmo.h"

#include <QPainter>

#include "../QtUtils/QtUtils.h"

RectGizmo::RectGizmo() : BaseGizmo() {
    type = GizmoType::Rect;
}

RectGizmo::RectGizmo(QRect _rect) : BaseGizmo() {
    rect = _rect;
    type = GizmoType::Rect;
}


void RectGizmo::MovePosition(const QPoint& delta) {
    QPoint currentPosition = QPoint(rect.x(), rect.y());
    utils::UpdateRect(rect, currentPosition + delta);
}

void RectGizmo::Draw(QPainter& painter) const {
    // auto gizmoSurface = QImage(rect.size(), QImage::Format_ARGB32_Premultiplied);
    // QPainter gizmoPainter(&gizmoSurface);
    // gizmoSurface.fill(Qt::transparent);

    // QPainter painter(&surface);

    auto last_pen = painter.pen();

    QPen pen(Qt::blue, 1);
    painter.setPen(pen);

    painter.drawRect(rect);


    painter.setPen(last_pen);
}

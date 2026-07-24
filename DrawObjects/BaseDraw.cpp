//
// Created by spp16 on 21.07.2026.
//

#include <iostream>
#include "BaseDraw.h"

#include "../QtUtils/QtUtils.h"

BaseDraw::BaseDraw() {

}

BaseDraw::BaseDraw(const std::string& name) : name(name) {

}

void BaseDraw::DrawGizmos(QPainter& painter) const {
    for (const auto gizmo : gizmos) {
        gizmo->Draw(painter);
    }
}


QPoint BaseDraw::GetPosition() const {
    return QPoint(
        boundingRect.x(),
        boundingRect.y()
    );
}

void BaseDraw::SetPos(const QPoint& pos) {
    QPoint delta = pos - GetPosition();
    utils::UpdateRect(boundingRect, pos);

    std::for_each(gizmos.begin(), gizmos.end(), [delta](auto gizmo) { gizmo->MovePosition(delta); });
}
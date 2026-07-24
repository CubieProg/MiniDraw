//
// Created by spp16 on 21.07.2026.
//

#include <iostream>
#include "BaseDraw.h"

BaseDraw::BaseDraw() {

}

BaseDraw::BaseDraw(const std::string& name) : name(name) {

}

void BaseDraw::SetName(const std::string& _name) {
    this->name = _name;
}



QRect BaseDraw::GetBoundingRect() const {
    return QRect(boundingRect);
}

std::string BaseDraw::GetName() const {
    return name;
}

void BaseDraw::DrawGizmos(QPainter& painter) const {

    for (const auto gizmo : gizmos) {

        gizmo->Draw(painter);

        // switch (gizmo->GetType()) {
        //     case GizmoType::Base:
        //
        //         break;
        // }
    }
}

void BaseDraw::SetPos(const QPoint& pos) {
    boundingRect.setX(pos.x());
    boundingRect.setY(pos.y());
}
//
// Created by spp16 on 24.07.2026.
//

#ifndef MINIDRAW_BASEGIZMO_H
#define MINIDRAW_BASEGIZMO_H

#include <QColor>
#include <QImage>

enum class GizmoType {
    Base,
    Rect,
    Dot,
    Line
};

class BaseGizmo {
public:
    BaseGizmo();
    virtual ~BaseGizmo() = default;

    virtual void Draw(QPainter& painter) const = 0;

    GizmoType GetType() const {return type;}

protected:
    QColor color;
    GizmoType type = GizmoType::Base;
    // QImage gizmoSurface;
};


#endif //MINIDRAW_BASEGIZMO_H

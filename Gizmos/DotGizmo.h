//
// Created by spp16 on 24.07.2026.
//

#ifndef MINIDRAW_DOTGIZMO_H
#define MINIDRAW_DOTGIZMO_H
#include "BaseGizmo.h"


class DotGizmo : public BaseGizmo {
public:
    DotGizmo();
    DotGizmo(QPoint _point);
    ~DotGizmo() = default;

    void Draw(QPainter& painter) const override;
    void MovePosition(const QPoint& point) override;

private:
    QPoint point;
    int dotGizmoWidth = 4;
};


#endif //MINIDRAW_DOTGIZMO_H

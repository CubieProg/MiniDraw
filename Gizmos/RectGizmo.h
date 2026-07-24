//
// Created by spp16 on 24.07.2026.
//

#ifndef MINIDRAW_RECTGIZMO_H
#define MINIDRAW_RECTGIZMO_H
#include "BaseGizmo.h"


class RectGizmo : public BaseGizmo {
public:
    RectGizmo();
    RectGizmo(QRect rect);
    ~RectGizmo() = default;

    void Draw(QPainter& painter) const override;
    void MovePosition(const QPoint& point) override;

private:
    QRect rect;
};


#endif //MINIDRAW_RECTGIZMO_H

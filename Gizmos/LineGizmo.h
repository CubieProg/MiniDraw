//
// Created by spp16 on 24.07.2026.
//

#ifndef MINIDRAW_LINEGIZMO_H
#define MINIDRAW_LINEGIZMO_H
#include "BaseGizmo.h"


class LineGizmo : public BaseGizmo{
public:
    LineGizmo();
    LineGizmo(QPoint _start, QPoint _end);
    ~LineGizmo() = default;

    void Draw(QPainter& painter) const override;
    void MovePosition(const QPoint& point) override;

private:
    QPoint start;
    QPoint end;
};


#endif //MINIDRAW_LINEGIZMO_H

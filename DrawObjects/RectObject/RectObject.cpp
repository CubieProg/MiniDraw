//
// Created by spp16 on 21.07.2026.
//

#include "RectObject.h"

#include <QPainter>
#include <qpen.h>

#include "../../Gizmos/RectGizmo.h"
// #include "../Gizmos/BaseGizmo.h"


RectObject::RectObject() : BaseDraw("Rect object") {

};

RectObject::RectObject(QPen _pen, QPoint& _atopLeft, QPoint& _bottomRight) : BaseDraw("Rect object") {
    atopLeft = QPoint(
        std::min(_atopLeft.x(), _bottomRight.x()),
        std::min(_atopLeft.y(), _bottomRight.y())
    );
    abottomRight = QPoint(
        std::max(_atopLeft.x(), _bottomRight.x()),
        std::max(_atopLeft.y(), _bottomRight.y())
    );

    this->pen = _pen;
    auto halfPenSize = QPoint(pen.width() / 2, pen.width() / 2);
    this->boundingRect = QRect(atopLeft - halfPenSize, abottomRight + halfPenSize);


    surface = QImage(this->boundingRect.size(), QImage::Format_ARGB32_Premultiplied);
    surface.fill(Qt::transparent);

    QPainter painter(&surface);

    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(pen);

    QRect ellipseRect = boundingRect;
    ellipseRect.setX(0);
    ellipseRect.setY(0);

    painter.drawRect(
        pen.width()/2,
        pen.width()/2,
        boundingRect.width() - pen.width(),
        boundingRect.height() - pen.width()
    );

    gizmos.push_back(make_shared<RectGizmo>(boundingRect));
}

void RectObject::Draw(QPainter& painter) const {
    painter.drawImage(boundingRect.x(), boundingRect.y(), surface);
    DrawGizmos(painter);
}
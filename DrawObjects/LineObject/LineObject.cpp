//
// Created by spp16 on 21.07.2026.
//

#include "LineObject.h"

#include <iostream>
#include <ostream>
#include <QPainter>


LineObject::LineObject(std::vector<QPoint>& _points, QPen _pen, QPoint& atopLeft, QPoint& abottomRight) : BaseDraw("Line object") {

    this->points = std::vector<QPoint>(_points);
    this->points = _points;

    this->boundingRect = QRect(atopLeft, abottomRight);
    this->pen = _pen;

    surface = QImage(this->boundingRect.size(), QImage::Format_ARGB32_Premultiplied);
    surface.fill(Qt::transparent);

    QPainter painter(&surface);

    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(pen);


    if (points.size() == 1) {
        QBrush circlePen(pen.color());
        painter.setBrush(circlePen);
        painter.setPen(QPen(Qt::transparent));

        auto point = points[0] - atopLeft;
        painter.drawLine(point, point);
        painter.drawEllipse(point, pen.width()/2, pen.width()/2);

        painter.setBrush(QBrush());
        painter.setPen(pen);
    }

    if (points.size() >= 2) {
        for (
            auto left = points.begin(), right = left+1;
            right != points.end();
            ++left, ++right
        ) {
            painter.drawLine(*left - atopLeft, *right - atopLeft);
        }
    }

}

void LineObject::Draw(QPainter& painter) const {
    painter.drawImage(boundingRect.x(), boundingRect.y(), surface);
}
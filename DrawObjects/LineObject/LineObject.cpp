//
// Created by spp16 on 21.07.2026.
//

#include "LineObject.h"

#include <QPainter>

#include "../../Gizmos/DotGizmo.h"
#include "../../Gizmos/LineGizmo.h"
#include "../../Gizmos/RectGizmo.h"

LineObject::LineObject(std::vector<QPoint>& _points, QPen _pen, QPoint& atopLeft, QPoint& abottomRight) : BaseDraw("Line object") {
    type = DrawObjectType::LINE_OBJECT;

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

        gizmos.push_back(make_shared<DotGizmo>(point));
    }

    if (points.size() >= 2) {
        gizmos.push_back(make_shared<DotGizmo>(points[0]));

        for (
            auto left = points.begin(), right = left+1;
            right != points.end();
            ++left, ++right
        ) {
            painter.drawLine(*left - atopLeft, *right - atopLeft);


            gizmos.push_back(make_shared<LineGizmo>(*left, *right));
            gizmos.push_back(make_shared<DotGizmo>(*right));
        }
    }

}

void LineObject::Draw(QPainter& painter) const {
    painter.drawImage(boundingRect.x(), boundingRect.y(), surface);
}

rapidjson::Value LineObject::JSONRepr(rapidjson::MemoryPoolAllocator<> allocator) const {
    rapidjson::Value temp(rapidjson::kObjectType);
    temp.AddMember("Type", "LineObject", allocator);

    rapidjson::Value pointsArray(rapidjson::kArrayType);

    for (auto point : points) {
        rapidjson::Value pointNode(rapidjson::kArrayType);

        pointNode.PushBack(point.x(), allocator);
        pointNode.PushBack(point.y(), allocator);
        pointsArray.PushBack(pointNode, allocator);
    }
    temp.AddMember("Points", pointsArray, allocator);

    return temp;
};
//
// Created by spp16 on 21.07.2026.
//

#include "LineObject.h"

#include <filesystem>
#include <iostream>
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

    temp.AddMember("Pen", JSONPenRepr(allocator), allocator);

    return temp;
};

shared_ptr<LineObject> LineObject::FromJSON(const rapidjson::Value& json) {
    if (!json.HasMember("Pen")) {
        std::cerr << "Uncorrect .mdrw format" << std::endl;
        return nullptr;
    }
    if (!json["Pen"].HasMember("Width")) {
        std::cerr << "Uncorrect .mdrw format" << std::endl;
        return nullptr;
    }
    if (!json["Pen"].HasMember("Color")) {
        std::cerr << "Uncorrect .mdrw format" << std::endl;
        return nullptr;
    }
    if (!json.HasMember("Points")) {
        std::cerr << "Uncorrect .mdrw format" << std::endl;
        return nullptr;
    }


    const rapidjson::Value& jsonPoints = json["Points"];

    if (jsonPoints.Size() == 0) {
        std::cerr << "Uncorrect .mdrw format" << std::endl;
        return nullptr;
    }

    int min_x = jsonPoints[0][0].GetDouble();
    int min_y = jsonPoints[0][1].GetDouble();

    int max_x = jsonPoints[0][0].GetDouble();
    int max_y = jsonPoints[0][1].GetDouble();

    int pen_width = json["Pen"]["Width"].GetDouble();

    std::vector<QPoint> new_points;

    for (rapidjson::SizeType i = 0; i < jsonPoints.Size(); i++) {
        if (jsonPoints[i].Size() != 2) {
            std::cerr << "Uncorrect .mdrw format" << std::endl;
            return nullptr;
        }

        auto current_x = jsonPoints[i][0].GetDouble();
        auto current_y = jsonPoints[i][1].GetDouble();

        if (current_x - pen_width < min_x) {min_x = current_x - pen_width;}
        if (current_y - pen_width < min_y) {min_y = current_y - pen_width;}
        if (current_x + pen_width > max_x) {max_x = current_x + pen_width;}
        if (current_y + pen_width > max_y) {max_y = current_y + pen_width;}

        new_points.push_back(QPoint(current_x, current_y));
    }

    QPoint topLeft = QPoint(min_x, min_y);
    QPoint bottomRight = QPoint(max_x, max_y);

    QPen pen(json["Pen"]["Color"].GetString());
    pen.setWidth(pen_width);
    pen.setCapStyle(Qt::RoundCap);

    return make_shared<LineObject>(new_points, pen, topLeft, bottomRight);
}
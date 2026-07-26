//
// Created by spp16 on 21.07.2026.
//

#include "RectObject.h"

#include <QPainter>
#include <qpen.h>

#include "../../Gizmos/DotGizmo.h"
#include "../../Gizmos/RectGizmo.h"


RectObject::RectObject() : BaseDraw("Rect object") {
    type = DrawObjectType::RECT_OBJECT;
};

RectObject::RectObject(QPen _pen, QPoint& _atopLeft, QPoint& _bottomRight) : BaseDraw("Rect object") {
    type = DrawObjectType::RECT_OBJECT;

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

    gizmos.push_back(make_shared<DotGizmo>(boundingRect.topLeft()));
    gizmos.push_back(make_shared<DotGizmo>(boundingRect.topRight()));
    gizmos.push_back(make_shared<DotGizmo>(boundingRect.bottomLeft()));
    gizmos.push_back(make_shared<DotGizmo>(boundingRect.bottomRight()));
}

void RectObject::Draw(QPainter& painter) const {
    painter.drawImage(boundingRect.x(), boundingRect.y(), surface);
}

#include <iostream>

rapidjson::Value RectObject::JSONRepr(rapidjson::MemoryPoolAllocator<> allocator) const {
    rapidjson::Value temp(rapidjson::kObjectType);
    temp.AddMember("Type", "RectObject", allocator);


    rapidjson::Value topLeftNode(rapidjson::kArrayType);
    topLeftNode.PushBack(atopLeft.x(), allocator);
    topLeftNode.PushBack(atopLeft.y(), allocator);
    temp.AddMember("TopLeft", topLeftNode, allocator);

    rapidjson::Value bottomRightNode(rapidjson::kArrayType);
    bottomRightNode.PushBack(abottomRight.x(), allocator);
    bottomRightNode.PushBack(abottomRight.y(), allocator);
    temp.AddMember("BottomRight", bottomRightNode, allocator);

    temp.AddMember("Pen", JSONPenRepr(allocator), allocator);

    auto bounds = JSONBoundingRepr(allocator);
    auto position = get<0>(bounds);
    auto size = get<1>(bounds);

    temp.AddMember("Position", *position, allocator);
    temp.AddMember("Size", *size, allocator);

    return temp;
};

shared_ptr<RectObject> RectObject::FromJSON(const rapidjson::Value& json) {
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

    if (!json.HasMember("TopLeft") || json["TopLeft"].Size() != 2) {
        std::cerr << "Uncorrect .mdrw format" << std::endl;
        return nullptr;
    }
    if (!json.HasMember("BottomRight") || json["BottomRight"].Size() != 2) {
        std::cerr << "Uncorrect .mdrw format" << std::endl;
        return nullptr;
    }
    if (!json.HasMember("Position") || json["Position"].Size() != 2) {
        std::cerr << "Uncorrect .mdrw format" << std::endl;
        return nullptr;
    }
    if (!json.HasMember("Size") || json["Size"].Size() != 2) {
        std::cerr << "Uncorrect .mdrw format" << std::endl;
        return nullptr;
    }


    int pen_width = json["Pen"]["Width"].GetDouble();

    QPoint topLeft = QPoint(json["TopLeft"][0].GetDouble(), json["TopLeft"][1].GetDouble());
    QPoint bottomRight = QPoint(json["BottomRight"][0].GetDouble(), json["BottomRight"][1].GetDouble());

    QPen pen(json["Pen"]["Color"].GetString());
    pen.setWidth(pen_width);
    pen.setCapStyle(Qt::RoundCap);

    return make_shared<RectObject>(pen, topLeft, bottomRight);
}
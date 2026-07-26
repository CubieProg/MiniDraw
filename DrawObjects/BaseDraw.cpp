//
// Created by spp16 on 21.07.2026.
//

#include <iostream>
#include "BaseDraw.h"
#include <rapidjson/stringbuffer.h>
#include <rapidjson/prettywriter.h>

#include "../QtUtils/QtUtils.h"

BaseDraw::BaseDraw() {

}

BaseDraw::BaseDraw(const std::string& name) : name(name) {

}

void BaseDraw::DrawGizmos(QPainter& painter) const {
    for (const auto gizmo : gizmos) {
        gizmo->Draw(painter);
    }
}


QPoint BaseDraw::GetPosition() const {
    return QPoint(
        boundingRect.x(),
        boundingRect.y()
    );
}

void BaseDraw::SetPos(const QPoint& pos) {
    QPoint delta = pos - GetPosition();
    utils::UpdateRect(boundingRect, pos);

    std::for_each(gizmos.begin(), gizmos.end(), [delta](auto gizmo) { gizmo->MovePosition(delta); });
}

rapidjson::Value BaseDraw::JSONPenRepr(rapidjson::MemoryPoolAllocator<> allocator) const {
    auto a = pen.color().name();

    auto color_text = pen.color().name().toStdString();  // color.name(QColor::HexArgb);
    auto color_text_value = rapidjson::Value(color_text.c_str(), color_text.size(), allocator);

    rapidjson::Value temp(rapidjson::kObjectType);
    temp.AddMember("Width", pen.width(), allocator);
    temp.AddMember("Color", color_text_value, allocator);

    return temp;
};


std::tuple<rapidjson::Value*, rapidjson::Value*> BaseDraw::JSONBoundingRepr(rapidjson::MemoryPoolAllocator<> allocator) const {
    rapidjson::Value posArray(rapidjson::kArrayType);
    posArray.PushBack(boundingRect.x(), allocator);
    posArray.PushBack(boundingRect.y(), allocator);

    rapidjson::Value sizeArray(rapidjson::kArrayType);
    sizeArray.PushBack(boundingRect.width(), allocator);
    sizeArray.PushBack(boundingRect.height(), allocator);

    return std::make_tuple(&posArray, &sizeArray);
};
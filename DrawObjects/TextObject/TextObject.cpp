//
// Created by spp16 on 21.07.2026.
//

#include "TextObject.h"

#include <iostream>
#include <ostream>
#include <qpainter.h>
#include <qpen.h>
#include <qstring.h>

#include "../../Gizmos/LineGizmo.h"
#include "../../Gizmos/RectGizmo.h"


TextObject::TextObject() : BaseDraw("Text object") {
    type = DrawObjectType::TEXT_OBJECT;

};

TextObject::TextObject(QPen _pen, std::string _text, QPoint _pos) : BaseDraw("Text object") {
    type = DrawObjectType::TEXT_OBJECT;

    text = _text;
    pen = _pen;
    pos = _pos;

    auto font_name = "Arial";

    QFont font(font_name, pen.width());
    QFontMetrics fm(font);

    int width = fm.boundingRect(QString::fromStdString(text)).width();
    int height = fm.boundingRect(QString::fromStdString(text)).height();
    int ascent = fm.ascent();
    int descent = fm.descent();


    boundingRect = QRect(pos.x(), pos.y(), width + pos.x()+6, height + pos.y()+1);
    boundingRect.setWidth(width + 6); // Хз почему, но иначе width и height прямоугольника некорректные...
    boundingRect.setHeight(height + 1);

    surface = QImage(this->boundingRect.size(), QImage::Format_ARGB32_Premultiplied);
    surface.fill(Qt::transparent);

    QPainter painter(&surface);

    painter.setFont(QFont(font_name, pen.width()));
    painter.setPen(pen);

    painter.drawText(QPoint(1, ascent), QString::fromStdString(text));


    gizmos.push_back(make_shared<LineGizmo>(boundingRect.bottomLeft(), boundingRect.bottomRight()));
}

void TextObject::Draw(QPainter& painter) const {
    painter.drawImage(boundingRect.x(), boundingRect.y(), surface);
}

rapidjson::Value TextObject::JSONRepr(rapidjson::MemoryPoolAllocator<> allocator) const {
    rapidjson::Value temp(rapidjson::kObjectType);

    auto json_text_value = rapidjson::Value(text.c_str(), text.size(), allocator);

    temp.AddMember("Type", "TextObject", allocator);
    temp.AddMember("Text", json_text_value, allocator);

    temp.AddMember("Pen", JSONPenRepr(allocator), allocator);

    auto bounds = JSONBoundingRepr(allocator);
    auto position = get<0>(bounds);

    temp.AddMember("Position", *position, allocator);

    return temp;
};



shared_ptr<TextObject> TextObject::FromJSON(const rapidjson::Value& json) {
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

    if (!json.HasMember("Position") || json["Position"].Size() != 2) {
        std::cerr << "Uncorrect .mdrw format" << std::endl;
        return nullptr;
    }
    if (!json.HasMember("Text")) {
        std::cerr << "Uncorrect .mdrw format" << std::endl;
        return nullptr;
    }

    int pen_width = json["Pen"]["Width"].GetDouble();

    std::string text = json["Text"].GetString();

    QPoint pos = QPoint(json["Position"][0].GetDouble(), json["Position"][1].GetDouble());

    QPen pen(json["Pen"]["Color"].GetString());
    pen.setWidth(pen_width);
    pen.setCapStyle(Qt::RoundCap);

    return make_shared<TextObject>(pen, text, pos);
}
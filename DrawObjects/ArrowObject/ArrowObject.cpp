#include "ArrowObject.h"
#include <QPainter>
#include "../../Gizmos/DotGizmo.h"
#include "../../Gizmos/LineGizmo.h"

ArrowObject::ArrowObject() : BaseDraw("Circle object") {
    type = DrawObjectType::ARROW_OBJECT;

};

ArrowObject::ArrowObject(QPen _pen, QPoint& _startPoint, QPoint& _endPoint) : BaseDraw("Arrow object") {
    type = DrawObjectType::ARROW_OBJECT;

    startPoint = _startPoint;
    endPoint = _endPoint;

    auto atopLeft = QPoint(
        std::min(startPoint.x(), endPoint.x()),
        std::min(startPoint.y(), endPoint.y())
    );
    auto abottomRight = QPoint(
        std::max(startPoint.x(), endPoint.x()),
        std::max(startPoint.y(), endPoint.y())
    );

    this->pen = _pen;
    auto penSize = QPoint(pen.width() / 2, pen.width() / 2)*3;

    qreal arrowSize = pen.width()*2;
    this->boundingRect = QRect(atopLeft - penSize, abottomRight + penSize);


    surface = QImage(this->boundingRect.size(), QImage::Format_ARGB32_Premultiplied);
    surface.fill(Qt::transparent);

    QPainter painter(&surface);

    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(pen);
    painter.setBrush(QBrush(pen.color()));

    QLineF line(startPoint - atopLeft + penSize, endPoint - atopLeft + penSize);

    double angle = std::atan2(-line.dy(), line.dx());
    auto add_angle = M_PI / 3;

    QPointF arrowP1 = line.p2() - QPointF(
        sin(angle + add_angle),
        cos(angle + add_angle)
        ) * arrowSize;

    QPointF arrowP2 = line.p2() - QPointF(
        sin(angle + M_PI - add_angle),
        cos(angle + M_PI - add_angle)
        ) * arrowSize;

    QPolygonF arrowHead;
    arrowHead << line.p2() << arrowP1 << arrowP2;

    painter.drawLine(line);
    painter.drawPolygon(arrowHead);


    gizmos.push_back(make_shared<DotGizmo>(_startPoint));
    gizmos.push_back(make_shared<DotGizmo>(_endPoint));
    gizmos.push_back(make_shared<LineGizmo>(_startPoint, _endPoint));
}

void ArrowObject::Draw(QPainter& painter) const {
    painter.drawImage(boundingRect.x(), boundingRect.y(), surface);
}

rapidjson::Value ArrowObject::JSONRepr(rapidjson::MemoryPoolAllocator<> allocator) const {
    rapidjson::Value temp(rapidjson::kObjectType);
    temp.AddMember("Type", "ArrowObject", allocator);

    rapidjson::Value startPointNode(rapidjson::kArrayType);
    startPointNode.PushBack(startPoint.x(), allocator);
    startPointNode.PushBack(startPoint.y(), allocator);
    temp.AddMember("StartPoint", startPointNode, allocator);

    rapidjson::Value bottomRightNode(rapidjson::kArrayType);
    bottomRightNode.PushBack(endPoint.x(), allocator);
    bottomRightNode.PushBack(endPoint.y(), allocator);
    temp.AddMember("EndPoint", bottomRightNode, allocator);

    return temp;
};
#include "Liner.h"

#include <iostream>
#include <QPainter>

Liner::Liner() : BaseTool(), points() {
    toolType = ToolType::Liner;
    toolName = "Liner";
}

ToolMessage Liner::OnPress(const QMouseEvent* event) {
    if (event->button() == Qt::LeftButton){

        if (state == ToolState::DISABLED) points.clear();
        ToolMessage returnResult = (state == ToolState::ACTIVE)     ?
                                            ToolMessage::CONTINUE   :
                                            ToolMessage::ENTER;

        points.push_back(event->pos());


        QPainter painter(paintSurface);
        painter.setRenderHint(QPainter::Antialiasing);
        painter.setPen(pen);

        if (points.size() == 1) {
            QBrush  circlePen(pen.color());
            painter.setBrush(circlePen);
            painter.setPen(QPen(Qt::transparent));

            auto point = points[0];
            painter.drawLine(point, point);
            painter.drawEllipse(point, width/2, width/2);

            painter.setBrush(QBrush());
            painter.setPen(pen);
        }

        if (points.size() >= 2) {
            for (
                auto left = points.begin(), right = left+1;
                right != points.end();
                ++left, ++right
            ) painter.drawLine(*left, *right);
        }

        state = ToolState::ACTIVE;

        return returnResult;
    }

    if (event->button() == Qt::RightButton) {
        state = ToolState::DISABLED;
        return ToolMessage::QUIT;
    }
}


ToolMessage Liner::OnRelease(const QMouseEvent* event) {
    return ToolMessage::NOTHING;
};

ToolMessage Liner::OnMove(const QMouseEvent* event) {
    // if (state == ToolState::DISABLED) return ToolMessage::NOTHING;
    //
    // position = event->pos();
    //
    // QPen pen(currentColor, paintWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    // painter.setPen(pen);
    // painter.drawLine(lastPosition, position);
    // lastPosition = event->pos();
    //
    // return ToolMessage::CONTINUE;

    return ToolMessage::NOTHING;
};


shared_ptr<BaseDraw> Liner::ProduceDrawObject(QImage& image, QPoint atopLeft, QPoint abottomRight) {

    auto new_object = std::make_shared<LineObject>(this->points, this->pen, atopLeft, abottomRight);
    return new_object;
}
//
// Created by spp16 on 21.07.2026.
//

#include "SelectTool.h"

SelectTool::SelectTool() : BaseTool() {
    toolType = ToolType::SelectTool;
    toolName = "SelectTool";
}


ToolMessage SelectTool::OnPress(const QMouseEvent* event) {
    if (event->button() == Qt::LeftButton) {
        enterPoint = event->pos();

        state = ToolState::ACTIVE;
        return ToolMessage::ENTER;
    }

    return ToolMessage::NOTHING;
}


ToolMessage SelectTool::OnRelease(const QMouseEvent* event) {
    if (event->button() == Qt::LeftButton) {
        state = ToolState::DISABLED;
        return ToolMessage::QUIT;
    }

    return ToolMessage::NOTHING;
};

ToolMessage SelectTool::OnMove(const QMouseEvent* event) {
    if (state == ToolState::ACTIVE) {
        return ToolMessage::CONTINUE;
    }

    return ToolMessage::NOTHING;
};


shared_ptr<BaseDraw> SelectTool::ProduceDrawObject(QImage& image, QPoint atopLeft, QPoint abottomRight) {
    return nullptr;
}

void SelectTool::SetCatchDelta(const QPoint& objectPosition) {
    catchDelta = enterPoint - objectPosition;
}
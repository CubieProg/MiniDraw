//
// Created by spp16 on 21.07.2026.
//

#include <qlineedit.h>
#include <QInputDialog.h>
#include "TextTool.h"

#include "../../DrawObjects/TextObject/TextObject.h"

TextTool::TextTool() : BaseTool() {
    toolType = ToolType::TextTool;
    toolName = "TextTool";
}


ToolMessage TextTool::ProcessModalResponse(bool& ok, QString response) {

    if (ok && !response.isEmpty()) {
        text = response.toStdString();
        return ToolMessage::QUIT;
    } else {
        return ToolMessage::NOTHING;
    }
};


ToolMessage TextTool::OnPress(const QMouseEvent* event) {
    if (event->button() != Qt::LeftButton) return ToolMessage::NOTHING;

    pos = event->pos();


    return ToolMessage::ENTER;
};



ToolMessage TextTool::OnRelease(const QMouseEvent* event) {
    return ToolMessage::NOTHING;
};

ToolMessage TextTool::OnMove(const QMouseEvent* event) {
    return ToolMessage::NOTHING;
};


shared_ptr<BaseDraw> TextTool::ProduceDrawObject(QImage& image, QPoint atopLeft, QPoint abottomRight) {
    auto new_object = std::make_shared<TextObject>(pen, text, pos);
    return new_object;
}
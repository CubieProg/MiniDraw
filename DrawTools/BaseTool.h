//
// Created by spp16 on 21.07.2026.
//

#ifndef MINIDRAW_BASETOOL_H
#define MINIDRAW_BASETOOL_H

#include <QMouseEvent>
#include <qpen.h>
#include <string>

#include "../DrawObjects/BaseDraw.h"

using namespace std;

enum class ToolType {
    SelectTool,
    Pencil,
    Liner,
    CircleTool,
    RectTool,
    ArrowTool,
    TextTool
};

enum class ToolMessage {
    ENTER,
    CONTINUE,
    QUIT,

    NOTHING
};

enum class ToolState {
    ACTIVE,
    DISABLED
};

class BaseTool {
public:
    BaseTool();
    virtual ~BaseTool();

    ToolType GetToolType() {return toolType;};
    string GetToolName() {return toolName;};

    virtual ToolMessage OnPress(const QMouseEvent* event) = 0;
    virtual ToolMessage OnRelease(const QMouseEvent* event) = 0;
    virtual ToolMessage OnMove(const QMouseEvent* event/*, QPainter& painter*/) = 0;

    virtual shared_ptr<BaseDraw> ProduceDrawObject(QImage& image, QPoint atopLeft, QPoint abottomRight) = 0;


    ToolState GetState() {return state;};

    void SetWidth(int _width) {
        width = _width;
        pen.setWidth(width);
    }
    void SetColor(QColor _color) {
        color = _color;
        pen.setColor(color);
    }

    void SetPaintSurface(QImage* image){if (paintSurface == nullptr) paintSurface = image;}


protected:
    QPen pen;

    QImage* paintSurface = nullptr;

    ToolType toolType;
    string toolName;

    ToolState state;

    int width;
    QColor color;
};


#endif //MINIDRAW_BASETOOL_H

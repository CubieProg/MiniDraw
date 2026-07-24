//
// Created by spp16 on 21.07.2026.
//

#ifndef SIMPLE_WINDOW_BASETOOL_H
#define SIMPLE_WINDOW_BASETOOL_H

#include <QColor>
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

    // QPen pen(color, width, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);

    void SetPaintSurface(QImage* image){if (paintSurface == nullptr) paintSurface = image;}


protected:
    // void UpdatePen();

    QPen pen;

    QImage* paintSurface = nullptr;

    ToolType toolType;
    string toolName;

    ToolState state;

    int width;
    QColor color;
};


#endif //SIMPLE_WINDOW_BASETOOL_H

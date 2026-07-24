//
// Created by spp16 on 21.07.2026.
//

#ifndef SIMPLE_WINDOW_TOOLSCONTAINER_H
#define SIMPLE_WINDOW_TOOLSCONTAINER_H

#include <memory>
#include <qimage.h>
#include <unordered_map>
#include <string>

#include "BaseTool.h"

using namespace std;

class ToolsContainer {
public:
    ToolsContainer();
    shared_ptr<BaseTool> GetActiveTool();

    void SetActiveTool(ToolType toolType);
    void SetActiveTool(string toolName);

    void SetPaintWidth(int width) {GetActiveTool()->SetWidth(width);}
    void SetPaintColor(const QColor& color) {GetActiveTool()->SetColor(color);}

    void init(int width, const QColor& color, QImage* image);

private:
    // void SetPaintSurface(QImage* image);

    QImage* paintSurface = nullptr;
    shared_ptr<BaseTool> activeTool;
    unordered_map<ToolType, shared_ptr<BaseTool>> tools;
};


#endif //SIMPLE_WINDOW_TOOLSCONTAINER_H

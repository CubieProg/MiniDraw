//
// Created by spp16 on 21.07.2026.
//

#include <memory>
#include "ToolsContainer.h"

#include <iostream>
#include <map>
#include <ostream>

#include "BaseTool.h"

#include "SelectTool/SelectTool.h"
#include "Pencil/Pencil.h"
#include "Liner/Liner.h"
#include "CircleTool/CircleTool.h"
#include "RectTool/RectTool.h"
#include "ArrowTool/ArrowTool.h"
#include "TextTool/TextTool.h"


using namespace std;

ToolsContainer::ToolsContainer() {

    tools.insert({
        {ToolType::SelectTool, make_shared<SelectTool>()},
        {ToolType::Pencil, make_shared<Pencil>()},
        {ToolType::Liner, make_shared<Liner>()},
        {ToolType::CircleTool, make_shared<CircleTool>()},
        {ToolType::RectTool, make_shared<RectTool>()},
        {ToolType::ArrowTool, make_shared<ArrowTool>()},
        {ToolType::TextTool, make_shared<TextTool>()}
    });
}

shared_ptr<BaseTool> ToolsContainer::GetActiveTool() {
    return activeTool;
}


void ToolsContainer::SetActiveTool(ToolType toolType) {
    activeTool = tools.at(toolType);
    std::cout << activeTool->GetToolName() << std::endl;
};

void ToolsContainer::SetActiveTool(string toolName) {
    auto iterator = std::find_if(
        tools.begin(),
        tools.end(),
        [toolName](const auto& pair) { return pair.second->GetToolName() == toolName; }
    );

    if (iterator != tools.end()) { activeTool = iterator->second; }
};

void ToolsContainer::SetPaintWidth(int width) {
    for (const auto & [ key, value ] : tools) {
        value->SetWidth(width);
    }
}

void ToolsContainer::SetPaintColor(const QColor& color){
    for (const auto & [ key, value ] : tools) {
        value->SetColor(color);
    }
}

void ToolsContainer::init(int width, const QColor& color, QImage* image) {
    if (paintSurface != nullptr) return;

    paintSurface = image;

    for (const auto & [ key, value ] : tools) {
        value->SetWidth(width);
        value->SetColor(color);
        value->SetPaintSurface(paintSurface);
    }
}
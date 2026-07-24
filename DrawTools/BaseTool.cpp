//
// Created by spp16 on 21.07.2026.
//

#include "BaseTool.h"

BaseTool::BaseTool() : pen(Qt::black, 0, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin) {
    state = ToolState::DISABLED;

}

BaseTool::~BaseTool() = default;


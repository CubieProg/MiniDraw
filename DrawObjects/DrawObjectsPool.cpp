//
// Created by spp16 on 21.07.2026.
//
//
#include "DrawObjectsPool.h"

#include <iostream>

#include "BaseDraw.h"
#include "PixelObject/PixelObject.h"
#include <vector>
#include <memory>

#include <algorithm>

using namespace std;

DrawObjectsPool::DrawObjectsPool() : items() {
    items.push_back(std::make_shared<PixelObject>());
}

void DrawObjectsPool::AddItem(std::shared_ptr<BaseDraw> item) {
    items.push_back(item);
}



shared_ptr<BaseDraw> DrawObjectsPool::Select(QPoint pos) {

    auto it = std::find_if(
        items.begin(),
        items.end(),
        [pos](const auto& item) {
            return item->GetBoundingRect().contains(pos);
        });


    if (it != items.end()) {
        selectedObject = *it;
        return *it;
    } else {
        selectedObject = nullptr;
    }

    return nullptr;

    // vector<shared_ptr<BaseDraw>> layeredQueue;
    // ranges::copy_if(
    //     items,
    //     back_inserter(layeredQueue),
    //     [pos](shared_ptr<BaseDraw> item) {
    //         return  item->GetBoundingRect().contains(pos);
    //     }
    // );
    //
    // return layeredQueue.front();
};

void DrawObjectsPool::Deselect() {

};



void DrawObjectsPool::Draw(QPainter& painter) {
    for (auto item : items) {
        item->Draw(painter);
    }

    if (selectedObject != nullptr) {
        std::cout << "Draw Gizmos" << std::endl;
        selectedObject->DrawGizmos(painter);
    }
}
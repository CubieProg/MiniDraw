//
// Created by spp16 on 21.07.2026.
//
//
#include "DrawObjectsPool.h"
#include "BaseDraw.h"
#include "PixelObject/PixelObject.h"
#include <vector>
#include <memory>


using namespace std;

DrawObjectsPool::DrawObjectsPool() : items() {
    items.push_back(std::make_shared<PixelObject>());
}

void DrawObjectsPool::AddItem(std::shared_ptr<BaseDraw> item) {
    items.push_back(item);
}



shared_ptr<BaseDraw> DrawObjectsPool::Select(QPoint pos) {
    vector<int> foo = {25,15,5,-5,-15};
    vector<int> bar;

    ranges::copy_if (foo, std::back_inserter(bar), [](int i){return i>=0;} );

    vector<shared_ptr<BaseDraw>> layeredQueue;
    ranges::copy_if(
        items,
        back_inserter(layeredQueue),
        [pos](shared_ptr<BaseDraw> item) {
            return  item->GetBoundingRect().contains(pos);
        }
    );

    return layeredQueue.front();
};

void DrawObjectsPool::Deselect() {

};



void DrawObjectsPool::Draw(QPainter& painter) {
    for (auto item : items) {
        item->Draw(painter);
    }
}
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

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"


using namespace std;

DrawObjectsPool::DrawObjectsPool() : items() {

}

void DrawObjectsPool::AddItem(std::shared_ptr<BaseDraw> item) {
    if (item == nullptr) {return;}
    items.push_back(item);
}



shared_ptr<BaseDraw> DrawObjectsPool::Select(QPoint pos) {
    vector<shared_ptr<BaseDraw>> layeredQueue;
    ranges::copy_if(
        items,
        back_inserter(layeredQueue),
        [pos](shared_ptr<BaseDraw> item) {
            return item->GetBoundingRect().contains(pos);
        }
    );

    if (layeredQueue.size() == 0) {
        selectedObject = nullptr;
    } else {
        auto it = std::find(layeredQueue.begin(), layeredQueue.end(), selectedObject);

        if (it != layeredQueue.end()) {
            if (it == layeredQueue.begin()) {
                selectedObject = layeredQueue.back();
            } else {
                it--;
                selectedObject = *it;
            }
        } else {
            selectedObject = layeredQueue.back();
        }
    }

    return selectedObject;
};

void DrawObjectsPool::Deselect() {
    selectedObject = nullptr;
};

void DrawObjectsPool::UpdateSelectedObject(QPoint pos) {
    if (selectedObject == nullptr) {return;}
    selectedObject->SetPos(pos);
}


void DrawObjectsPool::TrySelectObject(std::shared_ptr<BaseDraw> obj) {
    auto iterator = std::find_if(
        items.begin(),
        items.end(),
        [obj](const auto& item) { return item == obj; }
    );

    if (iterator != items.end()) { selectedObject = *iterator; }
};


void DrawObjectsPool::Draw(QPainter& painter) {
    for (auto item : items) {
        item->Draw(painter);
    }

    if (selectedObject != nullptr) {
        selectedObject->DrawGizmos(painter);
    }
}


rapidjson::Document DrawObjectsPool::GenerateJSON() const {
    rapidjson::Document doc;
    doc.SetObject();

    rapidjson::Value objectsArray(rapidjson::kArrayType);

    std::cout << "Objects at all: " << items.size() << std::endl;
    for (auto item : items) {
        std::cout << item->GetName() << std::endl;
        objectsArray.PushBack(item->JSONRepr(doc.GetAllocator()), doc.GetAllocator());

    }

    doc.AddMember("DrawObjects", objectsArray, doc.GetAllocator());

    return doc;
};

void DrawObjectsPool::Clear() {
    selectedObject = nullptr;
    items.clear();
}
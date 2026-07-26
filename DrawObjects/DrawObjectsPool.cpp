//
// Created by spp16 on 21.07.2026.
//
//
#include "DrawObjectsPool.h"

#include <iostream>

#include "BaseDraw.h"
#include <vector>
#include <memory>
#include <algorithm>

#include "rapidjson/document.h"
#include "rapidjson/writer.h"

#include "rapidjson/istreamwrapper.h"
#include <fstream>

#include "ArrowObject/ArrowObject.h"
#include "CircleObject/CircleObject.h"
#include "LineObject/LineObject.h"
#include "PixelObject/PixelObject.h"
#include "RectObject/RectObject.h"
#include "TextObject/TextObject.h"


using namespace std;

DrawObjectsPool::DrawObjectsPool() : items() {

    typeAlias.insert({
        {"PixelObject", DrawObjectType::PIXEL_OBJECT},
        {"LineObject", DrawObjectType::LINE_OBJECT},
        {"CircleObject", DrawObjectType::CIRCLE_OBJECT},
        {"RectObject", DrawObjectType::RECT_OBJECT},
        {"ArrowObject", DrawObjectType::ARROW_OBJECT},
        {"TextObject", DrawObjectType::TEXT_OBJECT},
    });
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

    for (auto item : items) {
        objectsArray.PushBack(item->JSONRepr(doc.GetAllocator()), doc.GetAllocator());

    }

    doc.AddMember("DrawObjects", objectsArray, doc.GetAllocator());

    return doc;
};

void DrawObjectsPool::Clear() {
    selectedObject = nullptr;
    items.clear();
}

void DrawObjectsPool::LoadMDRW(const rapidjson::Document& doc) {

    // Key check example
    // document["Person"][0].HasMember("name")
    // -----------------------------------------------------------------

    if (!doc.HasMember("DrawObjects")) {
        std::cerr << "Uncorrect .mdrw format" << std::endl;
        return;
    }

    const rapidjson::Value& drawObjects = doc["DrawObjects"];
    for (rapidjson::SizeType i = 0; i < drawObjects.Size(); i++) {
        // auto item = drawObjects[i];

        if (!drawObjects[i].HasMember("Type")) {
            std::cerr << "Uncorrect .mdrw format" << std::endl;
            return;
        }

        std::string type_as_str = drawObjects[i]["Type"].GetString();

        if (typeAlias.find(type_as_str) == typeAlias.end()){
            std::cerr << "Uncorrect .mdrw format" << std::endl;
            return;
        }

        DrawObjectType type = typeAlias[type_as_str];

        switch (type) {
            case DrawObjectType::PIXEL_OBJECT:
                AddItem(PixelObject::FromJSON(drawObjects[i]));
                break;
            case DrawObjectType::LINE_OBJECT:
                AddItem(LineObject::FromJSON(drawObjects[i]));
                break;
            case DrawObjectType::CIRCLE_OBJECT:
                AddItem(CircleObject::FromJSON(drawObjects[i]));
                break;
            case DrawObjectType::RECT_OBJECT:
                AddItem(RectObject::FromJSON(drawObjects[i]));
                break;
            case DrawObjectType::ARROW_OBJECT:
                AddItem(ArrowObject::FromJSON(drawObjects[i]));
                break;
            case DrawObjectType::TEXT_OBJECT:
                AddItem(TextObject::FromJSON(drawObjects[i]));
                break;
        }

    }

};
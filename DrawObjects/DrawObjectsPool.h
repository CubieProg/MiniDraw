//
// Created by spp16 on 21.07.2026.
//

#ifndef MINIDRAW_DRAWOBJECTSPOOL_H
#define MINIDRAW_DRAWOBJECTSPOOL_H


#include <vector>

#include "BaseDraw.h"
#include "rapidjson/document.h"


class DrawObjectsPool {
public:
    DrawObjectsPool();

    void Draw(QPainter& painter);
    void AddItem(std::shared_ptr<BaseDraw>);


    std::shared_ptr<BaseDraw> Select(QPoint pos);
    void Deselect();

    void UpdateSelectedObject(QPoint pos);

    void TrySelectObject(std::shared_ptr<BaseDraw> obj);
    std::shared_ptr<BaseDraw> GetSelectedObject(){return selectedObject;}

    void Clear();

    rapidjson::Document GenerateJSON() const;

private:
    std::shared_ptr<BaseDraw> selectedObject = nullptr;
    std::vector<std::shared_ptr<BaseDraw>> items;
};


#endif //MINIDRAW_DRAWOBJECTSPOOL_H

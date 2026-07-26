//
// Created by spp16 on 21.07.2026.
//

#ifndef MINIDRAW_TEXTOBJECT_H
#define MINIDRAW_TEXTOBJECT_H
#include <qpen.h>

#include "../BaseDraw.h"


class TextObject : public BaseDraw {
public:
    TextObject();
    TextObject(QPen _pen, std::string _text, QPoint _pos);
    void Draw(QPainter& painter) const override;
    rapidjson::Value JSONRepr(rapidjson::MemoryPoolAllocator<> allocator) const override;

    static shared_ptr<TextObject> FromJSON(const rapidjson::Value& json);
private:
    std::string text;
    QPoint pos;
    // QPen pen;

};


#endif //MINIDRAW_TEXTOBJECT_H

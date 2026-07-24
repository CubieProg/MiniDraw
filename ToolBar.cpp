#include "toolbar.h"
#include <QVBoxLayout>
#include <QIcon>

#include "ui_toolbar.h"

ToolBar::ToolBar(QWidget *parent) : QToolBar(parent)
{
    // Создаем вертикальный лейаут для тулбара
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(2, 2, 2, 2); // Небольшие отступы
    layout->setSpacing(4); // Расстояние между кнопками

    // Генерируем 3 кнопки циклом
    for (int i = 0; i < 3; ++i) {
        createButton(i);
    }
}

void ToolBar::createButton(int index)
{
    QPushButton *btn = new QPushButton(this);
    
    // Устанавливаем размер 16x16
    btn->setFixedSize(16, 16);
    btn->setIconSize(QSize(16, 16));
    btn->setText(""); // Без текста
    
    // (Опционально) Добавляем иконку, если нужно
    // btn->setIcon(QIcon(":/icons/icon" + QString::number(index+1) + ".png"));

    // Подключаем сигнал
    connect(btn, &QPushButton::clicked, this, &ToolBar::onBtnClicked);
    
    // Сохраняем указатель, чтобы знать, какая кнопка нажата (через sender())
    buttons[index] = btn;
    
    // Добавляем в лейаут
    layout()->addWidget(btn);
}

void ToolBar::onBtnClicked()
{
    QPushButton *btn = qobject_cast<QPushButton*>(sender());
    if (!btn) return;

    // Определяем индекс кнопки
    int index = -1;
    for(int i=0; i<3; ++i) {
        if(buttons[i] == btn) {
            index = i;
            break;
        }
    }

    // Эмитим соответствующий сигнал
    if (index == 0) emit action1Triggered();
    else if (index == 1) emit action2Triggered();
    else if (index == 2) emit action3Triggered();
}

ToolBar::~ToolBar()
{
    // QToolBar сам удалит дочерние виджеты, но если есть ресурсы — удали их здесь
}
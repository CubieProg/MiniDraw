#ifndef TOOLBAR_H
#define TOOLBAR_H
#include <QToolBar>
#include <QPushButton>

class ToolBar : public QToolBar
{
    Q_OBJECT

public:
    explicit ToolBar(QWidget *parent = nullptr);
    ~ToolBar();

signals:
    void action1Triggered();
    void action2Triggered();
    void action3Triggered();

private slots:
    void onBtnClicked();

private:
    // Массив кнопок, чтобы не хранить 3 отдельные переменные
    QPushButton* buttons[3];
    void createButton(int index);
};
#endif
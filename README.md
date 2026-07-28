# MiniDraw

Оконное приложение для рисования графических примитивов.

## Установка

1. Открыть последний релиз https://github.com/CubieProg/MiniDraw/releases
2. Скачать архив _Dist.rar_.
3. Распаковать архив, запустить _MiniDraw.exe_.

## Общий обзор

Всё приложение разделено на 
1. Панель инструментов (слева);
2. Дерево объектов (справа);
3. Вспомогательная панель (сверху);
4. Рабочая область (по центру).
<img width="1910" height="993" alt="image" src="https://github.com/user-attachments/assets/a091b6c0-d607-4d14-bc1c-1ab908e1f616" />

## Панель инструментов
В панели инструментов можно выбрать следующие инструменты:

1. Инструмент выделения (инструмент по умолчанию);
2. Карандаш;
3. Инструмент ломаной линии;
4. Инструмент окружности;
5. Инструмент прямоугольника;
6. Инструмент стрелки;
7. Инструмент текста.

<img width="63" height="524" alt="image" src="https://github.com/user-attachments/assets/cfa53d0a-17a8-45bc-8aa6-c70be9cd0545" />

При запуске программы, по умолчанию выбран **инструмент выделения**.

### Инструмент выделения

<img width="64" height="67" alt="image" src="https://github.com/user-attachments/assets/4d7e80a0-ded6-42e6-a93f-c2e18a5fa7f3" />

Выделяет объекты в рабочей области. Для этого нужно нажать **ЛКМ** над объектом. Что бы выделить объект "под" другим объектом, нужно прокликать несколько раз. Что бы снять выделение, нужно нажать **ПКМ**.

<img width="880" height="590" alt="select-tool-select" src="https://github.com/user-attachments/assets/258f2471-a8ff-4816-931a-b6be062c2471" />

Может перемещать выделенные объекты. 

<img width="874" height="638" alt="select tool" src="https://github.com/user-attachments/assets/53c3d2e0-9c46-4af9-9e43-fa117138bf61" />

### Карандаш

<img width="65" height="65" alt="image" src="https://github.com/user-attachments/assets/f33a183b-47fd-4718-bdd9-baf247def863" />

Создаёт объект типа "растровое изображение". Можно нарисовать произвольную форму.

<img width="400" height="392" alt="pencil tool" src="https://github.com/user-attachments/assets/db20a440-5284-4a6d-9d93-7268cb4e3cd2" />

### Инструмент ломаной линии

<img width="65" height="69" alt="image" src="https://github.com/user-attachments/assets/4775577b-c536-4244-b1a3-b32dc42bfb59" />

Создаёт ломаную линию. Вершины ломаной линии устанавливаются последовательно нажатием на **ЛКМ**. Что бы подтвердить создание объекта, нужно нажать **ПКМ**.

<img width="400" height="362" alt="line tool" src="https://github.com/user-attachments/assets/f9e22797-ccfe-44de-b43f-fe5a01c7a840" />

### Инструмент окружности

<img width="65" height="70" alt="image" src="https://github.com/user-attachments/assets/258ef57e-1b5e-4a72-a9c7-2ee1d1faa8d2" />

Создаёт эллипс. Для этого нужно задать ограничивающий прямоугольник.

<img width="400" height="384" alt="circle tool" src="https://github.com/user-attachments/assets/2ed7ffa6-04f6-478a-8110-f3bd1bc508b3" />

### Инструмент прямоугольника

<img width="65" height="62" alt="image" src="https://github.com/user-attachments/assets/94630dbe-d71c-4801-80f1-1581e1ea001c" />

Создаёт прямоугольник. Для этого нужно задать ограничивающий прямоугольник.

<img width="400" height="394" alt="rect tool" src="https://github.com/user-attachments/assets/97edcc79-3ea4-4754-bd75-219c736ab484" />

### Инструмент стрелки

<img width="66" height="69" alt="image" src="https://github.com/user-attachments/assets/c141dca6-bcd8-4299-a706-22e106fc93b3" />

Создаёт указательную стрелку. Для этого нужно задать начальную и конечную точки.

<img width="400" height="382" alt="arrow tool" src="https://github.com/user-attachments/assets/6cb9d328-9ca9-4d7c-a683-61669b8f5811" />

### Инструмент текста

<img width="63" height="62" alt="image" src="https://github.com/user-attachments/assets/d7589c59-4afb-4d48-a0b4-291b26994fb6" />

Создаёт текст. Для этого нужно его ввести во всплывающем окне.

<img width="400" height="208" alt="text tool" src="https://github.com/user-attachments/assets/7412ee25-0c40-4086-9598-03270aadaddc" />

## Дерево объектов

Дерево объектов хранит перечень всех объектов в проекте **mdrw**. 

<img width="293" height="354" alt="image" src="https://github.com/user-attachments/assets/046362f3-389b-4cff-a111-ba2d371115dd" />

По клику на имя объекта, он выделяется

<img width="600" height="304" alt="tree selection" src="https://github.com/user-attachments/assets/730a006a-217a-4df7-85cc-37213b9cef16" />

## Вспомогательная панель

На вспомогательной панели расположены следующие элементы (слева на право):
1. Сохранить;
2. Сохранить как;
3. Открыть;
4. Название проекта;
5. Поле ввода ширины рисования;
6. Квадратик выбора цвета.

<img width="819" height="69" alt="image" src="https://github.com/user-attachments/assets/e1284aba-042d-421c-ad48-e0331e6f97b7" />

### Сохранить

<img width="66" height="65" alt="image" src="https://github.com/user-attachments/assets/744d4785-73d2-45c6-8a2c-75db1ace3c3b" />


Для сохранения доступны два формата:
1. **.png** - стандартный формат растрового изображения;
2. **.mdrw** - собственный формат _MiniDraw_. По сути является **.json**-ом. **.mdrw** - сокращение от _MiniDraw_. 

Если проект был открыт или уже был сохранён в формате **.png** или **.mdrw**, то сохраняет в тот же файл в соответствующем формате.

Иначе, запускает сценарий "сохранить как".

### Сохранить как

<img width="66" height="62" alt="image" src="https://github.com/user-attachments/assets/7de93f8e-35de-4bdd-8d06-ecdd104e946f" />


Сохраняет проект в указанный файл. Для сохранения можно указать формат **.mdrw** или **.png**. По умолчанию выбран формат **.mdrw**.

### Открыть 

<img width="64" height="62" alt="image" src="https://github.com/user-attachments/assets/51ec1457-eb12-461d-aee3-65b9d4aa7b71" />


Открывает файл формата **.png** или **.mdrw**.

### Название проекта

<img width="204" height="61" alt="image" src="https://github.com/user-attachments/assets/5878717b-7058-496a-913a-a7f2b35ea48d" />


Отображает название текущего проекта. Если название не установлено, то по умолчанию отображает "untiteled.mdrw".

### Поле ввода ширины рисования

<img width="261" height="60" alt="image" src="https://github.com/user-attachments/assets/ae63c2cb-3e2b-4f33-a7b1-afc8624654b4" />

Поле ввода текста. **Ввести можно только положительные целые числа** (от 1 до 2.147.483.647). После ввода и нажатия клавиши _Enter_ изменяет ширину рисования всех примитивов и размер шрифта рисуемого текста. При запуске программы по умолчанию установлено число 12.

### Квадратик выбора цвета

<img width="57" height="62" alt="image" src="https://github.com/user-attachments/assets/0194a9c1-3885-40fd-a8c0-62be4acb1d2b" />

При нажатии открывает диалоговое окно выбора цвета. При выборе цвета, устанавливает выбранный цвет для рисования всех примитивов и рисуемого текста. При запуске программы по умолчанию установлен светло серый цвет (rgba = (160, 160, 160)).

## Внутренняя модель

### Объектная модель MiniDraw



В объектной модели _MiniDraw_ есть один базовый графический примитив **BaseDraw**. Его нельзя создать, даже если очень сильно захочется. Остальные примитивы являются наследниками **BaseDraw**.

Существуют следующие типы графических примитивов: 
1. **PixelObject** - содержит растровое изображение. Может содержать любое изображение. Как правило создаётся инструментом "Карандаш";
2. **LineObject** - тип, представляющий ломаную линию. Создаётся инструментом создания ломаной линии;
3. **CircleObject** - тип, представляющий эллипс. Создаётся инструментом создания окружности;
4. **RectObject** - тип, представляющий прямоугольник. Создаётся инструментом создания прямоугольника;
5. **ArrowObject** - тип, представляющий указательную стрелку. Создаётся инструментом создания стрелок;
6. **TextObject** - тип, представляющий текст. Создаётся инструментом создания текста.

### Файл сохранения
**Не рекомендуется использовать информацию в данном пункте!!!**

Файл сохранения содержит следующие поля:
1. `"Version": "x.x.x"` нужно для обратной совместимости;
2. `"DrawObjects": [...]` хранит в себе объекты рисования.

Объекты в файле сохранения содержат поле `"Type": "object_type"`. Все типы объектов в файле сохранения соответствуют типам объектов в модели _MiniDraw_.

1. **PixelObject** - содержит поля `"Position": [x, y]`, `"Size": [w, h]` и `"Data": "..."`. Поле `"Data": "..."` хранит бинарное представление **.png** картинки в кодировке **base64**;
3. **LineObject** - содержит поля `"Points": [[x1, y1], [x2, y2], ...]` и `"Pen": {"Width": width; "Color": color}`. Поле `"Points": [...]` содержит точки по которым рисуется ломаная линия, поле `"Pen": ...` содержит параметры карандаша которым рисуется ломаная линия (ширина и цвет);
4. **CircleObject** - содержит поля `"TopLeft": [x, y]`, `"BottomRight": [x, y]`, `"Position": [x, y]`, `"Size": [w, h]` и `"Pen": {"Width": width; "Color": color}`. Поля `"TopLeft": [x, y]` и `"BottomRight": [x, y]` задают ограничивающий прямоугольник эллипса. Поле `"Position": [x, y]` задаёт положение эллипса, поле `"Size": [w, h]` задаёт размеры эллипса;
5. **RectObject** - содержит поля `"TopLeft": [x, y]`, `"BottomRight": [x, y]`, `"Position": [x, y]`, `"Size": [w, h]` и `"Pen": {"Width": width; "Color": color}`. Поля `"TopLeft": [x, y]` и `"BottomRight": [x, y]` задают ограничивающий прямоугольник прямоугольника. Поле `"Position": [x, y]` задаёт положение прямоугольника, поле `"Size": [w, h]` задаёт размеры прямоугольника;
6. **ArrowObject** - содержит поля `"StartPoint": [x, y]`, `"EndPoint": [x, y]` и `"Pen": {"Width": width; "Color": color}`. Поля `"StartPoint": [x, y]` и `"EndPoint": [x, y]` задают начальную и конечную точки соответственно.
7. **TextObject** - содержит поля `"Position": [x, y]`, `"Text": "your_text_here"` и `"Pen": {"Width": width; "Color": color}`. Поле `"Position": [x, y]` задаёт положение текста. Поле `"Text": "your_text_here"` хранит сам текст.


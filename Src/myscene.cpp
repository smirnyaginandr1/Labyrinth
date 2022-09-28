#include "Inc/myscene.h"

#include "Inc/mymessagebox.h"
#include <QGraphicsView>
#include <cmath>
#include <QtConcurrent/QtConcurrent>
#include <QGraphicsSceneMouseEvent>

MyScene::MyScene(QObject *parent)
{
    //myThread = new FindThread();
    qRegisterMetaType<QVector<QPair<int, int>>* >("QVector<QPair<int, int>>*");

    connect(&myThreadFind, &FindThread::finish, this, &MyScene::PrintPath);
//    connect(&myThreadAddLine, &AddLineThread::finish, this, &MyScene::AddPixmap);
}

void MyScene::SetRadioButton(MapRectangle::Point cell)
{
    if(cell != MapRectangle::CellA && cell != MapRectangle::CellB)
        return;
    currentRadioButton = cell;
}

void MyScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() != Qt::LeftButton) //Проверка на ЛКМ
        return;

    MapRectangle* rect = MapRectangle::GetInstance();

    if (!rect->IsGenerate()){ //Проверка на сгенерированное поле
        MyMessageBox::ShowMessageBox("Поле не сгенерировано");
        return;
    }

    if (currentRadioButton == MapRectangle::CellVoid) //Проверка на установленный флажок буквы
    {
        MyMessageBox::ShowMessageBox("Нечего ставить");
        return;
    }

    QPointF point = event->scenePos();

    int indexWidth = (point.x() - views().at(0)->geometry().topLeft().x()) / offsetWidth; //Расчитываем индекс столбца, куда было нажатие
    int indexHeight = (point.y() - views().at(0)->geometry().topLeft().y()) / offsetHeight; //Расчитываем индекс строки, куда было нажатие

    if (indexHeight < 0 || indexHeight > rect->GetHeight() ||
        indexWidth < 0 || indexWidth < rect->GetWidth())
    {
        MyMessageBox::ShowMessageBox("Нажатие мимо поля");
        return;
    }


    if (rect->GetValueInCell(indexWidth, indexHeight)) //Проверка на занятую ячейку
    {
        MyMessageBox::ShowMessageBox("Ячейка уже занята");
        return;
    }

    ChangeItem(currentRadioButton, indexWidth, indexHeight); //Изменяем положение точки

    rect->SetLetter(currentRadioButton, indexWidth, indexHeight); //Изменяем положение точки в матрице

    if (items().contains(itemA.data()) && items().contains(itemB.data())) //Если А и В установлены - запускаем поток поиска пути
    {
        myThreadFind.start();
    }
}

//void MyScene::AddPixmap(QPixmap pixmap)
//{
//    addPixmap(pixmap);
//}

void MyScene::GenetateScene(int width, int height)
{//TODO: Убрать код в отдельный поток AddLineThread
    ReInitItems(); //Переинициализация точек

    MapRectangle* rect = MapRectangle::GetInstance();

    QPoint topLeft = views().at(0)->geometry().topLeft(); //Получение левой верхней точки представления
    QPoint bottomRight = views().at(0)->geometry().bottomRight(); //Получение правой нижней точки представления

    offsetWidth = (bottomRight.x() - topLeft.x()) / (static_cast<float>(width)); //Расчитываем новое расстояние между линиями стен
    offsetHeight = (bottomRight.y() - topLeft.y()) / (static_cast<float>(height));

    int i = 1;

    while(i < width || i < height) //Добавляем линии на полотно
    {
        if(i < width)
            addLine(topLeft.x() + round(offsetWidth * i),
                             topLeft.y(),
                             topLeft.x() + round(offsetWidth * i),
                             bottomRight.y() - 2);


        if(i < height)
            addLine(topLeft.x(),
                             topLeft.y() + round(offsetHeight * i),
                             bottomRight.x() - 2,
                             topLeft.y() + round(offsetHeight * i));

        i++;
    }


//    myThreadAddLine.ReInitParameters(topLeft, bottomRight, width, height);
//    myThreadAddLine.start();


    rect->FindWall([&](int indexWidth, int indexHeight){ //Ищем стены на матрице и запускаем лямбду для построения стены TODO: изменить координаты
        addRect(topLeft.x() + 3 + offsetWidth * (indexWidth),
                topLeft.y() + 3 + offsetHeight * (indexHeight),
                round(offsetWidth - 6),
                round(offsetHeight - 6),
                QPen(), QBrush(QColor("#000000")));
    });
    views().at(0)->setFocus();
}

void MyScene::ChangeItem(MapRectangle::Point item, int indexWidth, int indexHeight)
{
    if (item != MapRectangle::CellA && item != MapRectangle::CellB) //Если это не точка - выходим
        return;

    QGraphicsTextItem* changeItem = (item == MapRectangle::CellA) ? itemA.data() : itemB.data(); //Получаем наш textItem

    QPoint pointAdd(views().at(0)->geometry().topLeft().x() + (offsetWidth * indexWidth) + offsetWidth / 2,
                    views().at(0)->geometry().topLeft().y() + (offsetHeight * indexHeight) + offsetHeight / 2); //Считаем точку отрисовки

    int x = pointAdd.x() - changeItem->boundingRect().width() / 2; //Распологаем точку отрисовки в центре клетки
    int y = pointAdd.y() - changeItem->boundingRect().height() / 2;

    changeItem->setPos(x, y);
    if (!items().contains(changeItem))
        addItem(changeItem);
}


void MyScene::CreateItemPtr(MapRectangle::Point item)
{
    QSharedPointer<QGraphicsTextItem> changeItem = ((item == MapRectangle::CellA) ? std::move(itemA) : std::move(itemB));
    if (changeItem.isNull())
    {//Если умный указатель пустой - даём ему новый объект ячейки
        QGraphicsTextItem* newTextItem = new QGraphicsTextItem();
        newTextItem->setPlainText((item == MapRectangle::CellA) ? "A" : "B");
        newTextItem->setDefaultTextColor(QColor(255, 0, 0));
        changeItem = QSharedPointer<QGraphicsTextItem>(newTextItem);
    }
    ((item == MapRectangle::CellA) ? itemA: itemB) = std::move(changeItem);
}


void MyScene::ReInitItems()
{
    itemA.clear(); //Чистим указатели
    itemB.clear();

    ClearPathList();
    clear(); //Чистим сцену

    CreateItemPtr(MapRectangle::CellA); //Создаём QSharedPointer для двух ячеек
    CreateItemPtr(MapRectangle::CellB);
}


void MyScene::PrintPath(QVector<QPair<int, int>>* path){
    auto it = path->begin(); //Итератор на начало листа
    ClearPathList();

    while(it != path->end()) //бежим по листу по всем ячейкам
    {
        //Считаем первую точку линии
        QPoint pointFirst(views().at(0)->geometry().topLeft().x() + (offsetWidth * it->first) + offsetWidth / 2,
                          views().at(0)->geometry().topLeft().y() + (offsetHeight * it->second) + offsetHeight / 2);
        it++;

        if (it == path->end()) //Если точка последняя - дальше ничего не строим
            break;
        //Считаем вторую точку линии
        QPoint pointLast(views().at(0)->geometry().topLeft().x() + (offsetWidth * it->first) + offsetWidth / 2,
                         views().at(0)->geometry().topLeft().y() + (offsetHeight * it->second) + offsetHeight / 2);

        QGraphicsLineItem* line = new QGraphicsLineItem(pointFirst.x(), pointFirst.y(), pointLast.x(), pointLast.y());
        listItemsPath.push_back(line); //Добавляем линию в лист

        addItem(line);
    }
    path->clear(); //Чистим аргумент
}


void MyScene::ClearPathList()
{
    for (int i = 0; i < listItemsPath.size(); i++) //Чистим линии пути
        delete listItemsPath.at(i);
    listItemsPath.clear();
}


MyScene::~MyScene()
{
    ClearPathList();
}

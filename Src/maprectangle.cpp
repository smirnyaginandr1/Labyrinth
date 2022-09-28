#include "Inc/maprectangle.h"
#include "Inc/mymessagebox.h"

MapRectangle* MapRectangle::obj = nullptr;

MapRectangle::MapRectangle()
{

}

void MapRectangle::GenerateMap(int width, int height, int percent)
{
    is_generate = true;
    if (height == mapRectangle.size() && width == mapRectangle.begin()->size()){ //Заполнение в первый запуск (если вектор пустой)
        for (auto &itH : mapRectangle){
            itH.clear(); //Очистка каждого листа в строке
            itH.resize(width); //Задаём новый размер
        }
    }
    else
    {
        mapRectangle.resize(height); //Задаём новый размер листа (количество строк)

        for(auto &it : mapRectangle){
            it.resize(width); //Задаём новый размер листа (количество столбцов)
        }
    }
    for (auto &itH : mapRectangle){ //Рандомно заполняем лист в зависимости от процента
        for (auto &itW :itH){
            if (qrand() % (100) <= percent)
                itW = CellWall;
        }
    }
}

void MapRectangle::SetLetter(Point cell, int indexWidth, int indexHeight)
{
    if ((cell != CellA) && (cell != CellB)) //Проверка на устанавливаемую точку
        return;

    for (auto &itH : mapRectangle){ //Ищем нужную нам точку для стирания
        if (itH.contains(cell)){
            QVector<Point>::iterator it = std::find(itH.begin(), itH.end(), cell);
            *it = CellVoid;
            break;
        }
    }

    mapRectangle[indexHeight][indexWidth] = cell; //Устанавливаем новое значение точки
}

MapRectangle::Point MapRectangle::GetValueInCell(int indexWidth, int indexHeight)
{
    return mapRectangle.at(indexHeight).at(indexWidth);
}

void MapRectangle::FindWall(std::function<void (int, int)> func){
    for (auto &itH : mapRectangle){ //Поиск стены для отрисовки
        for (auto &itW: itH){
            if (itW == MapRectangle::CellWall)
              func(&itW - itH.begin(), &itH - mapRectangle.begin()); //Если попалась стена - вызываем переданный метод для отрисовки
        }
    }
}


QPair<int, int> MapRectangle::GetIndexCell(MapRectangle::Point cell)
{
    if (cell == Point::CellA || cell == Point::CellB) //Если не А и не В - возвращаем -1 -1
        for (auto &itH : mapRectangle){ //Ищем точку в листе
            for (auto &itW: itH){
                if (itW == cell)
                    //Отправляем координаты в виде ключ - значение
                    return QPair<int, int>(&itW - itH.begin(), &itH - mapRectangle.begin());//(width, height)
            }
        }
    return QPair<int, int>(-1, -1);
}

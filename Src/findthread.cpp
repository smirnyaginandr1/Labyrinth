#include "Inc/findthread.h"
#include <QQueue>
#include <QArrayData>
FindThread::FindThread()
{
    di[0] = -1;
    di[1] = 0;
    di[2] = 1;
    di[3] = 0;
}

void FindThread::run() //Метод реализует поиск в ширину по графу
{
    MapRectangle* rect = MapRectangle::GetInstance();

    int heightMap = rect->GetHeight();
    int widthMap = rect->GetWidth();

    QPair<int, int> cellA = rect->GetIndexCell(MapRectangle::CellA);
    QPair<int, int> cellB = rect->GetIndexCell(MapRectangle::CellB);

    int** d = new int*[heightMap]; //Создание матрицы смежности. Выделяем память в куче, т.к. при большом значении стек может переполниться
    for (int i = 0; i < heightMap; i++)
    {
        d[i] = new int[widthMap];
        for (int j = 0; j < widthMap; j++)
            d[i][j] = 0;
    }

    int head = 0, tail = 0; //Указатели очереди TODO: переделать на QQueue
    Point* queue = new Point[heightMap * widthMap]; //Очередь

    d[cellA.second][cellA.first] = 1; //Расстояние до начальной клетки равно 1

    //Инициализация очереди
    head = tail = 0;
    queue[tail].i = cellA.second;
    queue[tail++].j = cellA.first; //Заносим в очередь начальную клетку

    while (head < tail){     //Цикл пока очередь не пуста
       Point p = queue[head++];          //Берем следующую позицию из очереди
       for (int k = 0; k < 4; k++)       //Цикл по соседним клеткам
       {
          Point newp;
          newp.i = p.i + di[k];
          newp.j = p.j + di[3 - k];
          //Проверяем, что такая клетка есть
          if (0 <= newp.i && newp.i < heightMap && 0 <= newp.j && newp.j < widthMap)
             //Проверяем, что она свободна и ранее ее не посещали
             if (rect->GetValueInCell(newp.j, newp.i) != MapRectangle::CellWall && d[newp.i][newp.j] == 0)
             {
                d[newp.i][newp.j] = d[p.i][p.j] + 1;     //Находим расстояние
                queue[tail++] = newp;                    //Заносим позицию в очередь
             }
       }
    }

    if (d[cellB.second][cellB.first]) //Проверяем на найденный путь
    { //Если путь найден - заполняем лист пути
        int widthCnt = cellB.first;
        int heightCnt = cellB.second;

        lastPath.push_back(QPair<int, int>(widthCnt, heightCnt)); //Добавляем первую точку в лист
        for(int i = d[heightCnt][widthCnt]; i != 1; i--)
        {//Ищем значение, меньшее на 1
            if (d[heightCnt][widthCnt] - 1 == d[heightCnt][widthCnt - 1])
                widthCnt--;

            else if (d[heightCnt][widthCnt] - 1 == d[heightCnt][widthCnt + 1])
                widthCnt++;


            else if (d[heightCnt][widthCnt] - 1 == d[heightCnt - 1][widthCnt])
                heightCnt--;

            else
                heightCnt++;

            lastPath.push_front(QPair<int, int>(widthCnt, heightCnt));  //Добавляем точку в начало пути
        }

        emit finish(&lastPath); //Вызываем слот отрисовки пути
    }

    //Очистка памяти из под матрицы смежности и очереди
    for (int i = 0; i < heightMap; i++)
    {
        delete[] d[i];
    }
    delete[] d;
    delete[] queue;
}

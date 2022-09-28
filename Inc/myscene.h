#ifndef MYSCENE_H
#define MYSCENE_H
#include <QGraphicsScene>
#include "maprectangle.h"
#include <QSharedPointer>
#include <QGraphicsTextItem>
#include <QList>
#include "findthread.h"
//#include "addlinethread.h"
//#include <QPixmap>

/**
 * @brief Класс унаследованной сцены
 * @details Класс обрабатывает данные, которые отображаются на @ref MyView
 */
class MyScene : public QGraphicsScene
{
public:
    /**
     * @brief Конструктор сцены
     * @details Подключает сигналы потоков к слотам этого класса
     */
    MyScene(QObject *parent = nullptr);


public slots:
    /**
     * @brief Слот генерации сцены
     * @details Генерирует границы ячеек лабиринта и стены в лабиринте
     * @param width - количество столбцов
     * @param height - количество строк
     */
    void GenetateScene(int width, int height);

    /**
     * @brief Слот установки текущего значения ячейки (A или B)
     * @param cell - устанавливаемая ячейка
     */
    void SetRadioButton(MapRectangle::Point cell);

    /**
     * @brief Слот печати пути
     * @details Добавляет линии пути на сцену по точкам из полученного листа @ref path
     * @param path - лист точек, представляющих путь от А до В. Содержит индексы точек в виде ключ - значение
     */
    void PrintPath(QVector<QPair<int, int>>* path);
//    void AddPixmap(QPixmap pixmap);

protected:
    /**
     * @brief Метод нажатия на представление
     * @details Проверяет клетку нажатия и устанавливает точку (A или B)
     * @param event - событие нажатия на view
     */
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

private:
    ///Текущая нажатая точка (А или В)
    MapRectangle::Point currentRadioButton = MapRectangle::CellVoid;

    /**
     * @brief Метод инициализации умного указателя
     * @param item - точка, для которой нужно создать указатель (@ref itemA, @ref itemB)
     */
    void CreateItemPtr(MapRectangle::Point item);

    ///Расстояние между столбцами
    float offsetWidth;

    ///Расстояние между строками
    float offsetHeight;

    ///Умный указатель на точку A
    QSharedPointer<QGraphicsTextItem> itemA;

    ///Умный указатель на точку B
    QSharedPointer<QGraphicsTextItem> itemB;

    /**
     * @brief Метод очистки листа, содержащего кратчайший путь @ref listItemsPath
     */
    void ClearPathList();

    /**
     * @brief Метод переинициализации @ref itemA и @ref itemB
     */
    void ReInitItems();

    ///Объект потока поиска кратчайшего пути
    FindThread myThreadFind;
//    AddLineThread myThreadAddLine;
    ///Указатель на лист с кратчайшим путём. Содержит линии между точками
    QList<QGraphicsItem*> listItemsPath;

    /**
     * @brief Метод изменения точки (@ref itemA или @ref itemB)
     * @param item - @ref itemA или @ref itemB
     * @param indexWidth - индекс столбца нового места точки
     * @param indexHeight - индекс строки нового места точки
     */
    void ChangeItem(MapRectangle::Point item, int indexWidth, int indexHeight);

    /**
     * @brief Деструктор класса
     * @details Очищает кратчайший путь
     */
    ~MyScene();
};

#endif // MYSCENE_H

#ifndef MAPRECTANGLE_H
#define MAPRECTANGLE_H
#include <QVector>
#include <QObject>
#include <functional>

/**
 * @brief Класс работы с матрицей элементов
 * @details Матрица внутри класса представлена как вектор векторов (@ref mapRectangle)
 */
class MapRectangle : public QObject
{
public:
    /**
     * @brief Перечисление возможных значений в матрице
     */
    enum Point : uint8_t{
      CellVoid = 0, ///< Пустая клетка
      CellWall = 1, ///< Клетка стена
      CellA = 2, ///< Клетка А
      CellB = 4 ///< Клетка B
    };

    /**
     * @brief Статический геттер объекта
     * @return Единственный созданный экземпляр класса
     */
    static inline MapRectangle* GetInstance()
    {
        if (obj == nullptr)
            obj = new MapRectangle();
        return obj;
    }

    /**
     * @brief Установка буквы в матрицу
     * @param cell - Устанавливаемая буква
     * @param coordX - Индекс столбца
     * @param coordY - Индекс строки
     */
    void SetLetter(Point cell, int coordX, int coordY);

    /**
     * @brief Геттер количества столбцов
     * @return Количество столбцов
     */
    inline int GetWidth(){return mapRectangle.begin()->size();}

    /**
     * @brief Геттер количества строк
     * @return Количество строк
     */
    inline int GetHeight(){return mapRectangle.size();}

    /**
     * @brief Геттер готовности генерации
     * @return is_generate -/ntrue - матрица сгенерирована/nfalse - матрица не сгенерирована
     */
    inline bool IsGenerate(){return is_generate;}

    /**
     * @brief Геттер значения в ячейке
     * @param indexWidth - Индекс столбца
     * @param indexHeight - Индекс строки
     * @return Значение, хранимое в ячейке матрицы
     */
    Point GetValueInCell(int indexWidth, int indexHeight);

    /**
     * @brief Сеттер значения ячейки
     * @param indexWidth - Индекс столбца
     * @param indexHeight - Индекс строки
     * @param cell - Новое значение ячейки
     */
    void SetValueInCell(int indexWidth, int indexHeight, Point cell);

    /**
     * @brief Метод построения стены
     * @details Осуществляет поиск ячеек со значением "стена" и вызывает метод установки стены
     * @param func - Указатель на метод установки стены
     */
    void FindWall(std::function<void(int, int)> func);

    /**
     * @brief Геттер индекса ячейки
     * @details Осуществляет поиск в матрице ячейки A или В
     * @param cell - значение искомой ячейки
     * @return Индексы ячейки в формате ключ - значение (столбец, строка)
     */
    QPair<int, int> GetIndexCell(Point cell);

    ///Вектор векторов для хранения ячеек (матрица)
    QVector<QVector<Point>> mapRectangle = QVector<QVector<Point>>(CellVoid);


public slots:

    /**
     * @brief Слот генерации матрицы
     * @param width - количество столбцов
     * @param height - количество строк
     * @param percent = процент заполнения стенами
     */
    void GenerateMap(int width, int height, int percent);

private:

    /**
     * @brief Флаг инициализации матрицы
     * @details Выставляется в true, когда матрица сгенерирована. Иначе - false
     */
    bool is_generate = false;

    /**
     * @brief Приватный конструктор
     * @details Реализация одиночки
     */
    MapRectangle();


    ///Указатель на единственный объект класса @ref MapRectangle
    static MapRectangle* obj;
};

#endif // MAPRECTANGLE_H

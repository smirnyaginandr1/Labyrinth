#ifndef FINDTHREAD_H
#define FINDTHREAD_H
#include <QThread>
#include "maprectangle.h"

/**
 * @brief Класс унаследован от QThread
 * @details Класс производит расчёт кратчайшего пути от точки до точки в отдельном потоке
 */
class FindThread : public QThread
{
    Q_OBJECT
public:
    /**
     * @brief Конструктор класса потока
     * @details Инициализирует массив @ref di
     */
    FindThread();

signals:
    /**
     * @brief Сигнал окончания работы метода @ref run()
     * @param path - указатель на созданный вектор пути
     */
    void finish(QVector<QPair<int, int>>* path);

protected:
    void run() override;

private:
    ///Структура точки
    typedef struct Point {
        int i, j; ///< Координаты точки
    }Point;


    ///Массив, содержащий значение шага по матрице смежности
    int8_t di[4];

    ///Вектор, содержащий последний пройденный путь
    QVector<QPair<int, int>> lastPath;
};

#endif // FINDTHREAD_H

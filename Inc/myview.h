#ifndef MYVIEW_H
#define MYVIEW_H
#include <QGraphicsView>
#include <QWheelEvent>

/**
 * @brief Класс унаследованного представления
 * @details Класс обрабатывает колесо мыши (@ref wheelEvent) и ведение указателем мыши по полотну (@ref mouseMoveEvent)
 */
class MyView : public QGraphicsView
{
public:
    /**
     * @brief Конструктор представления
     */
    MyView();

protected:
    /**
     * @brief Метод вызывается при прокрутке колесом мыши (при наведении на view)
     * @param event - событие прокрутки
     */
    void wheelEvent(QWheelEvent* event) override;

    /**
     * @brief Метод вызывается при ведении указателем мыши (при наведении на view)
     * @param event - событие ведения мыши
     */
    void mouseMoveEvent(QMouseEvent *event) override;
};

#endif // MYVIEW_H

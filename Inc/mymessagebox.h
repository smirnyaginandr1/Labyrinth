#ifndef MYMESSAGEBOX_H
#define MYMESSAGEBOX_H
#include <QString>
#include <QMessageBox>

/**
 * @brief Статический класс вывода окна ошибки на экран
 */
class MyMessageBox
{
public:
    /**
     * @brief Статический метод вызова окна ошибки
     * @param str - строка в сообщении
     */
    static void ShowMessageBox(QString str);
private:

    /**
     * @brief Приватный конструктор
     */
    MyMessageBox();
};

#endif // MYMESSAGEBOX_H

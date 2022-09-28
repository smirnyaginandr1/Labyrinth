#ifndef DIGITSVALIDATOR_H
#define DIGITSVALIDATOR_H
#include <QValidator>

/**
 * @brief Класс унаследован от QValidator
 * @details Представляет класс для обработки введённых строк
 */
class DigitsValidator : public QValidator
{
public:
    /**
     * @brief Конструктор валидатора
     */
    DigitsValidator(QObject* parent = nullptr);

    /**
     * @brief Метод проверки введёных символов
     * @param text - ссылка на проверяемую строку
     * @return Полученная валидность
     */
    QValidator::State validate(QString& text, int& /*position*/) const;

private:
    ~DigitsValidator();
};

#endif // DIGITSVALIDATOR_H

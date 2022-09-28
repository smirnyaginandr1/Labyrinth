#include "Inc/digitsvalidator.h"
#include "Inc/mymessagebox.h"

DigitsValidator::DigitsValidator(QObject* parent) : QValidator(parent) {}

QValidator::State DigitsValidator::validate(QString& text, int& /*position*/) const {
    QRegExp digitsRool("[^\\d]"); //Регулярное выражение (пропускает только цифры)

    if (text.contains(digitsRool)) {
        MyMessageBox::ShowMessageBox("Можно вводить только цифры"); //В случае ошибки вызывает окно
        return Invalid;
    }
    return Acceptable;
}

DigitsValidator::~DigitsValidator() {}

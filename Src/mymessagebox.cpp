#include "Inc/mymessagebox.h"

MyMessageBox::MyMessageBox(){}


void MyMessageBox::ShowMessageBox(QString str)
{
    QMessageBox* box = new QMessageBox();
    box->setAttribute(Qt::WA_DeleteOnClose, true); //Устанавливаем флаг очистки
    box->setText(str);
    box->setWindowTitle("Error!");
    box->show();
}

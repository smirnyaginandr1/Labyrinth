 #include "Inc/mainwindow.h"
#include "ui_mainwindow.h"
#include "Inc/mymessagebox.h"
#include <QScrollBar>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ReadSettings(); //Считываем файл настроек (если таковой имеется)

    scene = new MyScene(); //Создание сцены для работы с QGraphicsView
    view = new MyView(); //Создание QGraphicsView
    view->setScene(scene); //Крепим сцену к view
    ui->verticalLayout_2->addWidget(view); //Добавляем на форму view
//    view->verticalScrollBar()->installEventFilter(this);

    validator = new DigitsValidator(); //Создаём класс валидатора для проверки строк

    ui->widthLineEdit->setValidator(validator); //Устанавливаем валидатор
    ui->heightLineEdit->setValidator(validator);
    ui->percentLineEdit->setValidator(validator);

    ui->widthLineEdit->setMaxLength(4); //Максимальная длина вводимых значений
    ui->heightLineEdit->setMaxLength(4);
    ui->percentLineEdit->setMaxLength(3);

    mapRect = MapRectangle::GetInstance(); //Инициализация матрицы

    connect(this, &MainWindow::StartGenerate, mapRect, &MapRectangle::GenerateMap); //Сигнал старта генерации для матрицы
    connect(this, &MainWindow::StartGenerate, scene, &MyScene::GenetateScene); //Сигнал старта генерации для сцены
    connect(this, &MainWindow::ClickRadioButton, scene, &MyScene::SetRadioButton); //Сигнал изменения точки для сцены
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_generateButton_clicked()
{
    width = ui->widthLineEdit->text().toInt(); //Получаем длину и ширину
    height = ui->heightLineEdit->text().toInt();
    int percent = ui->percentLineEdit->text().toInt();

    if (width == 0 || height == 0 || (width == 1 && height == 1)) //Проверка на маленькие числа
    {
        MyMessageBox::ShowMessageBox("Неверное выражение длины или ширины");
        return;
    }

    if (percent < 0 || percent > 100) //Проверка процента заполнения
    {
        MyMessageBox::ShowMessageBox("Некорректный процент заполнения");
        return;
    }

    emit StartGenerate(width, height, percent); //Запуск генерации
    view->setFocus();
}

void MainWindow::on_radioButtonA_clicked()
{
    emit ClickRadioButton(MapRectangle::CellA); //Установить текущую точку
    view->setFocus();
}

void MainWindow::on_radioButtonB_clicked()
{
    emit ClickRadioButton(MapRectangle::CellB); //Установить текущую точку
    view->setFocus();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    QSettings settings("Settings.ini", QSettings::IniFormat); //Сохранение настроек в отдельный файл для сохранения местоположения окна
    settings.setValue("geometry", saveGeometry());
    settings.setValue("windowState", saveState());
    QMainWindow::closeEvent(event);
}

void MainWindow::ReadSettings()
{
    QSettings settings("Settings.ini", QSettings::IniFormat); //Чтение настроек из файла (местоположения окна)
    restoreGeometry(settings.value("geometry").toByteArray());
    restoreState(settings.value("windowState").toByteArray());
}

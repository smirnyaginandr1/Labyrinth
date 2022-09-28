#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "digitsvalidator.h"
#include "maprectangle.h"
#include "myscene.h"
#include "myview.h"
#include <QSettings>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


signals:
    /**
     * @brief Сигнал начала генерации
     * @param width - количество столбцов матрицы
     * @param height - количество строк матрицы
     * @param percent - процент заполнения
     */
    void StartGenerate(int width, int height, int percent);

    /**
     * @brief Сигнал нажатия на RadioButton
     * @param point - нажатая кнопка
     */
    void ClickRadioButton(MapRectangle::Point point);

protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    /**
     * @brief Слот нажатия на кнопку генерации
     */
    void on_generateButton_clicked();

    /**
     * @brief Слот нажатия на RadioButton со значением А
     */
    void on_radioButtonA_clicked();

    /**
     * @brief Слот нажатия на RadioButton со значением B
     */
    void on_radioButtonB_clicked();

private:
    Ui::MainWindow *ui;

    ///Указатель на созданный валидатор
    DigitsValidator *validator;

    /**
     * @brief Чтение настроек из файла (местоположение окна)
     */
    void ReadSettings();

    ///Указатель на созданную @ref MyScene
    MyScene* scene;

    ///Указатель на созданное @ref MyView
    MyView* view;

    ///Указатель на матрицу @ref MapRectangle
    MapRectangle* mapRect;

    ///Количество столбцов матрицы
    uint32_t width = 0;

    ///Количество строк матрицы
    uint32_t height = 0;
};
#endif // MAINWINDOW_H

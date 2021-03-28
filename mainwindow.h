#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "trem.h"
#include <qsemaphore.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


public slots:
    void updateInterface(int,int,int);

private slots:
    // Botões
    void on_pb_liga_clicked();
    void on_pb_para_clicked();
    void on_pb_max_clicked();
    void on_pb_min_clicked();
    void on_pb_random_clicked();

    // Sliders
    void on_t1_slider_valueChanged(int value);
    void on_t2_slider_valueChanged(int value);
    void on_t3_slider_valueChanged(int value);
    void on_t4_slider_valueChanged(int value);
    void on_t5_slider_valueChanged(int value);

private:
    Ui::MainWindow *ui;
    // Lista de semáforos
    std::vector<QSemaphore*> semaphore;
    //Cria os objetos TREM's
    Trem *trem1;
    Trem *trem2;
    Trem *trem3;
    Trem *trem4;
    Trem *trem5;
};

#endif // MAINWINDOW_H

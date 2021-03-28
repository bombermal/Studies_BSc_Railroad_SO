#include "mainwindow.h"
#include "ui_mainwindow.h"
//#include <stdlib.h> // Random

// Semáforos para cada região
QSemaphore sem1(0);
QSemaphore sem2(0);
QSemaphore sem3(0);
QSemaphore sem4(-1);
QSemaphore sem5(0);
QSemaphore sem6(0);
QSemaphore sem7(0);

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Adiciona os semáforos no vetor
    semaphore.push_back(&sem1);
    semaphore.push_back(&sem2);
    semaphore.push_back(&sem3);
    semaphore.push_back(&sem4);
    semaphore.push_back(&sem5);
    semaphore.push_back(&sem6);
    semaphore.push_back(&sem7);

    // Cria o trem com seu (ID, posição X, posição Y, e o vetor de semáforos)
    trem1 = new Trem(1,60,30, semaphore);
    trem2 = new Trem(2,330,30, semaphore);
    trem3 = new Trem(3,600,30, semaphore);
    trem4 = new Trem(4,190,150, semaphore);
    trem5 = new Trem(5,460,150, semaphore);

    /*
     * Conecta o sinal UPDATEGUI à função UPDATEINTERFACE.
     * Ou seja, sempre que o sinal UPDATEGUI foi chamado, será executada a função UPDATEINTERFACE.
     * Os 3 parâmetros INT do sinal serão utilizados na função.
     * Trem1 e Trem2 são os objetos que podem chamar o sinal. Se um outro objeto chamar o
     * sinal UPDATEGUI, não haverá execução da função UPDATEINTERFACE
     */
    connect(trem1,SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));
    connect(trem2,SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));
    connect(trem3,SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));
    connect(trem4,SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));
    connect(trem5,SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));

}

//Função que será executada quando o sinal UPDATEGUI for emitido
void MainWindow::updateInterface(int id, int x, int y){
    switch(id){
    case 1: //Atualiza a posição do objeto da tela (quadrado) que representa o trem1
        ui->label_trem1->setGeometry(x,y,21,17);
        break;
    case 2: //Atualiza a posição do objeto da tela (quadrado) que representa o trem2
        ui->label_trem2->setGeometry(x,y,21,17);
        break;
    case 3: //Atualiza a posição do objeto da tela (quadrado) que representa o trem2
        ui->label_trem3->setGeometry(x,y,21,17);
        break;
    case 4: //Atualiza a posição do objeto da tela (quadrado) que representa o trem2
        ui->label_trem4->setGeometry(x,y,21,17);
        break;
    case 5: //Atualiza a posição do objeto da tela (quadrado) que representa o trem2
        ui->label_trem5->setGeometry(x,y,21,17);

        break;
    default:
        break;
    }

    // Atualiza textos mostrados na tela, valor do semáforo e velocidade do trem
    ui->label_r1->setText("R1: "+QString::number(trem4->getSem(0))+" →");
    ui->label_r2->setText("R2: "+QString::number(trem4->getSem(1))+" →");
    ui->label_r3->setText("↑ R3: "+QString::number(trem4->getSem(2)));
    ui->label_r4->setText("↓ R4: "+QString::number(trem4->getSem(3)));
    ui->label_r5->setText("↑ R5: "+QString::number(trem4->getSem(4)));
    ui->label_r6->setText("↓ R6: "+QString::number(trem4->getSem(5)));
    ui->label_r7->setText("R7: "+QString::number(trem4->getSem(6))+" →");
    ui->veloci_1->setText("Trem 1: "+QString::number(trem1->getVelocity())+" ms/un");
    ui->veloci_2->setText("Trem 2: "+QString::number(trem2->getVelocity())+" ms/un");
    ui->veloci_3->setText("Trem 3: "+QString::number(trem3->getVelocity())+" ms/un");
    ui->veloci_4->setText("Trem 4: "+QString::number(trem4->getVelocity())+" ms/un");
    ui->veloci_5->setText("Trem 5: "+QString::number(trem5->getVelocity())+" ms/un");
}

MainWindow::~MainWindow()
{
    delete ui;
}

/*
 * Ao clicar, trens começam execução
 */
void MainWindow::on_pb_liga_clicked()
{
    trem1->start();
    trem2->start();
    trem3->start();
    trem4->start();
    trem5->start();
}

/*
 * Ao clicar, trens param execução
 */
void MainWindow::on_pb_para_clicked()
{
    trem1->terminate();
    trem2->terminate();
    trem3->terminate();
    trem4->terminate();
    trem5->terminate();
}

// Execução do botão Max, define a velocidade
// máxima para movimentação
void MainWindow::on_pb_max_clicked()
{
    int val = 1;
    // Update Trem
    trem1->setVelocity(val);
    trem2->setVelocity(val);
    trem3->setVelocity(val);
    trem4->setVelocity(val);
    trem5->setVelocity(val);
    // Update Slider
    ui->t1_slider->setValue(val);
    ui->t2_slider->setValue(val);
    ui->t3_slider->setValue(val);
    ui->t4_slider->setValue(val);
    ui->t5_slider->setValue(val);
}
// Execução do botão Min, define a velocidade
// minima para movimentação
void MainWindow::on_pb_min_clicked()
{
    int val = 500;
    // Update Trem
    trem1->setVelocity(val);
    trem2->setVelocity(val);
    trem3->setVelocity(val);
    trem4->setVelocity(val);
    trem5->setVelocity(val);
    // Update Slider
    ui->t1_slider->setValue(val);
    ui->t2_slider->setValue(val);
    ui->t3_slider->setValue(val);
    ui->t4_slider->setValue(val);
    ui->t5_slider->setValue(val);
}
// Execução do botão Random, define uma velocidade
// aleatória para movimentação, entre 1 e 500
void MainWindow::on_pb_random_clicked()
{
    int t1 = rand() % 500 + 1;
    int t2 = rand() % 500 + 1;
    int t3 = rand() % 500 + 1;
    int t4 = rand() % 500 + 1;
    int t5 = rand() % 500 + 1;
    //Update Trem
    trem1->setVelocity(t1);
    trem2->setVelocity(t2);
    trem3->setVelocity(t3);
    trem4->setVelocity(t4);
    trem5->setVelocity(t5);
    // Update Slider
    ui->t1_slider->setValue(t1);
    ui->t2_slider->setValue(t2);
    ui->t3_slider->setValue(t3);
    ui->t4_slider->setValue(t4);
    ui->t5_slider->setValue(t5);
}

// Defino as velocidades baseadas nos slides e mostro o valor
// no texto
void MainWindow::on_t1_slider_valueChanged(int value)
{
    trem1->setVelocity(value);
}

void MainWindow::on_t2_slider_valueChanged(int value)
{

    trem2->setVelocity(value);
}

void MainWindow::on_t3_slider_valueChanged(int value)
{

    trem3->setVelocity(value);
}

void MainWindow::on_t4_slider_valueChanged(int value)
{

    trem4->setVelocity(value);
}

void MainWindow::on_t5_slider_valueChanged(int value)
{

    trem5->setVelocity(value);
}

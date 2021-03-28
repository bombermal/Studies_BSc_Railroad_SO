#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <stdlib.h>

#define SHARED 0

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Cria semaforos para região crítica, um vetor ou um para cada?

    semaphore = new std::vector<QSemaphore*>();
    for (int i = 0; i < 7; i++) {
        QSemaphore sem(1);
        semaphore->push_back(&sem);
    }


    //Cria o trem com seu (ID, posição X, posição Y)
    trem1 = new Trem(1,60,30,60,30, semaphore);
    trem2 = new Trem(2,330,30,330,30, semaphore);
    trem3 = new Trem(3,600,30,600,30, semaphore);
    trem4 = new Trem(4,190,150,190,150, semaphore);
    trem5 = new Trem(5,460,150,460,150, semaphore);

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


//    for ( int i = 0; i<7;i++){
//        sem_destroy(&rg[i]);
//    }
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
    ui->label->setText(QString::number(trem1->getX())+" - "+QString::number(trem1->getY()));
    ui->label_2->setText( QString::number(trem2->getX())+" - "+QString::number(trem2->getY()));
    ui->label_3->setText( QString::number(trem3->getX())+" - "+QString::number(trem3->getY()));
    ui->label_4->setText( QString::number(trem4->getX())+" - "+QString::number(trem4->getY()));
    ui->label_5->setText( QString::number(trem5->getX())+" - "+QString::number(trem5->getY()));
    ui->label_6->setText(QString::number(trem1->getMolex()));
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
    QString vel{"Velocidade: "};
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
    // Update texto
    ui->label->setText( vel +QString::number(val));
    ui->label_2->setText( vel +QString::number(val));
    ui->label_3->setText( vel +QString::number(val));
    ui->label_4->setText( vel +QString::number(val));
    ui->label_5->setText( vel +QString::number(val));
}
// Execução do botão Min, define a velocidade
// minima para movimentação
void MainWindow::on_pb_min_clicked()
{
    int val = 500;
    QString vel{"Velocidade: "};
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
    // Update texto
    ui->label->setText( vel +QString::number(val));
    ui->label_2->setText( vel +QString::number(val));
    ui->label_3->setText( vel +QString::number(val));
    ui->label_4->setText( vel +QString::number(val));
    ui->label_5->setText( vel +QString::number(val));
}
// Execução do botão Random, define uma velocidade
// aleatória para movimentação, entre 1 e 500
void MainWindow::on_pb_random_clicked()
{
    QString vel{"Velocidade: "};
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
    // Update texto
    ui->label->setText( vel +QString::number(t1));
    ui->label_2->setText( vel +QString::number(t2));
    ui->label_3->setText( vel +QString::number(t3));
    ui->label_4->setText( vel +QString::number(t4));
    ui->label_5->setText( vel +QString::number(t5));
}

// Defino as velocidades baseadas nos slides e mostro o valor
// no texto
void MainWindow::on_t1_slider_valueChanged(int value)
{
    QString vel{"Velocidade: "};
    ui->label->setText( vel +QString::number(value));
    trem1->setVelocity(value);
}

void MainWindow::on_t2_slider_valueChanged(int value)
{
    QString vel{"Velocidade: "};
    ui->label_2->setText( vel +QString::number(value));
    trem2->setVelocity(value);
}

void MainWindow::on_t3_slider_valueChanged(int value)
{
    QString vel{"Velocidade: "};
    ui->label_3->setText( vel +QString::number(value));
    trem3->setVelocity(value);
}

void MainWindow::on_t4_slider_valueChanged(int value)
{
    QString vel{"Velocidade: "};
    ui->label_4->setText( vel +QString::number(value));
    trem4->setVelocity(value);
}

void MainWindow::on_t5_slider_valueChanged(int value)
{
    QString vel{"Velocidade: "};
    ui->label_5->setText( vel +QString::number(value));
    trem5->setVelocity(value);
}

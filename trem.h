#ifndef TREM_H
#define TREM_H

#include <QThread>
#include <qsemaphore.h>
#include <pthread.h>


class Trem: public QThread{
 Q_OBJECT
public:
    Trem(int,int,int,std::vector<QSemaphore*>);  //construtor
    void run();
    // Funções customizadas
    void updatePosition();  // Atualiza a posição do trem
    void updateSemaphore(); // Controla os semáforos
    void setVelocity(int);  // Define a velocidade do trem
    int getVelocity();      // Pega a velocidade atual do trem
    int getSem(int);        // Pega o valor que está no semáforo

//Cria um sinal
signals:
    void updateGUI(int,int,int);

private:
   int x;           //posição X do trem na tela
   int y;           //posição Y do trem na tela
   int ID;          //ID do trem
   int velocidade;  //Velocidade. É o tempo de dormir em milisegundos entre a mudança de posição do trem
   int startx;      // Coordenada de início X
   int starty;      // Coordenada de início Y
   std::vector<QSemaphore*> semaphore; // Vetor de semáforos compartilhado entre os trens
};

#endif // TREM_H

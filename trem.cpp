#include "trem.h"
#include <QtCore>

//Construtor
Trem::Trem(int ID, int x, int y, std::vector<QSemaphore*> semaphore){
    this->ID = ID;      // ID
    this->x = x;        // Coordenada X
    this->y = y;        // Coordenada Y
    this->startx = x;   // Coordenada de início X
    this->starty = y;   // Coordenada de início Y
    this->semaphore = semaphore; // Vetor de semáforos
    velocidade = 100;    // Velocidade de movimentação

}

// Função criada para atualizar a posição dos trens
// baseados em seu ponto inicial de partida
void Trem::updatePosition(){
    int hLength = 270; // Largura do trilho
    int vLength = 120; // Altura do trilho

    // Verifica os limites e atualiza a posição
    if (y == starty && x <startx+hLength)
        x+=10;
    else if (x == startx+hLength && y < starty+vLength)
        y+=10;
    else if (x > startx && y == starty+vLength)
        x-=10;
    else
        y-=10;
}

// Define a velocidade do trem
void Trem::setVelocity(int v){
    this->velocidade = v;
}
// Retorna a velocidade do trem
int Trem::getVelocity(){
    return this->velocidade;
}

// Retorna o valor atual do semáforo
int Trem::getSem(int p){
    return this->semaphore.at(p)->available();
}

// Verifica as posições dos trens e atualiza o valor dos semáforos
void Trem::updateSemaphore(){
    switch(ID){
        case 1:
            // Verifica a posição do trem 1
            // Trava o os trilhos R1 e R3
            if ( x == 310 && y == 30 ){
                semaphore.at(0)->acquire();
                semaphore.at(2)->acquire();
            }
            // Libera R1
            if( x == 310 && y == 150 ){
                semaphore.at(0)->release();
            }
            // Libera R3
            if( x == 170 && y == 150 ){
                semaphore.at(2)->release();
            }
        break;
        case 2:
            // Verifica a posição do trem 2
            // Trava o os trilhos R2 e R5
            if ( x == 580 && y == 30 ){
                semaphore.at(1)->acquire();
                semaphore.at(4)->acquire();
            }
            // Trava o os trilhos R1 e R4
            if ( x == 480 && y == 150 ){
                semaphore.at(0)->acquire();
                semaphore.at(3)->acquire();
            }
            // Libera R2 e R5
            if (x == 440 && y == 150 ){
                semaphore.at(1)->release();
                semaphore.at(4)->release();
            }
            // Libera R1 e R4
            if ( x == 350 && y == 30 ){
                semaphore.at(0)->release();
                semaphore.at(3)->release();
            }
        break;
        case 3:
            // Verifica a posição do trem 3
            // Trava o os trilhos R2 e R6
            if ( x == 750 && y == 150 ){
                semaphore.at(1)->acquire();
                semaphore.at(5)->acquire();
            }
            // Libera R6
            if ( x == 600 && y == 130 ){
                semaphore.at(5)->release();
            }
            // Libera R2
            if ( x == 620 && y == 30 ){
                semaphore.at(1)->release();
            }
        break;
        case 4:
            // Verifica a posição do trem 4
            // Trava o os trilhos R3 e R4
            if ( x == 190 && y == 170 ){
                semaphore.at(2)->acquire();
                semaphore.at(3)->acquire();
            }
            // Libera R3
            if ( x == 350 && y == 150 ){
                semaphore.at(2)->release();
            }
            // Trava o trilho R7
            if ( x == 440 && y == 150 ){
                semaphore.at(6)->acquire();
            }
            // Libera R4
            if ( x == 460 && y == 170 ){
                semaphore.at(3)->release();
            }
            // Libera R7
            if ( x == 440 && y == 270 ){
                semaphore.at(6)->release();
            }
        break;
        case 5:
            // Verifica a posição do trem 5
            // Trava o os trilhos R5, R6 e R7
            if ( x == 480 && y == 270 ){
                semaphore.at(4)->acquire();
                semaphore.at(5)->acquire();
                semaphore.at(6)->acquire();
            }
            // Libera R7
            if ( x == 480 && y == 150 ){
                semaphore.at(6)->release();
            }
            // Libera R5
            if ( x == 620 && y == 150 ){
                semaphore.at(4)->release();
            }
            // Libera R6
            if ( x == 730 && y == 170 ){
                semaphore.at(5)->release();
            }
        break;
    }
}

//Função a ser executada após executar trem->START
void Trem::run(){
    while(true){
        // Atualiza os valores do semáforo
        updateSemaphore();
        // Atualiza a posição dos trens
        updatePosition();
        emit updateGUI(ID, x,y);
        // Dorme 'velocidade' milissegundos
        msleep(velocidade);
    }
}





#include "trem.h"
#include <QtCore>

//Construtor
Trem::Trem(int ID, int x, int y, int startx, int starty, std::vector<QSemaphore*> *semaphore){
    this->ID = ID;
    this->x = x;
    this->y = y;
    this->startx = startx;
    this->starty = starty;
    this->semaphore = semaphore;
    velocidade = 40;

}

// Função criada para atualizar a posição dos trens
// baseados em seu ponto inicial de partida
void Trem::updatePosition(){
    int hLength = 270;
    int vLength = 120;

    if (y == starty && x <startx+hLength)
        x+=10;
    else if (x == startx+hLength && y < starty+vLength)
        y+=10;
    else if (x > startx && y == starty+vLength)
        x-=10;
    else
        y-=10;
}

// Fuçãoq ue define a velocidade

void Trem::setVelocity(int v){
    velocidade = v;
}
int Trem::getX(){
    return this->x;
}
int Trem::getY(){
    return this->y;
}
int Trem::getMolex(){
    return this->semaphore->at(0)->available();
}

void Trem::updateSemaphore(){
    switch(ID){
        case 1:
            if ( x == 320 && y == 30 ){
                semaphore->at(0)->acquire();
            }
            if( x <= 320 && y == 150 ){
                 semaphore->at(0)->release();
                 semaphore->at(2)->acquire();
            }
        break;
        case 2:
            if ( x == 340 && y == 150 ){
                semaphore->at(0)->acquire();
            }
            if ( x == 340 && y == 30 ){
                semaphore->at(0)->release();
            }
        break;
        case 3:
            if ( x == 750 && y == 150 ){
                semaphore->at(1)->acquire();
                semaphore->at(5)->acquire();
            }
            if ( x == 610 && y == 30 ){
                semaphore->at(1)->release();
                semaphore->at(5)->release();
            }
        break;
        case 4:
            if ( x == 190 && y == 140 ){
                semaphore->at(0)->acquire();
                semaphore->at(2)->acquire();
                semaphore->at(3)->acquire();
            }
            if ( x == 460 && y == 160 ){
                semaphore->at(0)->release();
                semaphore->at(2)->release();
                semaphore->at(3)->release();
            }
        break;
        case 5:
            if ( x == 480 && y == 270 ){
                semaphore->at(4)->acquire();
                semaphore->at(5)->acquire();
                semaphore->at(6)->acquire();
            }
            if ( x == 730 && y == 170 ){
                semaphore->at(4)->release();
                semaphore->at(5)->release();
                semaphore->at(6)->release();
            }
        break;
    }
}
// IVAN: Eu modifiquei essa função e retirei o switch case
// caso seja necessário retornar, veja o código fonte fornecido
// pelo Prof.
//
//Função a ser executada após executar trem->START
void Trem::run(){
    while(true){
//        switch (ID) {
//            case 1:
//                updateSemaphore();
//            break;
//            case 2:
//                updateSemaphore();
//            break;

//        }
//        sem_release(&rg);
//        sem_acquire(&rg);
//        sem_acquire(&rg);
//        qDebug() << "teste";
        updateSemaphore();
        updatePosition();
        emit updateGUI(ID, x,y);



        msleep(velocidade);
    }
}





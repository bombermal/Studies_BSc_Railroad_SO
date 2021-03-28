#include "trem.h"
#include <QtCore>

//Construtor
Trem::Trem(int ID, int x, int y, int startx, int starty, std::vector<QSemaphore*> semaphore){
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
    this->velocidade = v;
}
int Trem::getX(){
    return this->x;
}
int Trem::getY(){
    return this->y;
}
int Trem::getSem(int p){
    return this->semaphore.at(p)->available();
}

void Trem::updateSemaphore(){
    switch(ID){
        case 1:
            if ( x == 310 && y == 30 ){
                semaphore.at(0)->acquire();
                semaphore.at(2)->acquire();
            }
            if( x == 310 && y == 150 ){
                semaphore.at(0)->release();
            }
            if( x == 170 && y == 150 ){
                semaphore.at(2)->release();
            }
        break;
        case 2:
            if ( x == 580 && y == 30 ){
                semaphore.at(1)->acquire();
                semaphore.at(4)->acquire();
            }
            if ( x == 480 && y == 150 ){
                if ( semaphore.at(2)->tryAcquire() && semaphore.at(3)->tryAcquire()){
                    semaphore.at(1)->release();
                    semaphore.at(4)->release();

                }
            }
            if ( x == 350 && y == 30 ){
                semaphore.at(2)->release();
                semaphore.at(3)->release();
            }
        break;
        case 3:
            if ( x == 750 && y == 150 ){
                semaphore.at(1)->acquire();
                semaphore.at(5)->acquire();
            }
            if ( x == 600 && y == 130 ){
                semaphore.at(5)->release();
            }
            if ( x == 620 && y == 30 ){
                semaphore.at(1)->release();
            }
        break;
        case 4:
            if ( x == 190 && y == 170 ){
                semaphore.at(2)->acquire();
                semaphore.at(3)->acquire();
                semaphore.at(6)->acquire();
            }
            if ( x == 350 && y == 150 ){
                semaphore.at(2)->release();
            }
            if ( x == 460 && y == 170 ){
                semaphore.at(3)->release();
            }
            if ( x == 440 && y == 270 ){
                semaphore.at(6)->release();
            }
        break;
        case 5:
            if ( x == 480 && y == 270 ){
                semaphore.at(4)->acquire();
                semaphore.at(5)->acquire();
                semaphore.at(6)->acquire();
            }
            if ( x == 480 && y == 150 ){
                semaphore.at(6)->release();
            }
            if ( x == 620 && y == 150 ){
                semaphore.at(4)->release();
            }
            if ( x == 730 && y == 170 ){
                semaphore.at(5)->release();
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
        //verifica
        updateSemaphore();
        //trava

        updatePosition();
        //passa
        //destrava
        //atualiza posção

        emit updateGUI(ID, x,y);



        msleep(velocidade);
    }
}





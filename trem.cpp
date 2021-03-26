#include "trem.h"
#include <QtCore>

//Construtor
Trem::Trem(int ID, int x, int y, int startx, int starty){
    this->ID = ID;
    this->x = x;
    this->y = y;
    this->startx = startx;
    this->starty = starty;
    velocidade = 100;
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


// IVAN: Eu modifiquei essa função e retirei o switch case
// caso seja necessário retornar, veja o código fonte fornecido
// pelo Prof.
//
//Função a ser executada após executar trem->START
void Trem::run(){
    while(true){
        updatePosition();
        emit updateGUI(ID, x,y);
        msleep(velocidade);
    }
}





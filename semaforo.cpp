#include "semaforo.h"


Semaforo::Semaforo(int sID, sem_t mutex){
    this->sID = sID;
    this->mutex = mutex;

    sem_init(&this->mutex , 0, 1);
}

Semaforo::~Semaforo(){
  sem_destroy(&mutex);
}

int Semaforo::getID(){
    return this->sID;
}

void Semaforo::wait(){
    sem_wait(&this->mutex);
}

void Semaforo::post(){
    sem_post(&this->mutex);
}
int Semaforo::getMutex(){
    int value;
    return sem_getvalue(&this->mutex, &value);
}

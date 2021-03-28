#ifndef SEMAFORO_H
#define SEMAFORO_H

#include <semaphore.h>

class Semaforo{

public:

  Semaforo(int, sem_t);
  ~Semaforo();
  void wait();
  void post();
  int getID();
  int getMutex();

private:
  int sID;
  sem_t mutex;

};

#endif // SEMAFORO_H

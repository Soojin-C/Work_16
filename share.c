#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main(){
  key_t key;
  int shmid;
  char * data;

  key = ftok("./", 'R');
  shmid = shmget(key, sizeof(char) * 200, 0666 | IPC_CREAT);

  data = shmat(shmid, (void *)0, 0);

  return 0;
}

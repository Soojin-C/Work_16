#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <string.h>

int main(){
  key_t key;
  int shmid;
  char * data;
  char input[200];

  key = ftok("share.c", 'R');
  shmid = shmget(key, 200, 0644 | IPC_CREAT);

  data = shmat(shmid, (void *)0, 0);

  if (data[0] == 0){
    printf("Current: New\n" );
  }
  else{
    printf("Current: [%s]\n", data);
  }

  printf("Do you want to change the current string?[ yes | no ]:\n" );
  fgets(input, 200, stdin);

  if (strcmp(input, "y\n") == 0){
    printf("Enter new string: \n");
    fgets(input, 200, stdin);
    int counter = 0;
    while (counter < 200){
      if (strcmp(&input[counter], "\n") == 0){
        input[counter] = 0;
      }
      counter ++;
    }
    strncpy(data, input, 200);
  }

  printf("Do you want to delete the current string?[ yes | no ]:\n" );
  fgets(input, 200, stdin);

  if (strcmp(input, "y\n") == 0){
    shmdt(data);
    shmctl(shmid, IPC_RMID, NULL);
  }

  return 0;
}

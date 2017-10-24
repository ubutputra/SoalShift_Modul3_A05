#include <string.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define LOHAN 1
#define KEPITING 2
pthread_t threadID[3];

void* Degrade(void* arg);
void* DeadCheck(void* arg);
int main(int argc, char *argv[]) {
    int lohan[] = {LOHAN,10,15};
    int kepiting[] = {KEPITING,10,15};
    pthread_create(&threadID[KEPITING],NULL,&Degrade,lohan);
    pthread_create(&threadID[LOHAN],NULL,&Degrade,kepiting);
    pthread_create(&threadID[0],NULL,&DeadCheck,NULL);
    pthread_join(threadID[KEPITING],NULL);
    pthread_join(threadID[LOHAN],NULL);
    pthread_join(threadID[0],NULL); 
    return 0;
}

void* Degrade(void* arg){
   
}

void* DeadCheck(void* arg){
   
}

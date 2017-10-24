#include <string.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define LOHAN 1
#define KEPITING 2
pthread_t threadID[3];
int status[3]={0,100,100};
void* Degrade(void* arg);
void* DeadCheck(void* arg);
int main(int argc, char *argv[]) {
    int lohan[] = {LOHAN,10,15};
    int kepiting[] = {KEPITING,20,10};
    pthread_create(&threadID[KEPITING],NULL,&Degrade,lohan);
    pthread_create(&threadID[LOHAN],NULL,&Degrade,kepiting);
    pthread_create(&threadID[0],NULL,&DeadCheck,NULL);
    char hewan[10];
    while(1){
        scanf("%s",hewan);
        
        if(strcmp(hewan,"lohan")==0){
            status[LOHAN]+=10;
            printf("Memberi makan lohan, status lohan %d\n",status[LOHAN]);
        }else if(strcmp(hewan,"kepiting")==0){
            status[KEPITING]+=10;
            printf("Memberi makan kepiting, status kepiting %d\n",status[KEPITING]);
        }else{
            printf("Input Tidak Valid\n");
        }
    }
    
    pthread_join(threadID[KEPITING],NULL);
    pthread_join(threadID[LOHAN],NULL);
    pthread_join(threadID[0],NULL); 
    return 0;
}

void* Degrade(void* arg){
   
}

void* DeadCheck(void* arg){
   
}

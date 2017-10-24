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
    int *data=(int*)arg;
    while(1){
        sleep(data[1]);
        status[data[0]]-=data[2];
        printf("Status : Lohan %d , Status Kepiting %d\n",status[LOHAN],status[KEPITING]);
    }
}

void* DeadCheck(void* arg){
    while(1){
        if(status[LOHAN]<=0){
            printf("Lohan telah mati\n");
            exit(EXIT_SUCCESS);
        }else if(status[LOHAN]>100){
            printf("Lohan telah meledak\n");
            exit(EXIT_SUCCESS);
        }
        if(status[KEPITING]<=0){
            printf("Kepiting telah mati\n");
            exit(EXIT_SUCCESS);
        }else if(status[KEPITING]>100){
            printf("Kepiting telah meledak\n");
            exit(EXIT_SUCCESS);
        }
       
        sleep(1);
    }
}

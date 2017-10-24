#include <string.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define PLAYER1 0
#define PLAYER2 1


int score[2]={0,0};
char mineLoc[2][17];
pthread_t threadID[2];
pthread_mutex_t lock;
int turn=0;
int usedLoc[2]={0,0};
void* PlayerTurn(void *arg);

int main(int argc, char *argv[]) {
    char Nama[2][100];
    int positionFirst=0,positionSecond=1;
    for(int i=1;i<=16;i++){
        mineLoc[PLAYER1][i]=0;
        mineLoc[PLAYER2][i]=0;
    }
    pthread_mutex_init(&lock,NULL);
    printf("Masukkan nama Player 1 : ");
    scanf("%[^\n]%*c",Nama[PLAYER1]);
    void* parameterFirst[]={Nama[PLAYER1],&positionFirst};
    printf("Masukkan nama Player 2 : ");
    scanf("%[^\n]%*c",Nama[PLAYER2]);
    void* parameterSecond[]={Nama[PLAYER2],&positionSecond};
    pthread_create(&threadID[PLAYER1],NULL,&PlayerTurn,parameterFirst);
    pthread_create(&threadID[PLAYER1],NULL,&PlayerTurn,parameterSecond);
    pthread_join(threadID[PLAYER1]);
    pthread_join(threadID[PLAYER2]);
    pthread_mutex_destroy(&lock);
    return 0;
}

void* PlayerTurn(void *arg){
    
}


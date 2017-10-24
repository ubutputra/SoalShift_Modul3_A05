#include <string.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define PLAYER1 0
#define PLAYER2 1

struct Param{
    char *Nama;
    int Player;
};
int score[2]={0,0};
char mineLoc[2][17];
pthread_t threadID[2];
pthread_mutex_t lock;
int turn=0;
int usedLoc[2]={0,0};
void* PlayerTurn(void *arg);

int main(int argc, char *argv[]) {
    char Nama[2][100];
    for(int i=1;i<=16;i++){
        mineLoc[PLAYER1][i]=0;
        mineLoc[PLAYER2][i]=0;
    }
    pthread_mutex_init(&lock,NULL);
    printf("Masukkan nama Player 1 : ");
    scanf("%[^\n]%*c",Nama[PLAYER1]);
    struct Param Param1;
    Param1.Nama = Nama[PLAYER1];
    Param1.Player = PLAYER1;
    printf("Masukkan nama Player 2 : ");
    scanf("%[^\n]%*c",Nama[PLAYER2]);
    struct Param Param2;
    Param2.Nama = Nama[PLAYER2];
    Param2.Player = PLAYER2;
    pthread_create(&threadID[PLAYER1],NULL,&PlayerTurn,&Param1);
    pthread_create(&threadID[PLAYER1],NULL,&PlayerTurn,&Param2);
    pthread_join(threadID[PLAYER1],NULL);
    pthread_join(threadID[PLAYER2],NULL);
    pthread_mutex_destroy(&lock);
    return 0;
}

void* PlayerTurn(void *arg){
    char* Nama = ((struct Param*)arg)->Nama;
    int Player= ((struct Param*)arg)->Player;
    int inputs;
    while(1){
        pthread_mutex_lock(&lock);
        printf("Score saat ini :\nPlayer 1 = %d, Player 2 = %d\n",score[PLAYER1],score[PLAYER2]);
        printf("Turn ke - %d. Giliran %s\n",++turn,Nama);
        for(int i=1;i<=4;i++){
            printf("Lokasi ranjau ke %d : ",i);
            scanf("%d",&inputs);
            if(mineLoc[inputs]==0){
                usedLoc[Player]++;
            }
            mineLoc[Player][inputs] = 1;
        }
        if(turn>1){
            printf("Waktunya %s memilih tempat tanpa ranjau!\n",Nama);
            for(int i=1;i<=4;i++){
                printf("Masukkan lokasi percobaan ke %d :",i);
                scanf("%d",&inputs);
                if(mineLoc[Player^1][inputs]){
                    score[Player^1]++;
                    printf("BOOM!!!!!111!!!!1!\n");
                }else{
                    score[Player]++;
                    printf("YAYY!!!\n");
                }
                if(score[Player^1]>=10){
                    printf("Permainan telah berakhir dengan skor Player 1 : %d dan Player 2 : %d\n",score[PLAYER1],score[PLAYER2]);
                    exit(EXIT_SUCCESS);
                }
            }
        }
        
        if(usedLoc[PLAYER1]>=16&&usedLoc[PLAYER2]>=16){
            printf("PAPAN PENUH!\n");
            if(score[PLAYER1]>score[PLAYER2]){
                printf("Player 1 menang!\n");
            }else if(score[PLAYER1]<score[PLAYER2]){
                printf("Player 2 menang!\n");
            }else{
                printf("Hasil Seri!\n");
            }
            printf("Score Akhir Player 1 : %d , Player 2 : %d\n",score[PLAYER1],score[PLAYER2]);
            exit(EXIT_SUCCESS);
        }
        pthread_mutex_unlock(&lock);
        sleep(1);
    }
}


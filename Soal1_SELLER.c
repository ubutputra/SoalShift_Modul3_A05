#include <string.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
struct WeaponData{
    int count;
    char Name[10];
};
int main(int argc, char *argv[]) {
    key_t key = 1234;
    struct WeaponData* data;
    int shmid = shmget(key,sizeof(struct WeaponData)*6,IPC_CREAT | 0666);
    data = (struct WeaponData*)shmat(shmid, NULL, 0);
    char Query[100];
    int amount;
    strcpy(data[0].Name,"M4A1");
    strcpy(data[1].Name,"PM2-V1");
    strcpy(data[2].Name,"SPR-3");
    strcpy(data[3].Name,"SS2-V5");
    strcpy(data[4].Name,"SPG1-V3");
    strcpy(data[5].Name,"MINE");
    for(int i=0;i<6;i++){
        data[i].count=0;
    }
    while(1){
        printf("Avaiable Query, \"BROWSE\" and \"ADD\"\n");
        scanf("%s",Query);
        if(strcmp(Query,"BROWSE")==0){
            for(int i=0;i<6;i++){
                if(data[i].count>0){
                    printf("%s %d\n",data[i].Name,data[i].count);
                }
            }
        }else if(strcmp(Query,"ADD")==0){
            scanf("%s %d",Query,&amount);
            for(int i=0;i<=6;i++){
                if(i==6){
                    printf("INVALID INPUT\n");
                    break;
                }else if(strcmp(data[i].Name,Query)==0){
                    data[i].count+=amount;
                    printf("Weapon %s has been increased to %d\n",data[i].Name,data[i].count);
                    break;
                }
                
            }
        }
        
    }
    shmdt(data);
    shmctl(shmid, IPC_RMID, NULL);
    return 0;
}



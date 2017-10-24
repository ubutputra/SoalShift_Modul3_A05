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
    
    while(1){
        printf("Avaiable Query, \"BROWSE\" and \"BUY\"\n");
        scanf("%s",Query);
        if(strcmp(Query,"BROWSE")==0){
            for(int i=0;i<6;i++){
                if(data[i].count>0){
                    printf("%s %d\n",data[i].Name,data[i].count);
                }
            }
        }else if(strcmp(Query,"BUY")==0){
            scanf("%s %d",Query,&amount);
            for(int i=0;i<=6;i++){
                if(i==6){
                    printf("INVALID INPUT\n");
                    break;
                }else if(strcmp(data[i].Name,Query)==0){
                    if(data[i].count>=amount){
                        data[i].count-=amount;
                        printf("Weapon %s has been Bought %d Units!\n",data[i].Name,amount);
                        
                    }else{
                        printf("Not Enough Stock!\n");
                    }
                    break;
                }
                
            }
        }
        
    }
    shmdt(data);
    shmctl(shmid, IPC_RMID, NULL);
    return 0;
}



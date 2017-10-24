#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
 


 
int main(void)
{

    pthread_create(&(tid1), NULL, &, NULL);
    pthread_create(&(tid2), NULL, &, NULL);
 
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
 
    return 0;
}

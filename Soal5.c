
#include <string.h>
#include <pthread.h>
#include <cstdlib>
#include <stdio.h>
char globalIterator[1001];
char EndOfFile = 0;
int FinishedThread=0,avaiableThread=0;
void* StringCounter(void* arg);
pthread_mutex_t lock;
int main(int argc, char* argv[]) {
    pthread_mutex_init(&lock,NULL);
    avaiableThread = argc;
    for(int i=0;i<argc;i++){
        
    }
    pthread_mutex_destroy(&lock);
    return 0;
}

void* StringCounter(void* arg){
    char* subString = (char*)arg;
    int subLength = strlen(subString);
    int count = 0;
    while(!EndOfFile){
        char* iterator = globalIterator;
        while(iterator = strstr(iterator,subString)){
            iterator+= subLength;
            count++;
        }
        FinishedThread++;
        while(FinishedThread<avaiableThread){
            //Do Nothing...
        }
    }
    
    printf("%s : %d\n",subString,count);
    
}



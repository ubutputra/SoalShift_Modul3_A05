
#include <string.h>
#include <pthread.h>
#include <stdio.h>

char globalIterator[1500];
pthread_t threadID[101];

void* StringCounter(void* arg);

int main(int argc, char* argv[]) {
    FILE* source = fopen("Novel.txt","r");
    fscanf(source,"%[^\n]%*c",globalIterator);
    for(int i=1;i<argc;i++){
        pthread_create(&threadID[i],NULL,&StringCounter,argv[i]);
    }
    for(int i=1;i<argc;i++){
        pthread_join(threadID[i],NULL);
    }
    fclose(source);
    return 0;
}

void* StringCounter(void* arg){
    char* subString = (char*)arg;
    int subLength = strlen(subString);
    int count = 0;
    
    char* iterator = globalIterator;
    while(iterator = strstr(iterator,subString)){
        iterator+= subLength;
        count++;
    }

    printf("%s : %d\n",subString,count);
    
}



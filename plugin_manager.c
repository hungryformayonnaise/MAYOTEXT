#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>

char ** pluginsFind(int *amount) {
    struct dirent *dp;
    DIR *dfd;
    if((dfd=opendir("plugins"))==NULL) {
        printf("Can't open directory");
        return NULL;
    }
    (*amount)=0;
    while((dp=readdir(dfd))!=NULL) {
        (*amount)++;
    }
    closedir(dfd);
    char ** array;
    int i=0;
    array=(char**)malloc((*amount)*sizeof(char*));
    for(int j = 0; j < *amount; j++)
        array[j] = (char*)malloc(300* sizeof(char));

    if((dfd=opendir("plugins"))==NULL) {
        printf("Can't open directory");
        return NULL;
    }
    while((dp=readdir(dfd))!=NULL) {
        sprintf(array[i++], "plugins/%s", dp->d_name);
    }
    closedir(dfd);
    free(dp);
    return array;
}

void arrFree(char *** arr, size_t size) {
    for(int i=0;i<size;i++) {
        free((*arr)[i]);
    }
    free((*arr));
}

int main() {
    char ** arr;
    int amount=0;
    arr=pluginsFind(&amount);
    for(int i=0;i<amount;i++) {
        printf("%s\n", arr[i]);
    }
    arrFree(&arr, amount);
    return 0;
}

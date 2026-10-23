#include <stdio.h>

void printStrings(char* arr[], int size){
    for(int i=0;i<size;i++){
        printf("i: %d, String: %s", i,arr[i]);
    }
}

int main(){

    char* programmingLanguages[] = {
        "C languge",
        "Java language",
        "Rust language"
    };

    int sizeOfCharPointerArray = sizeof(programmingLanguages)/sizeof(char*);

    printStrings(programmingLanguages,sizeOfCharPointerArray);
    printf(programmingLanguages);
    return 0;
}
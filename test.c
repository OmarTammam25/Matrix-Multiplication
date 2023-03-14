#include <stdio.h>
#include <stdlib.h>  
#include <string.h>

int main(){
    
    char* str = (char* )malloc(100 * sizeof(char));
    str = "hello";
    char* str2 = "concat";
    strcat(str, str2);
    printf("%s", str);
}
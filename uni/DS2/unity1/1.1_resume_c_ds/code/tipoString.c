#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "tipoString.h"

struct string { 
    char string[100];
    int comprimento;
    };    

tString CriaString(const char *str){
    tString novaString = malloc(sizeof(struct string));

    if (!novaString){
        return NULL;
    }

    novaString->comprimento = -1;
    strcpy(novaString->string, str);
    novaString->comprimento = strlen(str);

    return novaString;
}

void DestroiString(tString *c){
    free(*c);
    *c = NULL;
}

tString ConcatenaStrings(tString str1, tString str2){
    tString novaString = CriaString("");
    novaString->comprimento = -1; //para indicar que n foi copiada corretamente

    if (ComprimentoString(str1) + ComprimentoString(str2) > 100){
        return novaString;
    } 

    int j = 0;
    for(int i = 0; i < ComprimentoString(str1); i++){
        novaString->string[j++] = str1->string[i];
    }
    for(int i = 0; i < ComprimentoString(str2); i++){
        novaString->string[j++] = str2->string[i];
    }
    novaString->comprimento = ComprimentoString(str1) + ComprimentoString(str2);
    novaString->string[novaString->comprimento] = '.'; 

    return novaString;
}

void ExibeString(tString str){
    for (int i = 0; i < str->comprimento; i++){
        printf("%c%c", str->string[i], (i == str->comprimento-1 ? '\n' : '\0'));
    }
}

int ComprimentoString(tString str){
    return str->comprimento;
}

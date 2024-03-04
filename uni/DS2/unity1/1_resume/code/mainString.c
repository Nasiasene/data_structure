#include <stdio.h>
#include "tipoString.h"

int main(void) {
    tString umaString, outraString;

    umaString = CriaString("cafe");
    ExibeString(umaString);
    printf("comprimento: %d\n", ComprimentoString(umaString));

    outraString = CriaString("Amargo");
    ExibeString(ConcatenaStrings(umaString, outraString));
    printf("comprimento: %d\n", ComprimentoString(ConcatenaStrings(umaString, outraString)));

    DestroiString(&umaString);
    DestroiString(&outraString);
    
    return 0;
}
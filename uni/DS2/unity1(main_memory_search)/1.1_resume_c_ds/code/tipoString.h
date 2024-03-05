#ifndef _TipoString2_H_
#define _TipoString2_H_

typedef struct string *tString; //tipo incompleto

extern tString CriaString(const char *str);
extern void DestroiString(tString *c);
extern tString ConcatenaStrings(tString str1, tString str2);
extern void ExibeString(tString str);
extern int ComprimentoString(tString str);

#endif
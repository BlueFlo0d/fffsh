#include <string.h>
typedef struct FffArray_{
        size_t len;
        size_t size;
        struct FffArray_ *objRingNext; // Put all array into a ring linklist
        // To allow resource reclamation when malloc fails
        struct FffArray_ *objRingPrev;
        char *content;
} FffArray;
void fffArrayExpand(FffArray *arr, size_t deltaLen);
void fffArrayPush(FffArray *arr, char *string, size_t len);
void fffArrayPushOne(FffArray *arr, char achar);
void fffArrayInit(FffArray *arr);
void fffArrayDestroy(FffArray *arr);
char *fffArrayDumpString(FffArray *arr);

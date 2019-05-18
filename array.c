#include "array.h"
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <limits.h>
#define MEM_EXPAND_SIZE 1024
#define NUCLEAR_CRISIS_CHECK(msg) if(errno!=ENOMEM){\
                perror("Hugh? I'm an innocent array, my "msg" return me NULL, but errno tells me something else"); \
                abort();\
        }
#define ALIEN_CRISIS(msg) fprintf(stderr,"Alien invasion warning. (which means the size of one array is overflowing while trying "msg")\n"); \
        abort();
void reclaim_mem(FffArray *arr){
        FffArray *currentArr = arr->objRingNext;
        while(currentArr != arr){
                currentArr->size = currentArr->len;
                char *newcontent = realloc(currentArr->content, currentArr->size);
                if(!newcontent){
                        NUCLEAR_CRISIS_CHECK("realloc");
                }
                else{
                        currentArr->content = newcontent;
                }
                currentArr = arr->objRingNext;
        }
}
// When you look at this, you are wondering: why make it a macro? why not an inline function?
// I'm using clang 6.0.1 when writing this.
// If I write a inline function, probably clang's constant propogation fails or some other weird things happen, and the performance drop by around 1/3.
#define expand(arr,len_) do {\
                size_t len = (len_);            \
        if(SIZE_T_MAX - arr->len < len){\
                ALIEN_CRISIS("realloc");\
        }\
        arr->len += len;\
        if(arr->len > arr->size){\
                size_t sectors = (arr->len/MEM_EXPAND_SIZE+1);\
                if(sectors > SIZE_T_MAX/MEM_EXPAND_SIZE){\
                        /* Integer overflow, address space is being exhausted   */ \
                        arr->size = arr->len;\
                }\
                else{\
                        arr->size = sectors*MEM_EXPAND_SIZE;\
                }\
                char *newcontent = realloc(arr->content, arr->size);\
                if(!newcontent){\
                        NUCLEAR_CRISIS_CHECK("realloc");\
                        /* Try smaller size*/           \
                        arr->size = arr->len;\
                        newcontent = realloc(arr->content, arr->size);\
                        if(!newcontent){\
                                NUCLEAR_CRISIS_CHECK("realloc");\
                                /* Do reclamation and retry     */  \
                                reclaim_mem(arr);\
                                newcontent = realloc(arr->content, arr->size);\
                                if(!newcontent){\
                                        NUCLEAR_CRISIS_CHECK("realloc");\
                                        /* That's all we can do, give up. */ \
                                        perror("Memory exhausted during array expansion");             \
                                        abort();\
                                }\
                        }\
                }\
                arr->content = newcontent;\
                errno = 0;\
        }\
         }while(0)
void fffArrayPush(FffArray *arr, char *string, size_t len_){
        size_t position = arr->len;
        expand(arr, len_); // len_ : Get rid of the non hygiene macro problem
        memcpy(arr->content + position, string, len_);
}
void fffArrayPushOne(FffArray *arr, char achar){
        size_t position = arr->len;
        expand(arr,1);
        *(arr->content+position)=achar;
}
FffArray *rootObj = NULL;
FffArray *headObj = NULL;
void reinitMem(FffArray *arr){
        arr->len = 0;
        arr->size = MEM_EXPAND_SIZE;
        char *newcontent = malloc(arr->size);
        if(!newcontent){
                NUCLEAR_CRISIS_CHECK("malloc");
                // Try no alloc
                // Lazy alloc on first push
                // Make use of realloc(NULL,_)=malloc(_)
                arr->size = 0;
                arr->content = NULL;
        }
        else{
                arr->content = newcontent;
        }
}
void fffArrayInit(FffArray *arr){
        if(!rootObj){
                rootObj = arr;
                headObj = arr;
                arr->objRingNext = arr;
                arr->objRingPrev = arr;
        }
        else{
                arr->objRingNext = rootObj;
                arr->objRingPrev = headObj;
                headObj->objRingNext = arr;
                headObj = arr;
        }
        reinitMem(arr);
}
void fffArrayDestroy(FffArray *arr){
        if(arr->objRingNext == arr){
                rootObj = NULL;
                headObj = NULL;
        }
        else{
                arr->objRingNext->objRingPrev = arr->objRingPrev;
                arr->objRingPrev->objRingNext = arr->objRingNext;
        }
        if(arr->size){
                free(arr->content);
        }
}
char *fffArrayDumpString(FffArray *arr){
        size_t position = arr->len;
        expand(arr, 1);
        arr->content[position]='\0';
        char *ret = arr->content;
        arr->len = 0;
        reinitMem(arr);
        return ret;
}

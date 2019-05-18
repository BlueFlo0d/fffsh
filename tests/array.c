#include "../array.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
int main(int argc,char **argv){
        long long counts = 10000;
        if(argc > 1){
                counts = strtoll(argv[1], NULL, 10);
                if(errno == EINVAL){
                        fprintf(stderr, "Illegal argument, using default value %lld\n", counts);
                }
        }
        FffArray testArr;
        long long sum=0;
        fffArrayInit(&testArr);
        for(long long i=0;i<counts;i++){
                fffArrayPushOne(&testArr, i);
                sum+=testArr.content[i];
        }
        printf("Result: %lld\n", sum);
        fffArrayDestroy(&testArr);
        return 0;
}

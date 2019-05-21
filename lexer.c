#include <stdio.h>
#include <assert.h>
#include "lexer.h"
#include "array.h"

#define MLISTMAP_FUNC(x) "("#x")",
const char * const tokenPrintNames[] = {MLISTMAP(TOKEN_LIST)};
#undef MLISTMAP_FUNC

#define MLISTMAP_APPLIED(x,y) "(Operator)"#y,
#define MLISTMAP_FUNC(x) MLISTMAP_APPLIED x
const char * const tokenOperatorPrintNames[] = {MLISTMAP(TOKEN_OPERATOR_LIST)};
#undef MLISTMAP_FUNC
#undef MLISTMAP_APPLIED

#define MLISTMAP_FUNC(x) "(ReservedWord)"#x,
const char * const tokenReservePrintNames[] = {MLISTMAP(TOKEN_RESERVE_LIST)};
#undef MLISTMAP_FUNC

#define MLISTMAP_APPLIED(x,y) "(ReservedWord)"#y,
#define MLISTMAP_FUNC(x) MLISTMAP_APPLIED x
const char * const tokenConditionalReserveNames[] = {MLISTMAP(TOKEN_CONDITIONAL_RESERVE_LIST)};
#undef MLISTMAP_FUNC
#undef MLISTMAP_APPLIED

int indexInNameList(FffToken *tk){
        assert((tk->type ^ TOKEN_CATEGORY_MASK) > 0);
        return (tk->type ^ TOKEN_CATEGORY_MASK) - 1;
}
int faithfulPrintIt(FffToken *tk, const char * const list[],FILE *output){
        return fputs(list[indexInNameList(tk)], output);
}
int fprintToken(FILE *output,FffToken *tk){

#define CHECK_FPUTS_RET(ret) if(countDelta < 0)\
        return ret

        int count = 0;
        int countDelta;
        switch(tk->type & TOKEN_CATEGORY_MASK){
        case 0: // Just a word
                countDelta = fputs(tokenPrintNames[indexInNameList(tk)], output);
                CHECK_FPUTS_RET(countDelta);
                count += countDelta;
                countDelta = fputs(tk->content, output);
                CHECK_FPUTS_RET(countDelta);
                count += countDelta;
                break;
        case TOKEN_OPERATOR_FLAG:
                return faithfulPrintIt(tk, tokenOperatorPrintNames, output);
        case TOKEN_RESERVE_FLAG:
                return faithfulPrintIt(tk, tokenReservePrintNames, output);
        case TOKEN_CONDITIONAL_RESERVE_FLAG:
                return faithfulPrintIt(tk, tokenConditionalReserveNames, output);
        }
        return count;
}
int fffTokenize(FILE *input, FffToken **tokenList){
        FffArray lineBuf;
        fffArrayInit(&lineBuf);
        fffArrayDestroy(&lineBuf);
        return 0;
}

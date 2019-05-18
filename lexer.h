#include "macro_magic.h"
#define TOKEN_LIST (Word)\
        (AssignmentWord)\
                (Name)\
                (NewLine)\
                (IoNumber)\
                (LIST_END)
#define TOKEN_OPERATOR_LIST (AndIf,&&)\
        (OrIf,||)\
                (DSemi,;;)\
                (DLess,<<)\
                (DGreat,>>)\
                (DLessAnd,<&)\
                (DGreatAnd,>&)\
                (DLessGreat,<>)\
                (DLessDash,<<-)\
                (Clobber,>|)   \
                (LIST_END)
#define TOKEN_RESERVE_LIST (if)\
        (then)\
        (else)\
        (elif)\
        (fi)\
        (do)\
        (done)\
        (case)\
        (esac)\
        (while)\
        (until)\
        (for)                                   \
        (LIST_END)
#define TOKEN_CONDITIONAL_RESERVE_LIST (Lbrace,{)\
                                        (Rbrace,})\
        (Bang,!)\
                (In,in)\
                (LIST_END)
typedef enum fffTokenType_{
#define MLISTMAP_FUNC(x) CAT(t,x),
        MLISTMAP(TOKEN_LIST)
} fffTokenType;
typedef struct FffToken_ {
        int type;
        struct FffToken_ *next;
        char *content;
} FffToken;

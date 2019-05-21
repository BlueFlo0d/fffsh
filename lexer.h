#include "macro_magic.h"
#define TOKEN_LIST (Word)\
        (AssignmentWord)\
                (Name)\
                (NewLine)\
                (IoNumber)\
                (LIST_END)
#define TOKEN_OPERATOR_LIST ((AndIf,&&))        \
        ((OrIf,||))                             \
        ((DSemi,;;))                            \
        ((DLess,<<))                            \
        ((DGreat,>>))                           \
        ((DLessAnd,<&))                         \
        ((DGreatAnd,>&))                        \
        ((DLessGreat,<>))                       \
        ((DLessDash,<<-))                       \
        ((Clobber,>|))                          \
        ((LBracket,"("))\
         ((RBracket,")"))\
        ((And,&))                                \
        ((Less,<))                                \
        ((Greater,>))                                \
        ((Semi,;))                                   \
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
#define TOKEN_CONDITIONAL_RESERVE_LIST ((Lbrace,{)) \
                                        ((Rbrace,}))    \
        ((Bang,!))                                      \
        ((In,in))                                       \
                (LIST_END)
// Enum must fit into a char/int/uint type, and int is at least 16-bit wide
#define TOKEN_CATEGORY_MASK 0xF000 // Use highest 4 bit to store category information
#define TOKEN_OPERATOR_FLAG 0x1000
#define TOKEN_RESERVE_FLAG 0x2000
#define TOKEN_CONDITIONAL_RESERVE_FLAG 0x4000
typedef enum fffTokenType_{
        tDummy = 0,
#define MLISTMAP_FUNC(x) CAT(t,x),
        MLISTMAP(TOKEN_LIST)
#undef MLISTMAP_FUNC

        tDummyOperator = TOKEN_OPERATOR_FLAG,
#define MLISTMAP_APPLIED(x,y) CAT(t,x),
#define MLISTMAP_FUNC(x) MLISTMAP_APPLIED x
        MLISTMAP(TOKEN_OPERATOR_LIST)
#undef MLISTMAP_FUNC
#undef MLISTMAP_APPLIED

        tDummyReserve = TOKEN_RESERVE_FLAG,
#define MLISTMAP_FUNC(x) CAT(t,x),
        MLISTMAP(TOKEN_RESERVE_LIST)
#undef MLISTMAP_FUNC

        tDummyConditionalReserve = TOKEN_CONDITIONAL_RESERVE_FLAG,
#define MLISTMAP_APPLIED(x,y) CAT(t,x),
#define MLISTMAP_FUNC(x) MLISTMAP_APPLIED x
        MLISTMAP(TOKEN_CONDITIONAL_RESERVE_LIST)
#undef MLISTMAP_FUNC
#undef MLISTMAP_APPLIED
} fffTokenType;
struct FffTokenSegment_;
typedef struct FffToken_ {
        int type;
        struct FffToken_ *next;
        struct FffTokemSegment *content;
} FffToken;

typedef struct FffTokenParameterExpansion_ {
        int type;
        struct FffToken_ *content;
        struct FffToken_ *substition;
} FffTokenParameterExpansion;

typedef struct FffTokenSegment_ {
        int type;
        struct FffTokenSegment *next;
        char *content;
} FffTokenSegment;

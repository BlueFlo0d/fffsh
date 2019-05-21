// This is some evil macros.
// Just no need for a codegen I think, which is also evil.
// I'll write good document though.
// (If I were younger I would say: Those code are self explanatory! RTFS!)

// Concatenate
#define CAT_(x,y) x##y
#define CAT(x,y) CAT_(x,y)

// Macro List Map
#define MLISTMAP___X(MLISTMAP_num,MLISTMAP_k,...) MLISTMAP_k(MLISTMAP_FUNC(MLISTMAP_num) MLISTMAP_Y)
#define MLISTMAP___Y(MLISTMAP_num,MLISTMAP_k,...) MLISTMAP_k(MLISTMAP_FUNC(MLISTMAP_num) MLISTMAP_X)
#define MLISTMAP_X(MLISTMAP_num,...) MLISTMAP___X(MLISTMAP_num __VA_ARGS__,IDENTITY)
#define MLISTMAP(x) MLISTMAP_X x
#define MLISTMAP_Y(MLISTMAP_num,...) MLISTMAP___Y(MLISTMAP_num __VA_ARGS__,IDENTITY)
#define IDENTITY(...) __VA_ARGS__
#define TERMINAL(...)

#define LIST_END IDENTITY TERMINAL() (IDENTITY(TERMINAL,TERMINAL))

// Example Usage:
// #define MY_LIST (x)(y)(z)(LIST_END) // Make a list by enclosing each element in brackets. End with LIST_END
// #define MLISTMAP_FUNC(x) x, // Define the function that you want to apply to each element
// MLISTMAP(MY_LIST) //  ---Expand to---> x, y, z,

// Some more: Multiple arguments
// #define MY_LIST ((x,1))((y,2))((z,3))(LIST_END)
// #define MLISTMAP_APPLIED(x,y) x, // The actual funtion
// #define MLISTMAP_FUNC(x) MLISTMAP_APPLIED x // Strip a layer of brackets
// MLISTMAP(MY_LIST)  ---Expand to---> x, y, z,

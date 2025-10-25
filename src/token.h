typedef enum {
    TOKEN_NUMERO,
    TOKEN_OPERADOR,
    TOKEN_PARENTESE
} TipoToken;

typedef struct {
    TipoToken tipo;
    char* valor;
} Token;
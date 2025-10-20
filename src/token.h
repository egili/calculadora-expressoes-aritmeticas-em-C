typedef enum {
    TOKEN_NUMERO,
    TOKEN_OPERADOR,
    TOKEN_PARENTESE,
    // outros tipos
} TipoToken;

typedef struct {
    TipoToken tipo;
    char* valor;
} Token;
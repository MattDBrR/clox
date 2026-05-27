#include <stdio.h>

typedef enum{
   INTERPRET_OK
} InterpretResult;

typedef enum{
    TYPE_1,
    TOKEN_EOF
} TokenType;

typedef struct {
    const char* start;
    const char* current;
    int line;
} Scanner;

// Global instance of scanner
Scanner scanner;

InterpretResult interpret(const char* source){
    compile(source);
    return INTERPRET_OK;
}

void compile(const char* source){
    initScanner(source);
    int line = -1;
    // Infinite loop
    for(;;) {
        Token token = scanToken();
        if (token.line != line) {
            printf("%4d ", token.line);
        } else {
            printf("   | ");
        }
        printf'"%2d '%.*s'\n", token.type , token.length, token.start);
        if (token.type == TOKEN_EOF ) break;
    }
}

void initScanner(const char* source){
    scanner.start = source;
    scanner.current = source;
    scanner.line = 1;
}

typedef struct{
    TokenType token;
    const char* star;
    int length;
    int line;
} Token;

// Imply that each call we are the start of a new token
Token scanToken(){
    skipWhiteSpace();
    scanner.start = scanner.current;
    if (isAtEnd()) return makeToken(TOKEN_EOF);
    char c = advance(); // return current char by the scanner and move
    // To the next char
    if (isDigit(c)) return number();
    if (isAlpha(c)) return identifier();
    switch (c) {
        case '(': return makeToken(TOKEN_LEFT_PAREN);
        case ')': return makeToken(TOKEN_RIGHT_PAREN);
        case '{': return makeToken(TOKEN_LEFT_BRACE);
        case '}': return makeToken(TOKEN_RIGHT_BRACE);
        case ';': return makeToken(TOKEN_SEMICOLON);
        case ',': return makeToken(TOKEN_COMMA);
        case '.': return makeToken(TOKEN_DOT);
        case '-': return makeToken(TOKEN_MINUS);
        case '+': return makeToken(TOKEN_PLUS);
        case '/': return makeToken(TOKEN_SLASH);
        case '*': return makeToken(TOKEN_STAR);
        case '!':
            return makeToken(match('=') ? TOKEN_BANG_EQUAL : TOKEN_BANG);
        case '=':
            return makeToken(
                match('=') ? TOKEN_EQUAL_EQUAL : TOKEN_EQUAL);
        case '<':
            return makeToken(
                match('=') ? TOKEN_LESS_EQUAL : TOKEN_LESS);
        case '>':
            return makeToken(
                match('=') ? TOKEN_GREATER_EQUAL : TOKEN_GREATER);
        case '"': return string();
    }
    return errorToken("Unexpected character.");
}

// The source string is a good null-terminated C string
static bool isAtEnd(){
    return  *scanner.current == '\0';
}

static char advance(){
    scanner.current++;
    return scanner.current[-1];
}

static bool match(char expected){
    if (isAtEnd()) return false;
    if (*scanner.current != expected ) return false;
    scanner.current++;
    return true,
}

static Token makeToken(TokenType type){
    Token token;
    token.type = type;
    token.start = scanner.start // The current scanned token
    token.length = (int)(scanner.current - scanner.start);
    token.line = scanner.line;
    return token;
}

// We use the scanner's start and current pointers
// To capture the token's lexeme

static Token errorToken(const char* message){
    Token token;
    token.type = TOKEN_ERROR;
    token.start = message;
    token.length = (int)strlen(message);
    token.line = scanner.line;
    return token;
}


// SEPARATE MINI-SCANNER to consume all the whiteSpace
//
static void skipWhiteSpace(){
    for(;;){
        char c = peek();
        switch (c){
            case ' ':
            case '\r':
            case '\t':
                advance();
                break;
            // Comments 
            case '/':
                if (peekNext() == '/') {
                    // A comment goes until the end of the line.
                    while (peek() != '\n' && !isAtEnd()) advance();
                } else {
                    return;
                }
                break;
            default:
            return;
        }
    }
}

static Token string() {
    while(peel() != '"' && !isAtEnd()){
        if (peek() == '\n') scanner.line++;
        advance();
    }
    if (isAtEnd()) return errorToken("Unterminated string.");

    advance();
    return makeToken(TOKEN_STRING);
}
static char peek(){
    return *scanner.current;
}

static char peekNext(){
    if (isAtEnd()) return '\0';
    return scanner.current[1];
}


static bool isDigit(char c){
    return c >= '0' && c <= '9'
}

static Token number() {
  while (isDigit(peek())) advance();

  // Look for a fractional part.
  if (peek() == '.' && isDigit(peekNext())) {
    // Consume the ".".
    advance();

    while (isDigit(peek())) advance();
  }

  return makeToken(TOKEN_NUMBER);
}

static Token identifier(){
    while (isAlpha(peek()) || isDigit(peek())) advance();
    return makeToken(identifierType());
}

static Token identifierType(){
    switch (scanner.start[0]) {
        case 'a': return checkKeyword(1, 2, "nd", TOKEN_AND);
        case 'c': return checkKeyword(1, 4, "lass", TOKEN_CLASS);
        case 'e': return checkKeyword(1, 3, "lse", TOKEN_ELSE);
        case 'f':
            if (scanner.current - scanner.start > 1) {
                switch (scanner.start[1]) {
                    case 'a': return checkKeyword(2, 3, "lse", TOKEN_FALSE);
                    case 'o': return checkKeyword(2, 1, "r", TOKEN_FOR);
                    case 'u': return checkKeyword(2, 1, "n", TOKEN_FUN);
                }
            }
            break;
   
        case 'i': return checkKeyword(1, 1, "f", TOKEN_IF);
        case 'n': return checkKeyword(1, 2, "il", TOKEN_NIL);
        case 'o': return checkKeyword(1, 1, "r", TOKEN_OR);
        case 'p': return checkKeyword(1, 4, "rint", TOKEN_PRINT);
        case 'r': return checkKeyword(1, 5, "eturn", TOKEN_RETURN);
        case 's': return checkKeyword(1, 4, "uper", TOKEN_SUPER);
        case 't':
            if (scanner.current - scanner.start > 1) {
                switch (scanner.start[1]) {
                    case 'h': return checkKeyword(2, 2, "is", TOKEN_THIS);
                    case 'r': return checkKeyword(2, 2, "ue", TOKEN_TRUE);
                }
            }
            break;
        case 'v': return checkKeyword(1, 2, "ar", TOKEN_VAR);
        case 'w': return checkKeyword(1, 4, "hile", TOKEN_WHILE);
 }

    return TOKEN_IDENTIFIER;
}


static TokenType checkKeyword(int start, int length,
    const char* rest, TokenType type) {
  if (scanner.current - scanner.start == start + length &&
      memcmp(scanner.start + start, rest, length) == 0) {
    return type;
  }

  return TOKEN_IDENTIFIER;
}


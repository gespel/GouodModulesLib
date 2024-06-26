#include <Array.h>

Array<String, 1024> split(String input) {
    Array<String, 1024> out;

    String sub = "";
    for(int i = 0; i < strlen(input.c_str()); i++) {
        if(input.charAt(i) == ' ') {
            out.push_back(sub);
            sub = "";
        }
        else {
            sub.concat(input.charAt(i));
        }
    }
    out.push_back(sub);
    return out;
}

enum TokenType {
    IDENTIFIER,
    NUMBER,
    FUNCTION,
    RETURN,
    SEMICOLON
};

class Token {
public:
    Token() {

    }
    Token(TokenType t, String v) {
        this->t = t;
        this->v = v;
    }
    TokenType getType() {
        return t;
    }
    String getValue() {
        return v;
    }
    String typeAsString() {
        if(t == TokenType::FUNCTION) {
            return "FUNCTION";
        }
        else if(t == TokenType::RETURN) {
            return "RETURN";
        }
        else if(t == TokenType::IDENTIFIER) {
            return "IDENTIFIER";
        }
        else if(t == TokenType::NUMBER) {
            return "NUMBER";
        }
        return "UNKNOWN";
    }
private:
    TokenType t;
    String v;
};

class Slang {
public:
    Slang();
    void tokenize(String input);
    Token createAlphaToken(String input);
    void printTokens();
private:
    Array<Token, 1024> tokens;
};

Slang::Slang() {
    
}

void Slang::printTokens() {
    for(Token t : tokens) {
        Serial.println(t.typeAsString() + " -> " + t.getValue());
    }
}

void Slang::tokenize(String input) {
    //tokens.push_back(Token(TokenType::FUNCTION, "FUNCTION"));
    Array<String, 1024> splited = split(input);
    for(auto ts : splited) {
        int i = 0;
        if(isAlpha(ts.charAt(i))) {
            String name = "";
            while(isAlpha(ts.charAt(i))) {
                name.concat(ts.charAt(i));
                i++;
            }
            auto t = createAlphaToken(name);
            tokens.push_back(t);
        }
        else if(isDigit(ts.charAt(i))) {
            String nr = "";
            while(isDigit(ts.charAt(i))) {
                nr.concat(ts.charAt(i));
                i++;
            }
            tokens.push_back(Token(TokenType::NUMBER, nr));
        }
    }
}

Token Slang::createAlphaToken(String input) {
    if(input.equals("fn")) {
        return Token(TokenType::FUNCTION, "Function");
    }
    else if(input.equals("return")) {
        return Token(TokenType::RETURN, "Return");
    }
    else if(input.equals("sinesynth")) {

    }
    else if(input.equals("sawtoothsynth")) {
        
    }
    else {
        return Token(TokenType::IDENTIFIER, input);
    }
}

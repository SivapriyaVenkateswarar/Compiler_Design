// Creating a parse tree for the rules:
// expr   → term { (+ | -) term }
// term   → factor { (* | /) factor }
// factor → ( expr ) | number


#include <iostream>
#include <cctype> // Includes functions to work with characters (isalpha(), isdigit())
#include <string>

using namespace std;

string input;
int pos=0;

//To access each character of an input:
char peek(){
    if(pos<input.size()){
        return input[pos];
    }

    return '\0'; //end of string (null character)
}

char get(){
    if(pos<input.size()){
        return input[pos++];
    }
    return '\0';
}

// Forward declarations:
int expr();
int term();
int factor();

// expr  → term { (+ | -) term }
int expr(){
    int value=term();
    while(peek()== '+' || peek()== '-'){
        char op=get();
        int rhs=term();
        if(op=='+') value=value+rhs;
        if(op=='-') value=value-rhs;
    }
    return value;
}

// term   → factor { (* | /) factor }
int term(){
    int value= factor();
    while(peek()=='*' || peek()=='/'){
        char op=get();
        int rhs= factor();
        if(op == '*'){
            value=value*rhs;
        }

        else {
            if (rhs == 0) {
                cerr << "Error: division by zero\n";
                return 0;
            }
            value /= rhs;
        }
    }

    return value;
}

// factor → ( expr ) | number
int factor(){
    
    if(isdigit(peek())){
        int value=0;
        while(isdigit(peek())){
            value = value * 10 + (get() - '0');
        }

        return value;
    }

    else if (peek() == '('){
        get();
        int value=expr();
        if(peek()==')') get();
        else { cerr << "missing )"; }

        return value;
    }
    cerr << "Error: Invalid";
}

int main(){
    cout << "Enter an arithmetic expression: ";
    getline(cin, input);

    int result = expr();

    if (pos < input.size()) {
        cerr << "Error: unexpected character at position " << pos 
             << " ('" << input[pos] << "')" << endl;
    } else {
        cout << "Result = " << result << endl;
    }

    return 0;

}

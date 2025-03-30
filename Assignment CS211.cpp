#include <iostream>
#include <fstream>
#include <cctype>
using namespace std;

int CHARClass;
char lexeme[255];
char NextChar;
int lexLen;
int token;
int NextToken;
ifstream in_fp;

void ADDChar();
void getChar();
void getNonBlank();
int LEX();

#define LETTER 0
#define DIGit 1
#define UNKNOWN 98

#define INT_LIT 11
#define IDENT 12
#define ASSIGN_OP 21
#define ADD_OP 22
#define SUB_OP 23
#define MULT_OP 24
#define DIV_OP 25
#define LEFT_PAREN 26
#define RIGHT_PAREN 27


int lOOkup(char ch) {
	switch (ch) {
	case '(':
		ADDChar();
		NextToken = LEFT_PAREN;
		break;
	case ')':
		ADDChar();
		NextToken = RIGHT_PAREN;
		break;
	case '+':
		ADDChar();
		NextToken = ADD_OP;
		break;
	case '-':
		ADDChar();
		NextToken = SUB_OP;
		break;
	case '*':
		ADDChar();
		NextToken = MULT_OP;
		break;
	case '/':
		ADDChar();
		NextToken = DIV_OP;
		break;
	default:
		ADDChar();
		NextToken = EOF;
		break;
	}
	return NextToken;
}
void ADDChar() {
	if (lexLen <= 98) {
		lexeme[lexLen++] = NextChar;
		lexeme[lexLen] = '\0';
	}
	else {
		cout << "Error - lexeme is too long" << endl;
	}
}
void getChar() {
	if (in_fp.get(NextChar)) {
		if (isalpha(NextChar))
			CHARClass = LETTER;
		else if (isdigit(NextChar))
			CHARClass = DIGit;
		else
			CHARClass = UNKNOWN;
	}
	else {
		CHARClass = EOF;
	}
}
void getNonBlank() {
	while (isspace(NextChar))
		getChar();
}
int LEX() {
	lexLen = 0;
	getNonBlank();
	switch (CHARClass) {
	case LETTER:
		ADDChar();
		getChar();
		while (CHARClass == LETTER || CHARClass == DIGit) {
			ADDChar();
			getChar();
		}
		NextToken = IDENT;
		break;
	case DIGit:
		ADDChar();
		getChar();
		while (CHARClass == DIGit) {
			ADDChar();
			getChar();
		}
		NextToken = INT_LIT;
		break;
	case UNKNOWN:
		lOOkup(NextChar);
		getChar();
		break;

	case EOF:
		NextToken = EOF;
		lexeme[0] = 'E';
		lexeme[1] = 'O';
		lexeme[2] = 'F';
		lexeme[3] = '\0';
		break;
	}
	cout << "Next token is: " << NextToken << ", Next lexeme is " << lexeme << endl;
	return NextToken;
}

int main() {
	in_fp.open(R"(C:\Users\admin\Desktop\lexcal analy\lexcal.txt)");
	if (!in_fp) {
		cout << "ERROR - can't open LEXCAL.txt" << endl;
		return 1;
	}
	else {
		getChar();
		do {
			LEX();
		} while (NextToken != EOF);
	}
	in_fp.close();
	return 0;
}

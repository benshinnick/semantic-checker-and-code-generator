/*
    Student Name: Ben Shinnick
    File Name: parser.c
    Assignment: COP4020 Project 1
*/

#include "parser.h"

void Parse_Program() {
    lookahead = Lexan();
    Match(BEGIN);
    while(lookahead != END) {
        Parse_Assignment_Statement();
    }
    lookahead = Lexan();
    Match('.');

    printf("successfuly parsed\n");
    Print_Found_Identifiers();
}

void Parse_Assignment_Statement() {
    Match(ID);
    if(lookahead != '=') {
        Print_Expected_Symbol_Message(lineNumber, '=');
        Deactivate_Lexer();
        Exit_Program_Due_To_Error();
    } else {
        Match(lookahead);
        Parse_Expression();
        Match(';');
    }
}

void Parse_Expression() {
    Parse_Term();
    while(lookahead == '+' || lookahead == '-') {
        Match(lookahead);
        Parse_Term();
    }
}

void Parse_Term() {
    Parse_Factor();
    while(lookahead == '*' || lookahead == '/') {
        Match(lookahead);
        Parse_Factor();
    }
}

void Parse_Factor() {
    if(lookahead == ID) Match(ID);
    if(lookahead == NUM) Match(NUM);
    else if(lookahead == '(') {
        Match('(');
        Parse_Expression();
        Match(')');
    }
}

void Match(int type) {
    if(lookahead == type) {
        lookahead = Lexan();
    } else {
        Print_Expected_Symbol_Message(lineNumber, type);
        Deactivate_Lexer();
        Exit_Program_Due_To_Error();
    }
}

void Print_Found_Identifiers() {
    printf("found identifiers: ");
    char** allIds = Get_All_Values_Of_Type(ID);
    for(int i = 0; i < numOfEntriesInTable; ++i) {
        if(i == numOfEntriesInTable - 1) printf("%s\n\n", allIds[i]);
        else printf("%s, ", allIds[i]);
    }
    free(allIds);
}
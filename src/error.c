/*
    Student Name: Ben Shinnick
    File Name: error.c
    Assignment: COP4020 Project 1
*/

#include "error.h"

void Print_Expected_Symbol_Message(int lineNumber, int expectedSymbol) {
    int maxAsciiValue = 256;
    if(expectedSymbol <= maxAsciiValue) {
        printf("line %i: sytax error expected \'%c\'\n", lineNumber, expectedSymbol);
    } else {
        char expectedMultiCharSymbol[50] = "";
        if(expectedSymbol == ID) strcpy(expectedMultiCharSymbol, "identifier");
        if(expectedSymbol == NUM) strcpy(expectedMultiCharSymbol, "number");
        if(expectedSymbol == BEGIN) strcpy(expectedMultiCharSymbol, "begin");
        if(expectedSymbol == END) strcpy(expectedMultiCharSymbol, "end");
        printf("line %i: sytax error expected \'%s\'\n", lineNumber, expectedMultiCharSymbol);
    }
}

void Print_Invalid_Identifier_Message(int lineNumber, char* identifier, char* causeOfError) {
    int strcmpEquals = 0;
    if(strcmp(causeOfError, "end_") == strcmpEquals) {
        printf("line %i: identifier \'%s\' cannot end with underscore\n", lineNumber, identifier);
    } else if(strcmp(causeOfError, "consecutive_") == strcmpEquals) {
        printf("line %i: identifier \'%s\' cannot have consecutive underscores\n", lineNumber, identifier);
    }
}

void Print_Illegal_Redefinition_Message(int lineNumber, char* identifier) {
    printf("line %i: illegal redefinition of identifier \'%s\'\n", lineNumber, identifier); 
}

void Print_Undefined_Variable_Message(int lineNumber, char* identifier) {
    printf("line %i: undefined variable \'%s\'\n", lineNumber, identifier);
}

void Exit_Program_Due_To_Error() {
    printf("failed to parse\n\n");
    exit(0);
}
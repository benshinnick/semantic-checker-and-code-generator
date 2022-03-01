/*
    Student Name: Ben Shinnick
    File Name: parser.c
    Assignment: COP4020 Project 1
*/

#include "parser.h"

void Initialize_Parser(char* programFileName) {
    if(programFileName == NULL) return;
    Initialize_Lexer(programFileName);

    char codeOutputFilePath[OUTPUT_FILE_PATH_MAX_CHAR_LENGTH] = "";
    strcat(codeOutputFilePath, OUTPUT_FILES_DIRECTORY);
    strcat(codeOutputFilePath, programFileName);
    strcat(codeOutputFilePath, ".out");

    codeOutputFile = fopen(codeOutputFilePath, "w");
    fputs("Hello All", codeOutputFile);
}

void Parse_Program() {
    indecles = true;
    lookahead = Lexan();
    Match(BEGIN);
    while(lookahead != END) {
        if(indecles) Parse_Declaration_Statement();
        else Parse_Assignment_Statement();
    }
    lookahead = Lexan();
    Match('.');

    printf("successfuly parsed\n");
    Print_Found_Identifiers();
}

void Parse_Declaration_Statement() {
    if(lookahead != ID) {
        Match(INT);
        Match(ID);
        Check_Declaration_Id();
        while(lookahead == ',') {
            Match(',');
            Match(ID);
            Check_Declaration_Id();
        }
        Match(';');
    } else indecles = false;
}

void Parse_Assignment_Statement() {
    Match(ID);
    Check_Assignment_Statement_Id();
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
    Parse_Term(); // gets first operand
    while(lookahead == '+' || lookahead == '-') { // gets operator
        Match(lookahead);
        Parse_Term(); // gets second operand
    }
}

void Parse_Term() {
    Parse_Factor(); // gets first operand
    while(lookahead == '*' || lookahead == '/') { // gets operator
        Match(lookahead);
        Parse_Factor(); // gets second operand
    }
}

void Parse_Factor() {
    if(lookahead == ID) Match(ID); // put into register
    if(lookahead == NUM) Match(NUM); // put into register
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

void Check_Declaration_Id() {
    if(Lookup_Symbol_Table_Type(extractedIdLexeme) == NOT_FOUND) {
        Add_Table_Entry(extractedIdLexeme, ID);
    } else {
        Print_Illegal_Redefinition_Message(lineNumber, extractedIdLexeme);
        free(extractedIdLexeme);
        Exit_Program_Due_To_Error();
    }
}

void Check_Assignment_Statement_Id() {
    if(Lookup_Symbol_Table_Type(extractedIdLexeme) == NOT_FOUND) {
        Print_Undefined_Variable_Message(lineNumber, extractedIdLexeme);
        free(extractedIdLexeme);
        Exit_Program_Due_To_Error();
    }
    else free(extractedIdLexeme);
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

void Deactivate_Parser() {
    if(codeOutputFile != NULL) fclose(codeOutputFile);
    Deactivate_Lexer();
}
/*
    Student Name: Ben Shinnick
    File Name: lexical-analyzer.c
    Assignment: COP4020 Project 1
*/

#include "lexical-analyzer.h"

void Initialize_Lexer(char* programFileName) {
    if(programFileName == NULL) return;

    char programFilePath[INPUT_FILE_PATH_MAX_CHAR_LENGTH] = "";
    strcat(programFilePath, INPUT_FILES_DIRECTORY);
    strcat(programFilePath, programFileName);

    Initialize_Symbol_Table();
    programFile = fopen(programFilePath, "r");
    lookahead = -999;
    lineNumber = 1;
    extractedIdLexeme = NULL;
}

int Lexan() {
    while(true) {
        char currChar = fgetc(programFile);
        if(isspace(currChar)) {
            if(currChar == '\n') lineNumber++;
            continue;
        }
        else if(currChar == '~') {
            while((currChar = fgetc(programFile)) != '\n');
            lineNumber++;
            continue;
        }
        else if(isdigit(currChar)) {
            ungetc(currChar, programFile);
            int numLexeme = Extract_Num_Lexeme();
            return NUM;
        }
        else if(isalpha(currChar)) {
            ungetc(currChar, programFile);
            char* idLexeme = Extract_Id_Lexeme();
            int type = Lookup_Symbol_Table_Type(idLexeme);
            // printf("idLexeme = %s, %i\n", idLexeme, type);
            if(type == NOT_FOUND) {
                if(!Is_Valid_Id(idLexeme)) {
                    free(idLexeme);
                    Deactivate_Lexer();
                    Exit_Program_Due_To_Error();
                } else type = ID;
            }
            extractedIdLexeme = idLexeme;
            return type;
        }
        else if(currChar == EOF) {
            return DONE;
        }
        else {
            return currChar;
        }
    }
}

int Extract_Num_Lexeme() {
    char numLexeme[MAX_ID_CHAR_SIZE];
    int pos = 0;
    char currChar = fgetc(programFile);
    while(isalnum(currChar) || currChar == '_') {
        numLexeme[pos++] = currChar;
        currChar = fgetc(programFile);
    }
    ungetc(currChar, programFile);
    numLexeme[pos] = '\0';

    int numLexemeIntValue;
    sscanf(numLexeme, "%d", &numLexemeIntValue);

    return numLexemeIntValue;
}

char* Extract_Id_Lexeme() {
    char* idLexeme = malloc(MAX_ID_CHAR_SIZE);

    int pos = 0;
    char currChar = fgetc(programFile);
    while(isalnum(currChar) || currChar == '_') {
        idLexeme[pos++] = currChar;
        currChar = fgetc(programFile);
    }
    ungetc(currChar, programFile);
    idLexeme[pos] = '\0';

    return idLexeme;
}

bool Is_Valid_Id(char* idLexeme) {
    int idLength = strlen(idLexeme);
    for(int i = 1; i < idLength; ++i) {
        if(idLexeme[i-1] == idLexeme[i] && idLexeme[i] == '_') {
            Print_Invalid_Identifier_Message(lineNumber, idLexeme, "consecutive_");
            return false;
        }
        else if(i == idLength - 1 && idLexeme[i] == '_') {
            Print_Invalid_Identifier_Message(lineNumber, idLexeme, "end_");
            return false;
        }
    }
    return true;
}

void Deactivate_Lexer() {
    if(programFile != NULL) fclose(programFile);
    Free_Symbol_Table();
}
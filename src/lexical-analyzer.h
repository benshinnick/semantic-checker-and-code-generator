/*
    Student Name: Ben Shinnick
    File Name: lexical-analyzer.h
    Assignment: COP4020 Project 1
    Description:
     Contains functions responsible
     for extracting token types from
     program input files
*/

#ifndef LEXICAL_ANALYZER_H
#define LEXICAL_ANALYZER_H

#include <ctype.h>

#include "symbol-table.h"
#include "error.h"

#define INPUT_FILES_DIRECTORY "input-files/"
#define INPUT_FILE_PATH_MAX_CHAR_LENGTH 50

int lookahead;
int lineNumber;
char* extractedIdLexeme;

FILE* programFile;

void Initialize_Lexer(char* programFileName);

int Lexan();

int Extract_Num_Lexeme();

char* Extract_Id_Lexeme();

bool Is_Valid_Id(char* idLexeme);

void Deactivate_Lexer();

#endif
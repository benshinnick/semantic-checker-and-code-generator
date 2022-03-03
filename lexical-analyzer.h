/*
    Student Name: Ben Shinnick
    File Name: lexical-analyzer.h
    Assignment: COP4020 Project 2
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

// used a separate folder to hold input files while developing
#define INPUT_FILES_DIRECTORY ""
#define INPUT_FILE_PATH_MAX_CHAR_LENGTH 50

int lookahead;
int lineNumber;

char* extractedIdLexeme;
int extractedNumLexeme;

FILE* programFile;

void Initialize_Lexer(char* programFileName);

int Lexan();

int Extract_Num_Lexeme();

char* Extract_Id_Lexeme();

bool Is_Valid_Id(char* idLexeme);

void Deactivate_Lexer();

#endif
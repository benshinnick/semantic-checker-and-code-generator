/*
    Student Name: Ben Shinnick
    File Name: parser.h
    Assignment: COP4020 Project 1
    Description:
     Contains functions responsible
     for parsing programs and throwing
     syntax errors if they exist
*/

#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>

#include "lexical-analyzer.h"
#include "error.h"

#define OUTPUT_FILES_DIRECTORY "output-files/"
#define OUTPUT_FILE_PATH_MAX_CHAR_LENGTH 50

bool indecles;
FILE* codeOutputFile;

void Initialize_Parser(char* programFileName);

void Parse_Program();

void Parse_Declaration_Statement();

void Parse_Assignment_Statement();

void Parse_Expression();

void Parse_Term();

void Parse_Factor();

void Match(int type);

void Check_Declaration_Id();

void Check_Assignment_Statement_Id();

void Print_Found_Identifiers();

void Deactivate_Parser();

#endif
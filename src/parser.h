/*
    Student Name: Ben Shinnick
    File Name: parser.h
    Assignment: COP4020 Project 1
    Description:
     Contains functions responsible
     for parsing programs and throwing
     syntax and semantic errors if they
     exist. Also generates register based
     code output files.
*/

#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>

#include "lexical-analyzer.h"
#include "error.h"

#define OUTPUT_FILES_DIRECTORY "output-files/"
#define OUTPUT_FILE_PATH_MAX_CHAR_LENGTH 50
#define MAX_POSTFIX_ITEMS 25

bool indecles;
int registerCount;

char* assignmentStatementId;
char** postfixContainer;
int numOfItemsInPostfixContainer;

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

void Output_Register_Item_To_File(int type);

void Output_Register_Operation_To_File(char operator);

void Ouput_Variable_Register_Assignment_To_File();

void Output_Postfix_Expression_To_File();

void Reset_Postfix_Container_And_Register_Count();

void Deactivate_Parser();

#endif
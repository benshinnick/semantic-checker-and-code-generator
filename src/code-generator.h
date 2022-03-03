/*
    Student Name: Ben Shinnick
    File Name: code-generator.h
    Assignment: COP4020 Project 2
    Description:
     Contains functions that generates
     the register based code and outputs
     that code to .out files
*/

#ifndef CODE_GENERATOR_H
#define CODE_GENERATOR_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define OUTPUT_FILES_DIRECTORY "output-files/"
#define OUTPUT_FILE_PATH_MAX_CHAR_LENGTH 50
#define MAX_POSTFIX_ITEMS 25
#define MAX_POSTFIX_ITEM_CHAR_LENGTH 50

int registerCount;

char* assignmentStatementId;
char** postfixContainer;
int numOfItemsInPostfixContainer;

FILE* codeOutputFile;

void Initialize_Code_Generator(char* programFileName);

void Output_Register_Identifier_Assignment_To_File(char* extractedIdLexeme);

void Output_Register_Number_Assignment_To_File(int extractedNumLexeme);

void Output_Register_Operation_To_File(char operator);

void Ouput_Variable_Register_Assignment_To_File();

void Output_Postfix_Expression_To_File();

void Write_Illegal_Program_Message_To_Output_File();

void Reset_Postfix_Container_And_Register_Count();

void Deactivate_Code_Generator();

#endif
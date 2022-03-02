/*
    Student Name: Ben Shinnick
    File Name: parser.h
    Assignment: COP4020 Project 2
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
#include "code-generator.h"
#include "error.h"

bool indecles;

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

void Deactivate_Parser_Due_To_Error();

void Deactivate_Parser();

#endif
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

void Parse_Program();

void Parse_Assignment_Statement();

void Parse_Expression();

void Parse_Term();

void Parse_Factor();

void Match(int type);

void Print_Found_Identifiers();

#endif
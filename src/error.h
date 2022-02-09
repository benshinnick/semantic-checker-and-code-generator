/*
    Student Name: Ben Shinnick
    File Name: error.h
    Assignment: COP4020 Project 1
    Description:
     Contains functions responsible
     for handling error operations
*/

#ifndef ERROR_H
#define ERROR_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "type-constants.h"

void Print_Expected_Symbol_Message(int lineNumber, int expectedSymbol);

void Print_Invalid_Identifier_Message(int lineNumber, char* identifier, char* causeOfError);

void Exit_Program_Due_To_Error();

#endif
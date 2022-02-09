/*
    Student Name: Ben Shinnick
    File Name: symbol-table.h
    Assignment: COP4020 Project 1
    Description:
     Contains functions responsible
     for creating and adding entries
     to the symbol table
*/

#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "type-constants.h"

#define SYMBOL_TABLE_SIZE 100
#define MAX_ID_CHAR_SIZE 80

typedef struct TableEntry {
    char* value;
    int type;
} TableEntry;

struct TableEntry** symbolTable;
int numOfEntriesInTable;

void Initialize_Symbol_Table();

TableEntry* Create_Table_Entry(char* value, int type);

void Add_Table_Entry(char* value, int type);

bool Remove_Table_Entry(char* value);

bool Contains_Table_Entry(char* value);

int Lookup_Symbol_Table_Type(char* idLexeme);

char** Get_All_Values_Of_Type(int type);

void Free_Symbol_Table();

#endif
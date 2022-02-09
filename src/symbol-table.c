/*
    Student Name: Ben Shinnick
    File Name: symbol-table.c
    Assignment: COP4020 Project 1
*/

#include "symbol-table.h"

void Initialize_Symbol_Table() {
    symbolTable = malloc(SYMBOL_TABLE_SIZE * sizeof(TableEntry));
    numOfEntriesInTable = 0;
}

TableEntry* Create_Table_Entry(char* value, int type) {
    TableEntry* tableEntry = malloc(sizeof(TableEntry));
    tableEntry->value = value;
    tableEntry->type = type;
    return tableEntry;
}

void Add_Table_Entry(char* value, int type) {
    struct TableEntry* newTableEntry = Create_Table_Entry(value, type);
    symbolTable[numOfEntriesInTable] = newTableEntry;
    numOfEntriesInTable++;
}

bool Remove_Table_Entry(char* value) {
    if(symbolTable == NULL) return false;

    int strcmpEquals = 0;
    for(int i = 0; i < numOfEntriesInTable; ++i) {
        if(strcmp(symbolTable[i]->value, value) == strcmpEquals) {
            free(symbolTable[i]);
            for(int j = i; j < numOfEntriesInTable; ++j) {
                symbolTable[j] = symbolTable[j+1];
            }
            numOfEntriesInTable--;
            return true; //success
        }
    }
    return false; //failure
}

bool Contains_Table_Entry(char* value) {
    if(symbolTable == NULL) return false;

    int strcmpEquals = 0;
    for(int i = 0; i < numOfEntriesInTable; ++i) {
        if(strcmp(symbolTable[i]->value, value) == strcmpEquals) {
            return true;
        }
    }
    return false;
}

int Lookup_Symbol_Table_Type(char* idLexeme) {
    int strcmpEquals = 0;
    if(strcmp(idLexeme, "begin") == strcmpEquals) return BEGIN;
    else if(strcmp(idLexeme, "end") == strcmpEquals) return END;
    else if(Contains_Table_Entry(idLexeme)) return ID;
    else return NOT_FOUND;
}

char** Get_All_Values_Of_Type(int type) {
    char** allIdValues = malloc(SYMBOL_TABLE_SIZE * sizeof(TableEntry));
    int idArrayCounter = 0;
    for(int i = 0; i < numOfEntriesInTable; ++i) {
        if(symbolTable[i]->type == type) {
            allIdValues[idArrayCounter] = symbolTable[i]->value;
            idArrayCounter++;
        }
    }
    return allIdValues;
}

void Free_Symbol_Table() {
    for(int i = 0; i < numOfEntriesInTable; ++i) {
        free(symbolTable[i]->value);
        free(symbolTable[i]);
    }
    free(symbolTable);
}
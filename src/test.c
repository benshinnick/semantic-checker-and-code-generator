/*
    Student Name: Ben Shinnick
    File Name: test.c
    Assignment: COP4020 Project 2
    Description:
     [not intended for submission] File I
     used to test main components of program
     while developing
*/

#include "parser.h"

void Test_Lexical_Analyzer() {
    lookahead = Lexan();
    while(lookahead != DONE) {
        if(lookahead == BEGIN) printf("BEGIN\n");
        else if(lookahead == ID) printf("ID\n");
        else if(lookahead == NUM) printf("NUM\n");
        else if(lookahead == END) printf("END\n");
        else printf("%c\n", lookahead);
        lookahead = Lexan();
    }

    printf("\nFound Ids:\n");
    char** allIds = Get_All_Values_Of_Type(ID);
    for(int i = 0; i < numOfEntriesInTable; ++i) {
        printf("[%s]\n", allIds[i]);
    }
    free(allIds);
}

void Test_Symbol_Table() {
    Initialize_Symbol_Table();

    char value1[] = "hello";
    char value2[] = "goodbye";
    char value3[] = "bonjour";
    Add_Table_Entry(value1, ID);
    Add_Table_Entry(value2, ID);
    Add_Table_Entry(value3, ID);
    Add_Table_Entry("yo", ID);
    Add_Table_Entry("what's up", ID);
    Add_Table_Entry("hi!", ID);

    printf("Before Removing:\n");
    char** allIds = Get_All_Values_Of_Type(ID);
    for(int i = 0; i < numOfEntriesInTable; ++i) {
        printf("[%s]\n", allIds[i]);
    }
    free(allIds);

    printf("\nContains %s: %i\n", value1, Contains_Table_Entry(value1));
    printf("Contains %s: %i\n", value2, Contains_Table_Entry(value2));
    printf("Contains %s: %i\n", "sup", Contains_Table_Entry("sup"));

    printf("\nRemoving: %s\n", value2);
    Remove_Table_Entry(value2);
    printf("Removing: %s\n", value1);
    Remove_Table_Entry(value1);
    printf("Removing: %s\n", value3);
    Remove_Table_Entry(value3);
    printf("Removing: %s\n\n", "hi!");
    Remove_Table_Entry("hi!");

    printf("After Removing:\n");
    allIds = Get_All_Values_Of_Type(ID);
    for(int i = 0; i < numOfEntriesInTable; ++i) {
        printf("[%s]\n", allIds[i]);
    }
    free(allIds);

    printf("\nContains %s: %i\n", value1, Contains_Table_Entry(value1));
    printf("Contains %s: %i\n", value3, Contains_Table_Entry(value3));
    printf("Contains %s: %i\n", "yo", Contains_Table_Entry("yo"));

    //Modified version of Free_Symbol_Table, since we arent allocating values
    for(int i = 0; i < numOfEntriesInTable; ++i) {
        free(symbolTable[i]);
    }
    free(symbolTable);
}

void Test_Print_Program_File() {
    if(programFile == NULL) return;

    char ch;
    while((ch = fgetc(programFile)) != EOF)
        printf("%c",ch);
}

void Print_Divider() {
    printf("-----------------------------------------------------------------------\n");
}

int main(int argc, char *argv[]) {
    if(argv[1] == NULL) { printf("no program file provided\n"); return 0; }
    else { Print_Divider(); printf("Testing With Input File %s\n", argv[1]); }

    Print_Divider();

    printf("TESTING SYMBOL TABLE:\n");
    Test_Symbol_Table();
    
    Print_Divider();

    printf("FILE WE ARE TESTING: (\"%s\")\n", argv[1]);
    Initialize_Lexer(argv[1]);
    Test_Print_Program_File();
    Deactivate_Lexer();

    Print_Divider();

    printf("TESTING LEXICAL ANALYZER:\n");
    Initialize_Lexer(argv[1]);
    Test_Lexical_Analyzer();
    Deactivate_Lexer();

    Print_Divider();

    printf("TESTING PARSER:\n");
    Initialize_Lexer(argv[1]);
    Parse_Program();
    Deactivate_Lexer();
    
    return 0;
}
/*
    Student Name: Ben Shinnick
    File Name: main.c
    Assignment: COP4020 Project 1
*/

#include "parser.h"

int main(int argc, char *argv[]) {
    if(argv[1] == NULL) { printf("no program file provided\n"); return 0; }
    else printf("compiling %s\n", argv[1]);

    Initialize_Parser(argv[1]);
    Parse_Program();
    Deactivate_Parser();
    
    return 0;
}
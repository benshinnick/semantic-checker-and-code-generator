/*
    Student Name: Ben Shinnick
    File Name: parser.c
    Assignment: COP4020 Project 1
*/

#include "parser.h"

void Initialize_Parser(char* programFileName) {
    if(programFileName == NULL) return;
    Initialize_Lexer(programFileName);

    char codeOutputFilePath[OUTPUT_FILE_PATH_MAX_CHAR_LENGTH] = "";
    strcat(codeOutputFilePath, OUTPUT_FILES_DIRECTORY);
    strcat(codeOutputFilePath, programFileName);
    strcat(codeOutputFilePath, ".out");
    codeOutputFile = fopen(codeOutputFilePath, "w");

    registerCount = -999;
    int numOfItemsInPostfixContainer = -999;
    postfixContainer = malloc(MAX_POSTFIX_ITEMS *  MAX_ID_CHAR_SIZE * sizeof(char));
    fprintf(codeOutputFile, "Compiling %s.in\n", programFileName);
}

void Parse_Program() {
    indecles = true;
    lookahead = Lexan();
    Match(BEGIN);
    while(lookahead != END) {
        if(indecles) Parse_Declaration_Statement();
        else {
            Reset_Postfix_Container_And_Register_Count();
            Parse_Assignment_Statement();
            Ouput_Variable_Register_Assignment_To_File();
            Output_Postfix_Expression_To_File();
        }
    }
    lookahead = Lexan();
    Match('.');

    printf("successfuly parsed\n");
    Print_Found_Identifiers();
}

void Parse_Declaration_Statement() {
    if(lookahead != ID) {
        Match(INT);
        Match(ID);
        Check_Declaration_Id();
        while(lookahead == ',') {
            Match(',');
            Match(ID);
            Check_Declaration_Id();
        }
        Match(';');
    } else indecles = false;
}

void Parse_Assignment_Statement() {
    Match(ID);
    Check_Assignment_Statement_Id();
    if(lookahead != '=') {
        Print_Expected_Symbol_Message(lineNumber, '=');
        Deactivate_Parser_Due_To_Error();
    } else {
        Match(lookahead);
        Parse_Expression();
        Match(';');
    }
}

void Parse_Expression() {
    Parse_Term(); // gets first operand
    while(lookahead == '+' || lookahead == '-') {
        char operator = lookahead;
        Match(lookahead);
        Parse_Term(); // gets second operand
        Output_Register_Operation_To_File(operator);  // gets operator
    }
}

void Parse_Term() {
    Parse_Factor(); // gets first operand
    while(lookahead == '*' || lookahead == '/') {
        char operator = lookahead;
        Match(lookahead);
        Parse_Factor(); // gets second operand
        Output_Register_Operation_To_File(operator); // gets operator
    }
}

void Parse_Factor() {
    if(lookahead == ID) {
        Output_Register_Item_To_File(ID);
        Match(ID);
    } if(lookahead == NUM) {
        Output_Register_Item_To_File(NUM);
        Match(NUM);
    } else if(lookahead == '(') {
        Match('(');
        Parse_Expression();
        Match(')');
    }
}

void Match(int type) {
    if(lookahead == type) {
        lookahead = Lexan();
    } else {
        if(lookahead == NOT_LEGAL) Deactivate_Parser_Due_To_Error();
        Print_Expected_Symbol_Message(lineNumber, type);
        Deactivate_Parser_Due_To_Error();
    }
}

void Check_Declaration_Id() {
    if(Lookup_Symbol_Table_Type(extractedIdLexeme) == NOT_FOUND) {
        Add_Table_Entry(extractedIdLexeme, ID);
    } else {
        Print_Illegal_Redefinition_Message(lineNumber, extractedIdLexeme);
        Deactivate_Parser_Due_To_Error();
    }
}

void Check_Assignment_Statement_Id() {
    if(Lookup_Symbol_Table_Type(extractedIdLexeme) == NOT_FOUND) {
        Print_Undefined_Variable_Message(lineNumber, extractedIdLexeme);
        Deactivate_Parser_Due_To_Error();
    }
    else assignmentStatementId = extractedIdLexeme;;
}

void Print_Found_Identifiers() {
    printf("found identifiers: ");
    char** allIds = Get_All_Values_Of_Type(ID);
    for(int i = 0; i < numOfEntriesInTable; ++i) {
        if(i == numOfEntriesInTable - 1) printf("%s\n\n", allIds[i]);
        else printf("%s, ", allIds[i]);
    }
    free(allIds);
}

void Output_Register_Item_To_File(int type) {
    registerCount++;
    if(type == ID) {
        fprintf(codeOutputFile, "R%i = %s\n", registerCount, extractedIdLexeme);
        postfixContainer[numOfItemsInPostfixContainer++] = extractedIdLexeme;
    } else if (type == NUM) {
        fprintf(codeOutputFile, "R%i = %i\n", registerCount, extractedNumLexeme);
        char* strExtractedNumLexeme = malloc(sizeof(char) * MAX_ID_CHAR_SIZE);
        sprintf(strExtractedNumLexeme, "%i", extractedNumLexeme);
        postfixContainer[numOfItemsInPostfixContainer++] = strExtractedNumLexeme;
    }
}

void Output_Register_Operation_To_File(char operator) {
    registerCount--;
    int firstRegister = registerCount;
    int secondRegister = registerCount + 1;
    fprintf(codeOutputFile, "R%i = R%i %c R%i\n", firstRegister, firstRegister, operator, secondRegister);
    char* strOperator = malloc(sizeof(char));
    strOperator[0] = operator;
    postfixContainer[numOfItemsInPostfixContainer++] = strOperator;
}

void Ouput_Variable_Register_Assignment_To_File() {
    fprintf(codeOutputFile, "%s = R%i\n", assignmentStatementId, registerCount);
    free(assignmentStatementId);
}

void Output_Postfix_Expression_To_File() {
    fputs("*****[", codeOutputFile);
    for(int i = 0; i < numOfItemsInPostfixContainer; ++i) {
       fputs(postfixContainer[i], codeOutputFile);
       if(i != numOfItemsInPostfixContainer - 1) fputc(',', codeOutputFile);
    }
    fputs("]*****\n", codeOutputFile);
}

void Write_Illegal_Program_Message_To_Output_File() {
    fputs("*!*!*! Error Found In Program *!*!*!*!*!\n", codeOutputFile);
    fputs("*!*!*! Code Generation Terminated *!*!*!\n", codeOutputFile);
}

void Reset_Postfix_Container_And_Register_Count() {
    for(int i = 0; i < numOfItemsInPostfixContainer; ++i) {
        free(postfixContainer[i]);
    }
    numOfItemsInPostfixContainer = 0;
    registerCount = -1;
}

void Deactivate_Parser_Due_To_Error() {
    Write_Illegal_Program_Message_To_Output_File();
    if(codeOutputFile != NULL) fclose(codeOutputFile);
    Reset_Postfix_Container_And_Register_Count();
    free(postfixContainer);
    Deactivate_Lexer();
    Exit_Program_Due_To_Error();
}

void Deactivate_Parser() {
    if(codeOutputFile != NULL) fclose(codeOutputFile);
    Reset_Postfix_Container_And_Register_Count();
    free(postfixContainer);
    Deactivate_Lexer();
}
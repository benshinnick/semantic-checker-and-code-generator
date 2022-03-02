#include "code-generator.h"

void Initialize_Code_Generator(char* programFileName) {
    char codeOutputFilePath[OUTPUT_FILE_PATH_MAX_CHAR_LENGTH] = "";
    strcat(codeOutputFilePath, OUTPUT_FILES_DIRECTORY);
    strcat(codeOutputFilePath, programFileName);
    strcat(codeOutputFilePath, ".out");
    codeOutputFile = fopen(codeOutputFilePath, "w");

    registerCount = -999;
    int numOfItemsInPostfixContainer = -999;
    postfixContainer = malloc(MAX_POSTFIX_ITEMS *  MAX_POSTFIX_ITEM_CHAR_LENGTH * sizeof(char));
    fprintf(codeOutputFile, "Compiling %s.in\n", programFileName);
}

void Output_Register_Identifier_Assignment_To_File(char* extractedIdLexeme) {
    registerCount++;
    fprintf(codeOutputFile, "R%i = %s\n", registerCount, extractedIdLexeme);
    postfixContainer[numOfItemsInPostfixContainer++] = extractedIdLexeme;
}

void Output_Register_Number_Assignment_To_File(int extractedNumLexeme) {
    registerCount++;
    fprintf(codeOutputFile, "R%i = %i\n", registerCount, extractedNumLexeme);
    const int MAX_NUM_SIZE = 90;
    char* strExtractedNumLexeme = malloc(sizeof(char) * MAX_NUM_SIZE);
    sprintf(strExtractedNumLexeme, "%i", extractedNumLexeme);
    postfixContainer[numOfItemsInPostfixContainer++] = strExtractedNumLexeme;
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

void Deactivate_Code_Generator() {
    if(codeOutputFile != NULL) fclose(codeOutputFile);
    Reset_Postfix_Container_And_Register_Count();
    free(postfixContainer);
}
// evaluator.cc

#include <stdio.h>
#include <cstring>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <iostream>

#include "evaluator.h"

// check ident
// if stmt.value != null
//   evalstmt(stmt) !!!make dat function!!
// if string or number != null
//   evalarg()
//   do something based on string/num
//   if nextArg != null
//     evalarg()

void runEvaluator(stmt *stmt_head) {
    evalStmt(stmt_head);
}

void evalStmt (stmt *head) {
    std::string s;
    stmt *temp_stmt = head;
    args *temp_arg = head->stmtArgs;

    const std::string ident = head->ident;
    if (ident == "println") {
        while(temp_arg->nextArg !=NULL) {
            if (temp_arg->argNum != NULL) {
                std::cout << *(temp_arg->argNum);
            }

            if (temp_arg->argString != NULL) {
                std::cout << *(temp_arg->argString);
            }

            if (temp_arg->argStmt != NULL) {
                evalStmt(temp_arg->argStmt);
                std::cout << temp_arg->argStmt->value;
            }
            temp_arg = temp_arg->nextArg;
        }
        std::cout << std::endl;
    }
    else if (ident == "add") {
        long double sum = 0;
        while(temp_arg->nextArg !=NULL) {
            if (temp_arg->argNum != NULL) {
                sum += *(temp_arg->argNum);
            }
            else if (temp_arg->argStmt != NULL) {
                evalStmt(temp_arg->argStmt);
                sum += stold(temp_arg->argStmt->value);
            }
            else if (temp_arg->argString != NULL) {
                shittyErrorFunction();
            }

            temp_arg = temp_arg->nextArg;
        }
        std::ostringstream strs;
        strs << sum;
        head->value = strs.str();

    }
}

/*
   std::string evalArg (args *arg) {
   std::string next_string;
   std::string return_string;

//if (arg->argStmt->value != NULL)



if (arg->argNum != NULL)
{
return_string = arg->argNum;
}
if (arg->argString != NULL)
{
return_string = arg->argString;
}
if (arg->nextArg != NULL)
{
next_string = evalArg(arg->nextArg);
return_string = return_string + next_string;
}
return return_string;
}
*/

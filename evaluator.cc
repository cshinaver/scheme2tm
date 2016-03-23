// evaluator.cc

#include <stdio.h>
#include <cstring>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <iostream>

#include "evaluator.h"

void runEvaluator(std::vector<stmt *> stmts) {
    for (auto s : stmts) {
        evalStmt(s);
    }
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
                okayErrorFunction(1,"Tried to add a string");
            }

            temp_arg = temp_arg->nextArg;
        }
        std::ostringstream strs;
        strs << sum;
        head->value = strs.str();

    }
    else if (ident == "sub") {
        long double diff;
        if (temp_arg->argNum != NULL) {
            diff = 2 * *(temp_arg->argNum);
        }
        else {
            // makes sure it defaults to 0 if sub is given no args
            diff = 0;
        }
        while(temp_arg->nextArg !=NULL) {
            if (temp_arg->argNum != NULL) {
                diff -= *(temp_arg->argNum);
            }
            else if (temp_arg->argStmt != NULL) {
                evalStmt(temp_arg->argStmt);
                diff -= stold(temp_arg->argStmt->value);
            }
            else if (temp_arg->argString != NULL) {
                okayErrorFunction(1,"Tried to subtract a string");
            }

            temp_arg = temp_arg->nextArg;
        }
        std::ostringstream strs;
        strs << diff;
        head->value = strs.str();

    }
    else if (ident == "mult") {
        long double product = 1;
        while(temp_arg->nextArg !=NULL) {
            if (temp_arg->argNum != NULL) {
                product *= *(temp_arg->argNum);
            }
            else if (temp_arg->argStmt != NULL) {
                evalStmt(temp_arg->argStmt);
                product *= stold(temp_arg->argStmt->value);
            }
            else if (temp_arg->argString != NULL) {
                okayErrorFunction(1,"Tried to subtract a string");
            }

            temp_arg = temp_arg->nextArg;
        }
        std::ostringstream strs;
        strs << product;
        head->value = strs.str();

    }
    else if (ident == "div") {
        long double quotient;
        if (temp_arg->argNum != NULL) {
            quotient = *(temp_arg->argNum) * *(temp_arg->argNum);
        }
        else {
            // makes sure it defaults to 0 if sub is given no args
            quotient = 1;
        }
        while(temp_arg->nextArg !=NULL) {
            if (temp_arg->argNum != NULL) {
                quotient /= *(temp_arg->argNum);
            }
            else if (temp_arg->argStmt != NULL) {
                evalStmt(temp_arg->argStmt);
                quotient /= stold(temp_arg->argStmt->value);
            }
            else if (temp_arg->argString != NULL) {
                okayErrorFunction(1,"Tried to subtract a string");
            }

            temp_arg = temp_arg->nextArg;
        }
        std::ostringstream strs;
        strs << quotient;
        head->value = strs.str();

    }
}

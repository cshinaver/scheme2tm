// evaluator.cc

#include <stdio.h>
#include <cstring>
#include <fstream>
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

    std::cout << "before println if statment" << std::endl;
    std::cout << head->ident << std::endl;
    if (head->ident == "println") {
        std::cout << "dat if tho" << std::endl;
        do{
            //if (temp_stmt->stmtArgs != NULL)
            {
                std::cout << "n'do" << std::endl;
                if (temp_arg->argNum != NULL)
                {
                    std::cout << "in arg num" << std::endl;
                    std::cout << temp_arg->argNum << std::endl;
                }

                if (temp_arg->argString != NULL)
                {
                    std::cout << "in arg str" << std::endl;
                    std::cout << temp_arg->argString << std::endl;
                }

                if (temp_arg->argStmt != NULL)
                {
                    std::cout << "in arg stmt" << std::endl;
                    evalStmt(temp_arg->argStmt);
                }
            }
        }while (temp_arg->nextArg != NULL);
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

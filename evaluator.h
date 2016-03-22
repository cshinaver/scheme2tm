#ifndef EVALUATOR_H
#define EVALUATOR_H
#include "parser.h"

void runEvaluator(stmt *stmt_head);
void evalStmt(stmt *head);
std::string evalArg(args *arg);

#endif

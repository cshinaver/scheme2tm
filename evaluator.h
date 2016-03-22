#ifndef EVALUATOR_H
#define EVALUATOR_H
#include "parser.h"

void runEvaluator(std::vector<stmt *> stmts);
void evalStmt(stmt *head);
std::string evalArg(args *arg);

#endif

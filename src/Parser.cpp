#include "Parser.h"

ManualParser::ManualParser() {

  AddRule(GOAL, { MAIN_CLASS, MANY_OR_ZERO, CLASS_DECLARATION });
  AddRule(MAIN_CLASS,
          { CLASS, ID, LCUR, PUBLIC, VOID, MAIN, LB, STRING, LSQR, RSQR, ID, RB, LCUR, STATEMENT, RCUR, RCUR});
  AddRule(CLASS_DECLARATION,
          { CLASS, ID, ONE_OR_ZERO, EXTENDS_IDENTIFIER, LCUR, MANY_OR_ZERO, VAR_DECLARATION,
            MANY_OR_ZERO, METHOD_DECLARATION, RCUR});
  AddRule(VAR_DECLARATION, { TYPE, ID, SEMI });
  AddRule(METHOD_DECLARATION,
          { PUBLIC, TYPE, ID, LB, ONE_OR_ZERO, TYPE_ID_MANY, RB, LCUR, MANY_OR_ZERO, VAR_DECLARATION,
            MANY_OR_ZERO, STATEMENT, RETURN, EXPRESSION, SEMI, RCUR});
  AddRule(TYPE_ID_MANY, { TYPE, ID, MANY_OR_ZERO, DOT_TYPE_ID });
  AddRule(DOT_TYPE_ID, { DOT, TYPE, ID });
  AddRule(TYPE, { INT, LSQR, RSQR });
  AddRule(TYPE, { BOOLEAN });
  AddRule(TYPE, { INT });
  AddRule(TYPE, { ID });
  AddRule(STATEMENT, { LCUR, ONE_OR_ZERO, STATEMENT, RCUR });
  AddRule(STATEMENT, { IF, LB, EXPRESSION, RB, STATEMENT, ELSE, STATEMENT});
  AddRule(STATEMENT, { WHILE, LB, EXPRESSION, RB, STATEMENT });
  AddRule(STATEMENT, { PRINT, LB, EXPRESSION, RB, SEMI});
  AddRule(STATEMENT, { ID, EQ, EXPRESSION, SEMI });
  AddRule(STATEMENT, { ID, LSQR, EXPRESSION, RSQR, EQ, EXPRESSION, SEMI });
  AddRule(EXPRESSION, { EXPRESSION, BIOP, EXPRESSION });
  AddRule(EXPRESSION, { EXPRESSION, LSQR, EXPRESSION, RSQR });
  AddRule(EXPRESSION, { EXPRESSION, DOT, LENGTH });
  AddRule(EXPRESSION, { EXPRESSION, DOT, ID, LB, ONE_OR_ZERO, PARAS, RB});
  AddRule(PARAS, { EXPRESSION, MANY_OR_ZERO, DOT_EXPRESSION });
  AddRule(DOT_EXPRESSION, { DOT, EXPRESSION });
  AddRule(EXPRESSION, { INT_LITERAL });
  AddRule(EXPRESSION, { TRUE });
  AddRule(EXPRESSION, { FALSE });
  AddRule(EXPRESSION, { ID });
  AddRule(EXPRESSION, { THIS });
  AddRule(EXPRESSION, { NEW, INT, LSQR, EXPRESSION, RSQR });
  AddRule(EXPRESSION, { NEW, ID, LB, RB });
  AddRule(EXPRESSION, { NT, EXPRESSION });
  AddRule(EXPRESSION, { LB, EXPRESSION, RB });
}

void ManualParser::AddRule(TokenTag head, std::vector<TokenTag> form) {
  auto init_node = new NFANode();
  std::vector<NFANode *> current_nodes = { init_node };
  for (auto iter = form.begin(); iter != form.end(); iter++) {
    auto token = *iter;
    auto new_node = new NFANode();
    for (auto current_node : current_nodes) {
      current_node->nex_[token] = new_node;
    }
    if (token == MANY_OR_ZERO) {
      new_node->nex_[token] = new_node;
    }
    else if (token != ONE_OR_ZERO) {
      current_nodes.clear();
    };
    current_nodes.push_back(new_node);
  }
  for (auto node : current_nodes) {
    node->valid_ = true;
    node->tag_ = head;
  }
}

ManualParser::~ManualParser() {}

std::string ManualParser::GetParseTree(const std::vector<Token> &tokens, ParseTree &parse_tree) {
  return "";
}
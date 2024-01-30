%{
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include "AST.hpp"
extern int yylex();
extern void yyerror(const char* s);
using namespace std;
%}

%union{
string* id;
BinaryNode* bnode; //type clash bug fix
};

%code{
vector<string> selected_columns;
map<string, map<string, vector<string>>> database;
map<string, vector<string>> table;
void print_table(set<size_t>& candidate_indices);
set<size_t> interpret_predication(BinaryNode* proot);
}

%type <bnode> orcond andcond eqstmt

%token <id> TABLE COLUMN NAME //type clash bug fix
%token SELECT FROM WHERE EOL
%left OR
%left AND
%right NOT

%%

selectquery : SELECT columns FROM TABLE WHERE orcond EOL {
  table = database[*$4];
  auto candidate_indices = interpret_predication($6);
  print_table(candidate_indices);
  return 0;
}
;

columns : COLUMN {
  selected_columns.push_back(*$1);
}
| columns ',' COLUMN {
  selected_columns.push_back(*$3);
}
;

orcond : andcond
| orcond OR andcond {
  $$ = new OrNode($1, $3);
}
;

andcond : eqstmt
| andcond AND eqstmt {
  $$ = new AndNode($1, $3);
}
;

eqstmt : NAME '=' NAME {
  IdNode* left = new IdNode(*$1);
  IdNode* right = new IdNode(*$3);
  $$ = new EqualsNode(left, right, true);
}
| NOT NAME '=' NAME {
  IdNode* left = new IdNode(*$2);
  IdNode* right = new IdNode(*$4);
  $$ = new EqualsNode(left, right, false);
}
;

%%
void yyerror(const char* fmt) {
    printf("ERROR: %s\n", fmt);
}

void print_table(set<size_t>& candidate_indices){
  if(candidate_indices.empty()) {
    cout << "NO RESULTS\n";
    return;
  }
  for (auto column : selected_columns)
    cout << column << "\t";
  cout << endl;

  for (auto idx : candidate_indices) {
    for (auto column : selected_columns)
      cout << table[column][idx] << "\t";
    cout << endl;
  }
}

set<size_t> interpret_predication(BinaryNode* proot) {
  set<size_t> candidate_indices{};
  if(auto visitor = dynamic_cast<OrNode*>(proot)) {
    auto lset = interpret_predication(dynamic_cast<BinaryNode*>(visitor->left()));
    auto rset = interpret_predication(dynamic_cast<BinaryNode*>(visitor->right()));
    set_union(lset.begin(), lset.end(), rset.begin(), rset.end(), inserter(candidate_indices, candidate_indices.begin()));
  } else if(auto visitor = dynamic_cast<AndNode*>(proot)) {
    auto lset = interpret_predication(dynamic_cast<BinaryNode*>(visitor->left()));
    auto rset = interpret_predication(dynamic_cast<BinaryNode*>(visitor->right()));
    set_intersection(lset.begin(), lset.end(), rset.begin(), rset.end(), inserter(candidate_indices, candidate_indices.begin()));
  } else if(auto visitor = dynamic_cast<EqualsNode*>(proot)) {
    auto lid = dynamic_cast<IdNode*>(visitor->left())->id();
    auto rid = dynamic_cast<IdNode*>(visitor->right())->id();
    if(visitor->isEqual()){
      if(table.find(lid) != table.end()){  //if the column exists
        if(rid == lid) {//all items
          for (size_t i = 0; i < table[lid].size(); i++)
            candidate_indices.insert(i);
        } else if (table.find(rid) != table.end()) {//column eq another column
          for (size_t i = 0; i < table[lid].size(); i++)
            if(table[lid][i] == table[rid][i])
              candidate_indices.insert(i);
        } else {  // column eq value
          for (size_t i = 0; i < table[lid].size(); i++)
            if (table[lid][i] == rid)
              candidate_indices.insert(i);
        }
      }
    } else {  //NOT
      if(table.find(lid) != table.end()){  //if the column exists
        if(rid == lid){
          return {};  //no items
        } else if (table.find(rid) != table.end()){ //column eq another column
          for (size_t i = 0; i < table[lid].size(); i++)
            if(table[lid][i] != table[rid][i])
              candidate_indices.insert(i);
        } else {  // column eq value
          for (size_t i = 0; i < table[lid].size(); i++)
            if (table[lid][i] != rid)
              candidate_indices.insert(i);
        }
      }
    }
  }
  return candidate_indices;
}

int main(){
  map<string, vector<string>> words;
  words["w_id"] = vector<string>{"0", "1", "2",  "3",  "4",  "5",  "6", "7",
                                 "8", "9", "10", "11", "12", "13", "14"};
  words["spelling"] = vector<string>{
      "abandon",   "Apple",    "Alligator", "Airplane", "Adventure",
      "Apartment", "Abundant", "Autumn",    "Acoustic", "Aquarium",
      "Aardvark",  "Apricot",  "Astronaut", "Antelope", "Anxious"};
  database["words"] = words;

  yyparse();

  return 0;
}

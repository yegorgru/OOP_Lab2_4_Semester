#ifndef PARSER_H
#define PARSER_H
#include <stack>
#include <map>
#include <functional>
#include <utility>
#include <stdlib.h>
#include <iostream>
#include <queue>
#include <QString>
using namespace std;
class parser
{
public:
    parser();
    parser(QString input);
     void Parse(string input);
     double calc(queue<char> in);
     queue<char> to_revpol(const QString& input);
     int prior(char& in);
     bool is_digit(char& in);
     bool is_var(char& in);
     bool is_oper(char& in);
     queue<char> gen;
private:




};

#endif // PARSER_H

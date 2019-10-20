#ifndef STRINGOPERATIONS_H
#define STRINGOPERATIONS_H

#include <string>

class Data;

int StringToInt(std::string s);
bool StringToBoolean(std::string s);
float StringToFloat(std::string s);
std::string BooleanToString(bool b);
int BooleanToInt(bool b);
float BooleanToFloat(bool b);
std::string FloatToString(float f);
bool FloatToBool(float f);
int FloatToInt(float f);
std::string IntToString(int i);
float IntToFloat(int i);
bool IntToBoolean(int i);
std::string StringMinusInt(std::string s, int n);
std::string IntMinusString(int n, std::string s);
std::string StringMinusString(std::string a, std::string b);
int findStr(std::string a, std::string b);
std::string StringMulInteger(std::string s, int n);
bool Less(Data *l, Data *r);
bool Greater(Data *l, Data *r);
bool Equals(Data *l, Data *r);
bool isDigit(char c);
bool isLetter(char c);
bool isOperator(char c);
bool isPunctual(char c);

#endif // STRINGOPERATIONS_H



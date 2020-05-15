
#include "pch.h"
#include <iostream>
#include <fstream>
#include <fstream>
#include<string>
#include"Compiler.h"
std::ifstream in("input.txt");
int main()
{

	Compiler C;
	C.getFacts(in);
	C.getRules(in);
	C.GetNewFacts();

}



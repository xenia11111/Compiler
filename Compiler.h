#pragma once

#include<iostream>
#include<fstream>
#include<unordered_map>
#include<unordered_set>
#include<string>
#include<stack>
#include<vector>

class Compiler
{
public:
	Compiler();
	~Compiler();
	std::string getWord(std::ifstream&);
	void getFacts(std::ifstream& );
	void getRules(std::ifstream&);
	void InsertRule(std::string&);
	void InsertRule(std::string& _derivation, std::string& _name);
	bool Compile(const std::pair<std::string, std::string>& rule);
	bool SetTrueOrFalse(std::string& );
	void UpdateFacts();
	void GetNewFacts();
	std::unordered_map<std::string, std::string> derivableFacts; // êëþ÷-âûâîäèìûé ôàêò, çíà÷åíèå-âûâîä 
	std::unordered_set<std::string> knownFacts;
	std::unordered_set<std::string> newknownFacts;
	std::unordered_set<std::string> unknownFacts;
	std::unordered_set<std::string> undefinedFacts;
	std::unordered_set<std::string> visitedFacts;
};

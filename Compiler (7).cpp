#include "pch.h"
#include "Compiler.h"
#include<iostream>
#include<fstream>

Compiler::Compiler()
{
}


Compiler::~Compiler()
{
}

std::string Compiler::getWord(std::ifstream& in)
{
	std::string res;
	while (true) {
		char c = in.get();
		if (c == '"')
			break;
		res += c;
	}
	return res;
}

void Compiler::getFacts(std::ifstream& in) {

	while (true)
	{
		char c = in.get();
		if (c == '\n')
			break;
		if (c == '"')
		{
			auto fact = getWord(in);
			knownFacts.insert(fact);
		}
	}
}


void Compiler::getRules(std::ifstream& in)
{
	
	std::vector<std::string> rules;
	while (true)
	{
		char c = in.get();
		if (c == EOF)
			break;
		if (c == '"')
		{
			auto rule = getWord(in);
			rules.push_back(rule);
		}
	}
	for (std::string rule : rules) {
		InsertRule(rule);
	}
}


void Compiler::InsertRule(std::string& name,std::string& derivation) {

	if (derivation.rfind('>') == std::string::npos) {
		std::string n = name;
		std::string d = derivation;
		auto it = derivableFacts.find(n);
		if (it != derivableFacts.end()) {
			
			it->second = it->second + "|" + d;
		}
		
		derivableFacts.insert(std::make_pair(n, d));
	}
	else {
		int pos = derivation.rfind('>');
		std::string newName = derivation.substr(pos + 1);
		std::string newDerivation = derivation.substr(0, pos - 1);
		InsertRule(name,newName);
		InsertRule(newName,newDerivation );
	}
}

void Compiler::InsertRule(std::string &rule) {
	int pos = rule.rfind('>');
	std::string name = rule.substr(pos + 1);
	std::string derivation = rule.substr(0, pos - 1);
	InsertRule(name, derivation);
}

bool Compiler::Compile(const std::pair<std::string, std::string>& rule) {  // ������� � ������� ������� ������, ��������� �������� ���������
														// ���������� ������������ ����������� � ������� ���� ������ - � ���������� � ���������� ������
	std::string derivation = rule.second;
	std::string derivFact = rule.first;

	std::stack<bool> facts;
	std::stack<char> operations;
	std::string fact;
	bool res;
	for (int i = 0; i <= derivation.size(); i++) {
		if (fact != "" && (derivation[i] == '|' || derivation[i] == ',' || i == derivation.size())) //����� ����,��� ��������� ����, ��������� ��� ��������
		{
			bool value;                 
			value = SetTrueOrFalse(fact);
			facts.push(value);
			fact = "";

		}
		if (derivation[i] == '|' || derivation[i] == ',') {
			char operation = derivation[i];
			if (operation == '|') {                           // � �������� "|" ��������� ����, ��� � "," , ���� ���� �� ������ �������� "�����������"
				while (!operations.empty()) {          // �������� ���������� ���� ��� �������, �� ����� � ������� ������� �������������� �������� �����
					char currentOperation = operations.top();
					operations.pop();
					bool value1 = facts.top();
					facts.pop();
					bool value2 = facts.top();
					facts.pop();
					if (currentOperation == '|') {   // ��������� ���������� �������� ����� ������� � ���� ������
						res = value1 + value2;
						facts.push(res);
					}
					if (currentOperation == ',') {
						res = value1 * value2;
						facts.push(res);
					}
				}

			}
			operations.push(operation);


		}

		if (derivation[i] != '|' && derivation[i] != ',') {
			fact += derivation[i];
		}

	}

	if (operations.empty()) {        // ���� ����� ��������� ����� ���� �������� ������, �� ��������� ���������� ��������� ��������� � ����� ������
		bool value = facts.top();

		facts.pop();
		res = value + 0;
		if (res == true) {
			auto it3 = knownFacts.find(derivFact);

			if (it3 == knownFacts.end())
			{
				newknownFacts.insert(derivFact);
			}
		}
		if (res == false) { unknownFacts.insert(derivFact); }

	}
	else {                                // ���� �� �� ������, �� ������� ���������� �������� � �������������� �� ����� � ��������� �������� ���������
		while (!operations.empty()) {
			char currentOperation = operations.top();
			operations.pop();
			bool value1 = facts.top();
			facts.pop();
			bool value2 = facts.top();
			facts.pop();
			if (currentOperation == '|') {
				res = value1 + value2;
				facts.push(res);
			}
			if (currentOperation == ',') {
				res = value1 * value2;
				facts.push(res);
			}
		}

		res = facts.top();
		facts.pop();
		if (res == true) {

			auto it = knownFacts.find(derivFact);

			if (it == knownFacts.end())
			{
				newknownFacts.insert(derivFact);
			}

		}
		if (res == false) {
			unknownFacts.insert(derivFact);

		}
	}

	
	return res;
}



bool Compiler::SetTrueOrFalse(std::string& token) { // �������� ���������� �����
	auto it1 = knownFacts.find(token);
	auto it2 = newknownFacts.find(token);
	if (it1 != knownFacts.end() || it2 != newknownFacts.end())   //���� ���� ��������� ��� ���� ��������� � ���� ������, ���������� true
	{
		return true;
	}

	auto it3 = unknownFacts.find(token);
	if (it3 != unknownFacts.end()) {   //���� ���� ��������, ��� �����������-���������� false
		return false;
	}
	auto it4 = undefinedFacts.find(token);
	if (it4 != undefinedFacts.end()) { //���� �� ��� ��������� � undefinedFacts, ������ ��������� ������������, �������� ����������� ��� �������� false � �������� � undefined

		return false;

	}
	else if (derivableFacts.find(token) != derivableFacts.end()) { //�����, ���� ���� ���������, �������� �������� ������
		undefinedFacts.insert(token);
		auto it = derivableFacts.find(token);
		bool res = Compile(*it);
		undefinedFacts.erase(token);
		return res;
		
	}
	else { return false; }
}
void Compiler::UpdateFacts() {  //���� �������� ����������� ��������� �� ������� ��� �������������� ������
	for (std::string it : undefinedFacts) {
		auto it2 = derivableFacts.find(it);
		Compile(*it2);
	}
}

void Compiler::GetNewFacts() {
	for (auto it : derivableFacts) {
		Compile(it);
	}
	UpdateFacts();         
	for (auto it : newknownFacts) {
		std::cout << it << " ";
	}
}

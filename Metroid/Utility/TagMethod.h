#pragma once
#include <string>
#include <vector>

using namespace std;

class Tag
{
private: 
	vector<string> tags;
public:
	void AddTag(string tag);
	bool isHasTag(string tag);
	void EraseTag(string tag);
};
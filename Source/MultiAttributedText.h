#pragma once
#include <string>
#include <string_view>
#include <vector>
#include "ConsoleTextAttribute.h"

#include <iostream>

class MultiAttributedText
{
private:
	struct AttributeStartIndexPair
	{
		ConsoleTextAttribute Attribute;
		unsigned int StartIndex;
	};

	std::vector<AttributeStartIndexPair> _attributes;
	std::string _text;

public:
	void Print() const;

	void SetAttributeForCharacter(const int index, ConsoleTextAttribute attribute);
	void Append(ConsoleTextAttribute attribute, std::string text);

private:
	int GetAttributeStartIndexPairForTextIndex(const int index) const;

	void PrintSegment(const int index) const;

	std::string_view GetSegment(const int index) const;

	unsigned int GetSegmentLength(const int index) const;
};
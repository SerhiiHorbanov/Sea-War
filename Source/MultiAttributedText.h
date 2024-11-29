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

	void SetAttributeForCharacter(const int index, const ConsoleTextAttribute attribute);

	void TryAddAttributeAtEnd(const ConsoleTextAttribute attribute);

	void Append(const ConsoleTextAttribute attribute, const char character);
	void Append(const ConsoleTextAttribute attribute, const std::string& text);
	void Append(const std::string& text);
	void Append(const char character);

private:
	int GetAttributeStartIndexPairForTextIndex(const int index) const;

	void PrintSegment(const int index) const;

	int GetStartIndexOfSegment(const int segmentIndex) const;
	ConsoleTextAttribute GetAttributeOfSegment(const int segmentIndex) const;

	std::string_view GetSegment(const int index) const;

	unsigned int GetSegmentLength(const int index) const;
};
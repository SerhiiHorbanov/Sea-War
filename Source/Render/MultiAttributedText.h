#pragma once
#include <string>
#include <string_view>
#include <vector>
#include "ConsoleTextAttribute.h"

struct MultiAttributedText
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
	MultiAttributedText() : 
		_attributes({AttributeStartIndexPair()})
	{}
	
	MultiAttributedText(const ConsoleTextAttribute attribute, const std::string& text) : 
		_attributes({AttributeStartIndexPair(attribute)}),
		_text(text)
	{}
	
	void Print() const;

	void SetAttributeForCharacter(const int index, const ConsoleTextAttribute attribute);

	void TryAddAttributeAtEnd(const ConsoleTextAttribute attribute);
	void TryInsertAttribute(const ConsoleTextAttribute attribute, const int startIndex);
	
	void Append(const ConsoleTextAttribute attribute, const char character);
	void Append(const ConsoleTextAttribute attribute, const std::string& text);
	void Append(const std::string& text);
	void Append(const char character);
	void Append(const MultiAttributedText& other);

	void Reserve(const size_t size);
	
private:
	int GetAttributeStartPairIndexForCharacter(const int charIndex) const;

	void PrintSegment(const int index) const;

	int GetStartIndexOfSegment(const int segmentIndex) const;
	ConsoleTextAttribute GetAttributeOfSegment(const int segmentIndex) const;

	std::string_view GetSegment(const int index) const;

	unsigned int GetSegmentLength(const int index) const;
};
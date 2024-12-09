#include "MultiAttributedText.h"
#include <iostream>

void MultiAttributedText::Print() const
{
	for (int i = 0; i < _attributes.size(); i++)
		PrintSegment(i);
}

void MultiAttributedText::SetAttributeForCharacter(const int index, const ConsoleTextAttribute attribute)
{
	const int characterInPairIndex = GetAttributeStartPairIndexForCharacter(index + 1);
	ConsoleTextAttribute succedingAttribute = GetAttributeOfSegment(characterInPairIndex);
	
	TryInsertAttribute(attribute, index);
	TryInsertAttribute(succedingAttribute, index + 1);
}

void MultiAttributedText::Append(const ConsoleTextAttribute attribute, const std::string& text)
{
	TryAddAttributeAtEnd(attribute);
	_text += text;
}

void MultiAttributedText::Append(const ConsoleTextAttribute attribute, char character)
{
	TryAddAttributeAtEnd(attribute);
	_text += character;
}

void MultiAttributedText::Append(const std::string& text)
{
	_text += text;
}

void MultiAttributedText::Append(const char character)
{
	_text += character;
}

void MultiAttributedText::Append(const MultiAttributedText& other)
{
	const int previousTextLength = _text.size();
	_text += other._text;
	
	const std::vector<AttributeStartIndexPair>& otherAttributes = other._attributes;
	
	_attributes.reserve(_attributes.size() + otherAttributes.size());
	for (auto each : otherAttributes)
		TryInsertAttribute(each.Attribute, each.StartIndex + previousTextLength);
}

void MultiAttributedText::Reserve(const size_t size)
{
	_text.reserve(size);
}

void MultiAttributedText::TryAddAttributeAtEnd(const ConsoleTextAttribute attribute)
{
	const int attributesAmount = _attributes.size();
	if (!attributesAmount)
	{
		_attributes.emplace_back(attribute, 0);
		return;
	}

	const ConsoleTextAttribute lastAttribute = GetAttributeOfSegment(attributesAmount - 1);

	if (attribute == lastAttribute)
		return;

	_attributes.emplace_back(attribute, _text.size());
}

void MultiAttributedText::TryInsertAttribute(const ConsoleTextAttribute attribute, const int startIndex)
{
	AttributeStartIndexPair attributeStartIndexPair = AttributeStartIndexPair(attribute, startIndex);
	
	int previousAttributeIndex = GetAttributeStartPairIndexForCharacter(startIndex);
	
	if (GetAttributeOfSegment(previousAttributeIndex) == attribute)
		return;

	if (GetStartIndexOfSegment(previousAttributeIndex) == startIndex)
	{
		_attributes[previousAttributeIndex] = attributeStartIndexPair;
		return;
	}

	auto iterator = _attributes.begin() + previousAttributeIndex + 1;
	_attributes.insert(iterator, attributeStartIndexPair);
}

int MultiAttributedText::GetAttributeStartPairIndexForCharacter(const int charIndex) const
{
	for (int i = _attributes.size() - 1; i > 0; i--)
	{
		if (GetStartIndexOfSegment(i) <= charIndex)
			return i;
	}
	return 0;
}

void MultiAttributedText::PrintSegment(const int index) const
{
	std::string_view stringSegment = GetSegment(index);
	ConsoleTextAttribute attribute = GetAttributeOfSegment(index);

	attribute.Apply();
	std::cout << stringSegment;
}

int MultiAttributedText::GetStartIndexOfSegment(const int segmentIndex) const
{
	return _attributes[segmentIndex].StartIndex;
}

ConsoleTextAttribute MultiAttributedText::GetAttributeOfSegment(const int segmentIndex) const
{
	return _attributes[segmentIndex].Attribute;
}

std::string_view MultiAttributedText::GetSegment(const int index) const
{
	const unsigned int length = GetSegmentLength(index);
	const char* begin = _text.c_str() + GetStartIndexOfSegment(index);

	return std::string_view(begin, length);
}

unsigned int MultiAttributedText::GetSegmentLength(const int index) const
{
	const int lastAttributeIndex = _attributes.size() - 1;

	if (index == lastAttributeIndex)
		return _text.size() - GetStartIndexOfSegment(lastAttributeIndex);
	return GetStartIndexOfSegment(index + 1) - GetStartIndexOfSegment(index);
}

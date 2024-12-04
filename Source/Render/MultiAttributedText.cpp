#include "MultiAttributedText.h"
#include <iostream>

void MultiAttributedText::Print() const
{
	for (int i = 0; i < _attributes.size(); i++)
		PrintSegment(i);
}

void MultiAttributedText::SetAttributeForCharacter(const int index, const ConsoleTextAttribute attribute)
{
	if (index == _text.size() - 1)
		_attributes.emplace_back(attribute, index);

	const int characterInPairIndex = GetAttributeStartIndexPairForTextIndex(index);

	if (_attributes[characterInPairIndex].Attribute == attribute)
		return;

	auto iterator = _attributes.begin() + characterInPairIndex;

	_attributes.insert(iterator, AttributeStartIndexPair(attribute, index));
	_attributes.emplace(iterator, _attributes[characterInPairIndex]);
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

void MultiAttributedText::Reserve(const size_t size)
{
	_text.reserve(size);
}

void MultiAttributedText::Join(const MultiAttributedText& other)
{
	_text += other._text;
	
	const std::vector<AttributeStartIndexPair>& otherAttributes = other._attributes;
	
	_attributes.reserve(_attributes.size() + otherAttributes.size());
	_attributes.insert(_attributes.end(), otherAttributes.begin(), otherAttributes.end());
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

int MultiAttributedText::GetAttributeStartIndexPairForTextIndex(const int index) const
{
	const int attributesAmount = _attributes.size();

	for (int i = 1; i < attributesAmount; i++)
	{
		if (GetStartIndexOfSegment(i) >= index)
			return i - 1;
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

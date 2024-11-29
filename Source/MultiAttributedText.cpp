#include "MultiAttributedText.h"

void MultiAttributedText::Print() const
{
	for (int i = 0; i < _attributes.size(); i++)
		PrintSegment(i);
}

void MultiAttributedText::SetAttributeForCharacter(const int index, ConsoleTextAttribute attribute)
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

void MultiAttributedText::Append(ConsoleTextAttribute attribute, std::string text)
{
	const int lastAttributeIndex = _attributes.size() - 1;
	const ConsoleTextAttribute lastAttribute = _attributes[lastAttributeIndex].Attribute;

	_text += text;

	if (attribute == lastAttribute)
		return;

	_attributes.emplace_back(attribute, _text.size());
}

int MultiAttributedText::GetAttributeStartIndexPairForTextIndex(const int index) const
{
	const int attributesAmount = _attributes.size();

	for (int i = 1; i < attributesAmount; i++)
	{
		if (_attributes[i].StartIndex >= index)
			return i - 1;
	}
	return 0;
}

void MultiAttributedText::PrintSegment(const int index) const
{
	std::string_view stringSegment = GetSegment(index);
	ConsoleTextAttribute attribute = _attributes[index].Attribute;

	attribute.Apply();
	std::cout << stringSegment;
}

std::string_view MultiAttributedText::GetSegment(const int index) const
{
	const unsigned int length = GetSegmentLength(index);

	return std::string_view(_text.c_str(), length);
}

unsigned int MultiAttributedText::GetSegmentLength(const int index) const
{
	if (index >= _attributes.size() - 1)
		return _text.size();
	return _attributes[index + 1].StartIndex - _attributes[index].StartIndex;
}

#pragma once
#include <string>
#include "IRenderObject.h"

class RenderOfText final : public IRenderObject
{
    const std::string _text;
    const ConsoleTextAttribute _attribute;

    RenderOfText(const std::string& text, const ConsoleTextAttribute& attribute) :
        _text(text),
        _attribute(attribute)
    {}

    int EvaluateLength() override;

    MultiAttributedText GetAttributedText() override;
};
#pragma once
#include <string>
#include "IRenderObject.h"

class RenderOfText final : public IRenderObject
{
private:
    const std::string _text;
    const ConsoleTextAttribute _attribute;

public:
    RenderOfText(const std::string& text, const ConsoleTextAttribute& attribute) :
        _text(text),
        _attribute(attribute)
    {}

    int EvaluateLength() const override;

    MultiAttributedText RenderText() const override;
};
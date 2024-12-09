#pragma once
#include "IRenderObject.h"

class RenderOfInt final : IRenderObject
{
private:
    const int _number;
    const ConsoleTextAttribute _attribute;
    
public:
    RenderOfInt(const int number, const ConsoleTextAttribute& attribute) :
        _number(number),
        _attribute(attribute)
    {}

    int EvaluateLength() const override;

    MultiAttributedText RenderText() const override;
};

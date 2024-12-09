#include "RenderOfText.h"

int RenderOfText::EvaluateLength() const
{
    return _text.length();
}

MultiAttributedText RenderOfText::RenderText() const
{
    return {_attribute, _text};
}

#include "RenderOfText.h"

int RenderOfText::EvaluateLength()
{
    return _text.length();
}

MultiAttributedText RenderOfText::GetAttributedText()
{
    return {_attribute, _text};
}

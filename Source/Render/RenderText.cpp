#include "RenderText.h"

int RenderText::EvaluateLength()
{
    return _text.length();
}

MultiAttributedText RenderText::GetAttributedText()
{
    return {_attribute, _text};
}

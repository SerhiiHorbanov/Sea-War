#include "RenderOfInt.h"

constexpr int maxDigits = 10;// max value of int has 10 digits in base10 representation

int RenderOfInt::EvaluateLength() const
{
    int maxNumberWithCurrentDigitsAmount = 10;

    for (int digits = 0; digits < maxDigits; digits++)
    {
        maxNumberWithCurrentDigitsAmount *= 10;
        
        if (_number < maxNumberWithCurrentDigitsAmount)
            return digits;
    }
    
    return maxDigits;
}

MultiAttributedText RenderOfInt::RenderText() const
{
    std::string text = std::to_string(_number);
    return {_attribute, text};
}

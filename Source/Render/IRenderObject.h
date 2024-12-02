#pragma once
#include "MultiAttributedText.h"

class IRenderObject
{
public:
    virtual ~IRenderObject() = default;

    virtual int EvaluateLength() = 0;
    [[nodiscard]] virtual MultiAttributedText GetAttributedText() = 0;
};
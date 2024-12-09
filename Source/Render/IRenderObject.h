#pragma once
#include "MultiAttributedText.h"

class IRenderObject
{
public:
    virtual ~IRenderObject() = default;

    virtual int EvaluateLength() const = 0;
    [[nodiscard]] virtual MultiAttributedText RenderText() const = 0;
};
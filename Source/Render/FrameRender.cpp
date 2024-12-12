#include "FrameRender.h"

void FrameRender::Render()
{
    ReserveMemory();
    
    const int renderObjectsAmount = _renderObjects.size();
    for (int i = 0; i < renderObjectsAmount; i++)
        _text.Append(_renderObjects[i]->RenderText());
}

void FrameRender::Display() const
{
    std::system("cls");
    _text.Print();
}

void FrameRender::ReserveMemory()
{
    const int evaluatedLength = EvaluateImageLength(); 
    _text.Reserve(evaluatedLength);
}

int FrameRender::EvaluateImageLength() const
{
    int lengthsSum = 0;
    
    for (const std::shared_ptr each : _renderObjects)
        lengthsSum += each->EvaluateLength();

    return lengthsSum;
}

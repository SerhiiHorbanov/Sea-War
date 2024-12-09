#include "FrameRender.h"
#include <Windows.h>

const std::string CurrentPlayerMapText = "Your map:";
const std::string CurrentEnemyMapText = "Enemy map:";
const std::string GapBetweenMaps = "          ";
const std::string TipText = "press W/A/S/D to move. press E to shoot. press R to scan with radar\n";
const std::string PlayerRadarScansLeftText = "radar scans left:";

const ConsoleTextAttribute PlayerTextsAttribute = ConsoleTextAttribute();
const ConsoleTextAttribute MapTextAttribute = ConsoleTextAttribute();
const ConsoleTextAttribute PointedAtTileAttribute = ConsoleTextAttribute(ConsoleColor::Black, ConsoleColor::Red);//, false, false, false, false, true);
const ConsoleTextAttribute TipTextAttribute = ConsoleTextAttribute(ConsoleColor::LightGreen);

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

int FrameRender::EvaluateImageLength()
{
    int lengthsSum = 0;
    
    for (std::shared_ptr<const IRenderObject> each : _renderObjects)
        lengthsSum += each->EvaluateLength();

    return lengthsSum;
}
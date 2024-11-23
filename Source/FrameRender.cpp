#include "FrameRender.h"
#include <iostream>

const std::string CurrentPlayerMapText = "Your map:";
const std::string CurrentEnemyMapText = "Enemy map:";
const std::string GapBetweenMaps = "          ";
const std::string AskingPlayerWhereToShootText = "Where would you like to shoot?";

void FrameRender::ReserveMemory()
{
    const int lengthReserving = EvaluateImageLength();
    text.reserve(lengthReserving);
}

int FrameRender::EvaluateImageLength()
{
    int result = 0;

    result += CurrentPlayerMapText.length();
    result += CurrentEnemyMapText.length();
    result++;// newline
    result += GapBetweenMaps.length() * mapSize.second;// all the gaps between map rows
    result += mapSize.first * 2 * mapSize.second;// both map widths and newlines for each map row
    result += mapSize.second;// newlines between rows of maps
    result++;// newline
    result += AskingPlayerWhereToShootText.length();

    return result;
}

FrameRender FrameRender::Render(SeaMap& AttackingPlayer, SeaMap& AttackedPlayer)
{
    FrameRender result = FrameRender();

    result.ReserveMemory();
    result.AddPlayerTextsLine();
    result.AddPlayersMapsLines(AttackingPlayer, AttackedPlayer);

    return result;
}

void FrameRender::Display()
{
    std::system("cls");
    std::cout << text;
}

void FrameRender::AddPlayerTextsLine()
{
    text += CurrentPlayerMapText;
    const int GapBetweenPlayerTextsLength = mapSize.first + GapBetweenMaps.length() - CurrentPlayerMapText.length();
    text += std::string(GapBetweenPlayerTextsLength, ' ');
    text += CurrentEnemyMapText;
    text += '\n';
}

void FrameRender::AddPlayersMapsLines(SeaMap& AttackingPlayer, SeaMap& AttackedPlayer)
{
    for (int y = 0; y < mapSize.second; y++)
    {
        text += AttackingPlayer.GetMapRowText(y, false);
        text += GapBetweenMaps;
        text += AttackedPlayer.GetMapRowText(y, true);
        text += '\n';
    }
}
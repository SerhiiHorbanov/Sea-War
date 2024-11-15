#include "Render.h"
#include <iostream>

void Render()
{
    std::string image = GetImage();
    std::system("cls");
    std::cout << image;
}

std::string GetImage()
{
    std::string result;
    const int reserving = GetExpectedImageLength();
    result.reserve(reserving);
    
    result += CurrentPlayerMapText;
    const int GapBetweenPlayerTextsLength = mapSize.first + GapBetweenMaps.length() - CurrentPlayerMapText.length();
    result += std::string(GapBetweenPlayerTextsLength, ' ');
    result += CurrentEnemyMapText;
    result += '\n';

    for (int y = 0; y < mapSize.second; y++)
    {
        result += GetMapRowText(P1Map, y);
        result += GapBetweenMaps;
        result += GetMapRowText(P2Map, y);
        result += '\n';
    }

    return result;
}

int GetExpectedImageLength()
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

std::string GetMapRowText(const SeaMap seaMap, const int y)
{
    std::string result;
    result.reserve(seaMap.size.first);

    for (int x = 0; x < seaMap.size.first; x++)
    {
        std::pair<int, int> position = std::pair<int, int>(x, y);
        
        result += seaMap.GetTileChar(position);
    }

    return result;
}

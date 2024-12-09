#include "RenderOfSeaMap.h"

constexpr std::pair<char, char> TileTextures[] =
{
    {'~', '-'},// TileType::Sea
    {'W', 'x'},// TileType::Warship
};
constexpr char FogOfWarChar = '#';

const ConsoleTextAttribute MapTextAttribute = ConsoleTextAttribute();
const ConsoleTextAttribute PointedAtTileAttribute = ConsoleTextAttribute(ConsoleColor::Black, ConsoleColor::Red);

char GetTileChar(const Tile& tile, const bool fogOfWar)
{
    if (fogOfWar && !tile.WasShot)
        return FogOfWarChar;

    const auto [NotShotCharacter, ShotCharacter] = TileTextures[(int)tile.Type];

    return tile.WasShot ? ShotCharacter : NotShotCharacter;
}

char GetTileChar(const std::shared_ptr<const SeaMap> seaMap, const std::pair<int, int> position, bool fogOfWar)
{
    const Tile& tile = seaMap->GetTileConst(position);

    if (fogOfWar)
        fogOfWar &= seaMap->HasFogOfWarAtPosition(position);

    return GetTileChar(tile, fogOfWar);
}

MultiAttributedText GetMapRow(const std::shared_ptr<const SeaMap> seaMap, const std::pair<int, int> actionPosition, const int y, const bool fogOfWar)
{
    const int width = seaMap->size.first;
    
    MultiAttributedText result;
    
    for (int x = 0; x < width; x++)
    {
        std::pair position = std::pair(x, y);

        ConsoleTextAttribute attribute = MapTextAttribute;
        const char character = GetTileChar(seaMap, position, fogOfWar);
        
        result.Append(attribute, character);
    }

    if (y == actionPosition.second)
        result.SetAttributeForCharacter(actionPosition.first, PointedAtTileAttribute);

    return result;
}

int RenderOfSeaMap::EvaluateLength() const
{
    const int width = _seaMap->size.first + 1;// + 1 because '\n' is added on every row
    const int height = _seaMap->size.second;
    return width * height;
}

MultiAttributedText RenderOfSeaMap::RenderText() const
{
    const int height = _seaMap->size.second;

    MultiAttributedText result = MultiAttributedText();
    
    for (int y = 0; y < height; y++)
    {
        result.Append(GetMapRow(_seaMap, _actionPosition, y, _fogOfWar));
        result.Append(MapTextAttribute, '\n');
    }

    return result;
}

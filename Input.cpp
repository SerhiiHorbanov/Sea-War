#include "Input.h"
#include <iostream>
#include <sstream>
#include "SeaMap.h"

bool isValidShootingPosition;
std::pair<int, int> shootingPosition;

void Input()
{
    std::string input;
    std::getline(std::cin, input);

    ProcessInput(input);
}

void ProcessInput(const std::string& input)
{
    std::stringstream stream = std::stringstream(input);
    
    isValidShootingPosition = true;
    try
    {
        std::string numberText;
        std::getline(stream, numberText, ',');
        const int x = std::stoi(numberText) - 1;
        std::getline(stream, numberText);
        const int y = std::stoi(numberText) - 1;

        shootingPosition = std::pair<int, int>(x, y);
    }
    catch (std::exception exception)
    {
        isValidShootingPosition = false;
    }

    if (!AttackedPlayer->IsInBounds(shootingPosition))
        isValidShootingPosition = false;
}
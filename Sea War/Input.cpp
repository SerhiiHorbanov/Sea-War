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
    std::string numberText;
    
    isValidShootingPosition = true;
    try
    {
        std::getline(stream, numberText, ',');
        int x = std::stoi(numberText) - 1;
        std::getline(stream, numberText);
        int y = std::stoi(numberText) - 1;

        shootingPosition = std::pair<int, int>(x, y);
    }
    catch(std::invalid_argument exception)
    {
        isValidShootingPosition = false;
    }

    if (!AttackedPlayer->IsInBounds(shootingPosition))
        isValidShootingPosition = false;
}
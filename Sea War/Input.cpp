#include "Input.h"
#include <iostream>
#include <sstream>

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

    std::getline(stream, numberText, ',');
    int x = std::stoi(numberText);
    std::getline(stream, numberText);
    int y = std::stoi(numberText);

    shootingPosition = std::pair<int, int>(x, y);
}
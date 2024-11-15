#pragma once
#include <string>
#include "SeaMap.h"

const std::string CurrentPlayerMapText = "Your map:";
const std::string CurrentEnemyMapText = "Enemy map:";
const std::string GapBetweenMaps = "          ";
const std::string AskingPlayerWhereToShootText = "Where would you like to shoot?";

void Render();

std::string GetImage();
int EvaluateImageLength();
std::string GetMapRowText(const SeaMap& seaMap, const int y);
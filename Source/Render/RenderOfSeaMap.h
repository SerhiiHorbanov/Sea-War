#pragma once
#include <memory>
#include "IRenderObject.h"
#include "../SeaMap.h"

class RenderOfSeaMap : IRenderObject
{
private:
	const std::shared_ptr<const SeaMap> _seaMap;
	const bool _fogOfWar;
	const std::pair<int, int> _actionPosition;

public:
	RenderOfSeaMap(const std::shared_ptr<const SeaMap>& seaMap, const bool fogOfWar, const std::pair<int, int>& actionPosition) :
		_seaMap(seaMap),
		_fogOfWar(fogOfWar),
		_actionPosition(actionPosition)
	{}

	int EvaluateLength() const override;

	MultiAttributedText RenderText() const override;
};

#pragma once
#include "DEFINITIONS.h"

class State 
{
public:
	virtual void Init() = 0;
	virtual void HandleInput() = 0;
	virtual void Update(float dt) = 0;
	virtual void Draw() = 0;
};
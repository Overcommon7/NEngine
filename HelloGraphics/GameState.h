#pragma once

#include <../NEngine/Inc/NEngine.h>

class GameState : public NEng::AppState    
{
	void Initialize() override;
	void Update(float deltaTime) override;
};


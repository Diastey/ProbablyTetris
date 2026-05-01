#pragma once
#include "BaseScene.h"

class MainScene :public BaseScene
{
public:
	MainScene(int fps);

	bool Initialize() override;
	void Update(int frames) override;
	void Render() override;
	void Release() override;
};


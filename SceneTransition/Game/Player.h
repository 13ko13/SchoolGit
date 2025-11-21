#pragma once

#include "Actor.h"

class Input;
class Enemy;
/// <summary>
/// プレイヤーのクラス
/// </summary>
class Player : public Actor
{
	Enemy* enemy_;
public:
	void Update();
	void Draw();
};


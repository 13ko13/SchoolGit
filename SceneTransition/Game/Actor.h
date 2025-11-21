#pragma once

#include "../Geometry.h"
/// <summary>
/// 配置可能なゲームオブジェクトの基底クラス
/// </summary>
class Actor 
{
protected:
	Position2 pos_;
public:
	virtual void Update()abstract;
	virtual void Draw()abstract;
	virtual ~Actor() {};
	const Position2& GetPos() const;
};


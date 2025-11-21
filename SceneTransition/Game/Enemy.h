#pragma once

#include <memory>
#include "../Geometry.h"
#include "Actor.h"
//プレイヤー
class Player;
//弾生産工場
class BulletFactory;
/// <summary>
/// 敵の基底クラス
/// </summary>
class Enemy : public Actor
{
protected:
	Circle circle_;
	std::shared_ptr<Player> player_;//プレイヤーを持っておく(自機狙い弾等を出すため)
	std::shared_ptr<BulletFactory> bulletFactory_;
private:
	
public: 
	/// <summary>
	/// 敵基底クラスのコンストラクタ
	/// </summary>
	/// <param name="player">プレイヤーのポインタ</param>
	/// <param name="bf">弾生産工場のポインタのポインタ</param>
	/// <param name="pos">敵の初期座標</param>
	/// <param name="r">敵の半径</param>
	Enemy(std::shared_ptr<Player> player,std::shared_ptr<BulletFactory> bf,
		const Position2& pos,float r);
	virtual void OnHit(const Actor& actor) abstract;
	virtual void Update() abstract;
	virtual void Draw() abstract;
	virtual ~Enemy() {};
};


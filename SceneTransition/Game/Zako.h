#pragma once
#include "Enemy.h"

/// <summary>
/// 雑魚クラス
/// </summary>
class Zako : public Enemy
{
private:
	int handle_;//画像ハンドル
	int frame_;//経過フレーム
public:
	/// <summary>
	/// 雑魚のコンストラクタ
	/// </summary>
	/// <param name="player">プレイヤーのポインタ</param>
	/// <param name="pos">初期座標</param>
	Zako(int handle,std::shared_ptr<Player> player,std::shared_ptr<BulletFactory> bf, 
		const Position2& pos);
	/// <summary>
	/// 雑魚の座標等更新
	/// </summary>
	void Update() override;
	void Draw() override;
	void OnHit(const Actor& actor)override;
};


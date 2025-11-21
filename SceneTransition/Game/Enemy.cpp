#include "Enemy.h"

Enemy::Enemy(std::shared_ptr<Player> player, 
	std::shared_ptr<BulletFactory> bf, 
	const Position2& pos, float r) :
	player_(player),bulletFactory_(bf),circle_{pos,r}
{
	pos_ = pos;
}//プレイヤーを持っておく(自機狙い弾等を出すため)
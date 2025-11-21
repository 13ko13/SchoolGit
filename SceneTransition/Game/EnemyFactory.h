#pragma once
#include <memory>
#include <list>
#include <vector>

class Enemy;
class Player;
class BulletFactory;

/// <summary>
/// 敵タイプ
/// </summary>
enum class EnemyType
{
	none,//敵なし
	zako,//雑魚
	patapata,//パタパタ
	strider//ストライダー
};

/// <summary>
/// 敵生産工場
/// </summary>
class EnemyFactory
{
private:
	std::vector<int> handles_;//敵全員のハンドルを持っておく
	std::shared_ptr<Player> player_;//Enemyに渡すプレイヤーのポインタ
	std::shared_ptr<BulletFactory> bulletFactory;//Enemyに渡す弾生産工場のポインタ
	std::list<std::shared_ptr<Enemy>> enemies_;//管理すべき敵集合
public:
	EnemyFactory(std::shared_ptr<BulletFactory> bf);
	std::shared_ptr<Enemy> Create(int idxX,int idxY,EnemyType enemyType,std::shared_ptr<Player> player);
	std::list<std::shared_ptr<Enemy>>& GetEnemies();
	void Update();
	void Draw();
};


#pragma once
#include "../Scene.h"
#include "../Geometry.h"
#include <memory>

class Stage;
class GameScene : public  Scene
{
private:
	//プレイヤー情報
	Circle player_ = { {0.0f,0.0f},10.0f };//プレイヤーの座標
	int playerExplosionFrame_ = 0;
	//弾構造体(後で別のクラスに分ける)
	struct Bullet
	{
		Circle circle = { {},3.0f };//弾の座標
		Position2 shotVel;//弾の速度
		bool isDead = true;//無効になってる
	};
	Bullet shots_[32];	//プレイヤーの弾

	//敵情報
	Circle enemy_ = { {0.0f,0.0f},10.0f };//敵の座標
	int enemyExplosionFrame = 0;
	Position2 enemyVel_;//敵の速度
	Bullet bullets_[128];//敵の弾

	std::shared_ptr<Stage> stage_;//ステージデータ

	int playerH_;//プレイヤー画像(4x2)
	int shotH_;//プレイヤーの弾(敵の弾も兼用)
	int zakoH_;//雑魚敵の画像
	int papataH_;//パタパタ敵の画像
	int explosionH_;//爆発画像

	int backH_;//1枚絵
	int cloudH_;//多重スクロール用雲画像

	int frame_ = 0;//フェードインアウト用
	int gameFrame_ = 0;//ゲーム中のフレームをカウント

	void FadeInUpdate(Input&);
	void NormalUpdate(Input& input);
	void FadeOutUpdate(Input&);
	using UpdateFunc_t = void(GameScene::*)(Input&);
	UpdateFunc_t update_;//Update系を受け取るメンバ関数ポインタ

	void FadeDraw();
	void NormalDraw();
	using DrawFunc_t = void(GameScene::*)();
	DrawFunc_t draw_;//Draw系を受け取るメンバ関数ポインタ
	bool IsHit(const Circle& a, const Circle& b);
public:
	GameScene(SceneController& controller);
	void Update(Input&)override;
	void Draw()override;
};


#pragma once
#include "Scene.h"
#include "Geometry.h"

class GameScene : public  Scene
{
private:
	//プレイヤー情報
	Position2 playerPos;//プレイヤーの座標
	//弾構造体(後で別のクラスに分ける)
	struct Bullet
	{
		Position2 shotPos;//弾の座標
		Position2 shotVel;//弾の速度
		bool isDead = true;//無効になってる
	};
	Bullet shots_[32];	//プレイヤーの弾

	//敵情報
	Position2 enemyPos_;//敵の座標
	Position2 enemyVel_;//敵の速度
	Bullet bullets_[128];//敵の弾

	int playerH_;//プレイヤー画像(4x2)
	int shotH_;//プレイヤーの弾(敵の弾も兼用)
	int enemyH_;//雑魚敵の画像

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

public:
	GameScene(SceneController& controller);
	void Update(Input&)override;
	void Draw()override;
};


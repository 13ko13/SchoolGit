#include "GameScene.h"
#include <DxLib.h>
#include "Input.h"
#include "GameoverScene.h"
#include "SceneController.h"
#include <cassert>
#include "Application.h"
#include <cmath>

constexpr int player_cut_w = 16;
constexpr int player_cut_h = 24;
constexpr int bullet_cut_w = 16;
constexpr int bullet_cut_h = 16;
constexpr int exp_cut_w = 16;
constexpr int exp_cut_h = 16;

constexpr int fade_interval = 60;
constexpr float player_speed = 4.0f;	//プレイヤーの移動速度
constexpr float player_shot_speed = 8.0f;//プレイヤーの弾の速度
constexpr float player_scale = 2.0f;	//プレイヤー画像のスケーリング
constexpr int explosion_frame = 30;//爆発に要するフレーム数
constexpr float exp_scale = 4.0f;//爆発スケール

constexpr float enemy_speed = 2.0f;	//敵の移動速度
constexpr float enemy_bullet_speed = 4.0f;//敵の弾の速度
constexpr int enemy_cut_w = 16;
constexpr int enemy_cut_h = 16;
constexpr float enemy_scale = 2.5f;

/// <summary>
/// 2つの円が交差しているかどうかを返す
/// </summary>
/// <param name="a">円a</param>
/// <param name="b">円b</param>
/// <returns>当たってたらtrue / 当たってないならfalse</returns>
bool GameScene::IsHit(const Circle& a, const Circle& b)
{
	//①円aの中心から円bの中心へベクトルを引く
	auto vec = b.pos - a.pos;
	//②①で作ったベクトルの大きさをはかる
	float d = vec.Length();
	//③その大きさがそれぞれの円の半径を足したものより大きければ
	//当たっていない
	return d<=a.r + b.r;
}

GameScene::GameScene(SceneController& controller) :
	Scene(controller), player_{ { 320,400 },10.0f },
	enemy_{ {0,50},10.0f },
	enemyVel_{ enemy_speed,0 },
	update_(&GameScene::FadeInUpdate),
	draw_(&GameScene::FadeDraw),
	shots_{},
	bullets_{}
{
	//画像をロード
	playerH_ = LoadGraph(L"img/game/player.png");
	assert(playerH_ >= 0);

	shotH_ = LoadGraph(L"img/game/bullet.png");
	assert(shotH_ >= 0);

	backH_ = LoadGraph(L"img/game/background.png");
	assert(backH_ >= 0);

	cloudH_ = LoadGraph(L"img/game/cloud.png");
	assert(cloudH_ >= 0);

	enemyH_ = LoadGraph(L"img/game/zako.png");
	assert(enemyH_ >= 0);

	explosionH_ = LoadGraph(L"img/game/explosion.png");
	assert(explosionH_ >= 0);

	frame_ = fade_interval;
}

void GameScene::FadeInUpdate(Input&)
{
	if (--frame_ <= 0)
	{
		update_ = &GameScene::NormalUpdate;
		draw_ = &GameScene::NormalDraw;
		return;
	}
}

void GameScene::NormalUpdate(Input& input)
{

	if (input.IsTriggerd("ok"))
	{
		update_ = &GameScene::FadeOutUpdate;
		draw_ = &GameScene::FadeDraw;
		return;
	}
	Vector2 vel = { 0.0f,0.0f };//プレイヤーの速度ベクトル
	if (input.IsPressed("up"))
	{
		vel.y = -1.0f;
	}
	if (input.IsPressed("right"))
	{
		vel.x = 1.0f;
	}
	if (input.IsPressed("down"))
	{
		vel.y = 1.0f;
	}
	if (input.IsPressed("left"))
	{
		vel.x = -1.0f;
	}
	//爆発中は死んでるから動けない
	if (playerExplosionFrame_ == 0)
	{
		player_.pos += vel.Normalized() * player_speed;
	}
	

	//プレイヤーの弾の制御
	if (input.IsTriggerd("shot"))
	{
		for (auto& shot : shots_)
		{
			//弾発射の儀
			if (shot.isDead)
			{
				shot.isDead = false;//弾の復活
				shot.circle.pos = player_.pos;//弾の開始地点
				shot.shotVel = { 0.0f,-player_shot_speed };//弾の速度
				break;
			}
		}
	}
	const auto& wsize = Application::GetInstance().GetWindowSize();
	//敵の動きの制御
	enemy_.pos += enemyVel_;
	if ((enemyVel_.x > 0.0f && enemy_.pos.x > wsize.w - enemy_cut_w * enemy_scale / 2.0f) ||
		(enemyVel_.x < 0.0f && enemy_.pos.x < enemy_cut_w * enemy_scale / 2.0f))
	{
		enemyVel_.x = -enemyVel_.x;
	}
	//敵の弾の制御(自機狙い弾)
	++gameFrame_;
	if (gameFrame_ < 120) {
		if (gameFrame_ % 20 == 0) {
			//20フレームに１発弾を打つ
			for (auto& bullet : bullets_) {
				//敵弾発射の儀
				if (bullet.isDead) {
					bullet.isDead = false;
					bullet.circle.pos = enemy_.pos;
					bullet.shotVel = (player_ .pos- enemy_.pos).Normalized() * enemy_bullet_speed;//自機狙い弾
					break;
				}
			}
		}
	}
	else {//n-wayショット
		if (gameFrame_ % 20 == 0) {
			//20フレームに１発弾を打つ
			//真ん中は自機狙い
			//両隣は30度左右に分かれてるとします
			constexpr int way_num = 5;//何wayか
			constexpr float angle_30 = DX_PI_F / 6.0f;
			//一旦自機狙いの角度を計算します
			auto vec = player_.pos - enemy_.pos;//自機狙いベクトル
			auto theta = atan2(vec.y, vec.x) - angle_30*(way_num/2);
			int count = 0;
			for (auto& bullet : bullets_) {
				//敵弾発射の儀
				if (bullet.isDead) {
					bullet.isDead = false;
					bullet.circle.pos = enemy_.pos;
					bullet.shotVel = { cos(theta),sin(theta) };
					bullet.shotVel *= enemy_bullet_speed;
					theta += angle_30;
					++count;
				}
				if (count == way_num)
				{
					break;
				}
			}
		}
	}

	//プレイヤー弾の座標の更新
	for (auto& shot : shots_)
	{
		if (!shot.isDead)
		{
			shot.circle.pos += shot.shotVel;
			if (shot.circle.pos.y < -bullet_cut_h * player_scale)
			{
				shot.isDead = true;//画面買いに出たらまた無効にする(再利用可能にする)
				continue;
			}
			//プレイヤー弾と敵の当たり判定
			if (IsHit(shot.circle, enemy_))
			{
				shot.isDead = true;
				enemyExplosionFrame = explosion_frame;
			}
		}
	}
	enemyExplosionFrame = max(enemyExplosionFrame - 1, 0);

	//敵の弾の座標更新
	for (auto& bullet : bullets_)
	{
		if (bullet.isDead)continue;
		bullet.circle.pos += bullet.shotVel;
		if (bullet.circle.pos.x < -32 || bullet.circle.pos.x > wsize.w + 32 ||
			bullet.circle.pos.y < -32 || bullet.circle.pos.y > 480 + 32)
		{
			//弾は画面外に出たら死ぬ
			bullet.isDead = true;
			continue;
		}
		//敵の弾と自機の当たり判定
		if (playerExplosionFrame_ == 0) {
			if (IsHit(bullet.circle, player_))
			{
				bullet.isDead = true;
				playerExplosionFrame_ = explosion_frame;
			}
		}
	}
	playerExplosionFrame_ = max(playerExplosionFrame_ - 1, 0);
}

void GameScene::FadeOutUpdate(Input&)
{
	if (++frame_ >= fade_interval)
	{
		//以下の行を実行した時点でGameSceneは消滅します
		controller_.ChangeScene(std::make_shared<GameoverScene>(controller_));
		//もう死んでるのでreturn以外のコードを実行してはいけない
		return;//もうChangeSceneした直後にreturnする癖をつけておく
	}
}

void GameScene::FadeDraw()
{
	//背景
	DrawExtendGraph(0, 0, 640, 480, backH_, false);
	//自機表示
	DrawRectRotaGraph(player_.pos.x, player_.pos.y,
		player_cut_w * 2.0, player_cut_h * 0,
		player_cut_w, player_cut_h,
		player_scale, 0.0f, playerH_, true);
	float rate = static_cast<float>(frame_) / static_cast<float>(fade_interval);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 * rate);
	DrawBox(0, 0, 640, 480, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void GameScene::NormalDraw()
{
	const auto& wsize = Application::GetInstance().GetWindowSize();
	constexpr int cloud_height = 160;
	int cloudYOffset = (gameFrame_ * 5) %wsize.h;//雲
	int bgYOffset = (gameFrame_ * 2) % wsize.h;//画面の高さ分進んだらオフセット座標をリセット
	//背景(永遠スクロールの場合必要な枚数は、一度に表示する枚数+1)
	//↓０フレームの時は、画面上に映っていません
	DrawExtendGraph(0, -wsize.h + bgYOffset, wsize.w, 0 + bgYOffset, backH_, false);
	//常に映っているけれども画面の高さ分進んだ時点で見えなくなる
	DrawExtendGraph(0, 0 + bgYOffset, wsize.w, wsize.h + bgYOffset, backH_, false);

	//雲
	//↓０フレームの時は、画面上に映っていません
	DrawExtendGraph(
		0, -cloud_height + cloudYOffset - wsize.h, wsize.w, cloud_height + cloudYOffset - wsize.h, cloudH_, true);
	//常に映っているけれども画面の高さ分進んだ時点で見えなくなる
	DrawExtendGraph(0, 0 + cloudYOffset, wsize.w, cloud_height + cloudYOffset, cloudH_, true);

	int shotImgIdx = (gameFrame_ / 5) % 2;
	//弾表示
	for (auto& shot : shots_)
	{
		if (shot.isDead) continue;
		DrawRectRotaGraph(shot.circle.pos.x,shot.circle.pos.y,//表示座標
			bullet_cut_w * shotImgIdx, bullet_cut_h * 1,//切り取りの左上
			bullet_cut_w, bullet_cut_h,//切り取りの幅　高
			player_scale, 0.0f, shotH_, true);
	}
	int playerImgIdx = (gameFrame_ / 8) % 2;
	//自機表示
	if (playerExplosionFrame_ == 0)
	{
		//爆発していないときだけ表示
		DrawRectRotaGraph(player_.pos.x, player_.pos.y,//プレイヤーの表示座標
			player_cut_w * 2, player_cut_h * playerImgIdx,//切り取りの左上
			player_cut_w, player_cut_h,//切り取りの幅　高
			player_scale, 0.0f, playerH_, true);
	}
	
	//爆発表示
	if (playerExplosionFrame_ > 0)
	{
		int idx = 4 - (playerExplosionFrame_ / 6);
		DrawRectRotaGraph(player_.pos.x, player_.pos.y,//プレイヤーの表示座標
			exp_cut_w * idx, 0,
			exp_cut_w, exp_cut_h,
			exp_scale, 0.0f, explosionH_, true);
	}

	//敵弾表示
	for (auto& bullet : bullets_)
	{
		if (bullet.isDead) continue;
		DrawRectRotaGraph(bullet.circle.pos.x,bullet.circle.pos.y,
			bullet_cut_w * shotImgIdx, bullet_cut_h * 0,
			bullet_cut_w, bullet_cut_h,
			player_scale, 0.0f, shotH_, true);
	}

	int enemyImgIdx = (gameFrame_ / 6) % 2;
	//敵表示
	DrawRectRotaGraph(enemy_.pos.x, enemy_.pos.y,
		enemy_cut_w * enemyImgIdx, enemy_cut_h * 0,
		enemy_cut_w, enemy_cut_h,
		enemy_scale, 0.0f, enemyH_, true);

	//敵爆発表示
	int enemyExpOffsetX = GetRand(10) - 5;
	int enemyExpOffsetY = GetRand(10) - 5;
	
	if (enemyExplosionFrame > 0)
	{
		int idx = 4 - (enemyExplosionFrame / 6);
		DrawRectRotaGraph(enemy_.pos.x + enemyExpOffsetX, enemy_.pos.y + enemyExpOffsetY,//プレイヤーの表示座標
			exp_cut_w * idx, 0,
			exp_cut_w, exp_cut_h,
			exp_scale, 0.0f, explosionH_, true);
	}
}

void GameScene::Update(Input& input)
{
	(this->*update_)(input);
}

void GameScene::Draw()
{
	(this->*draw_)();
}

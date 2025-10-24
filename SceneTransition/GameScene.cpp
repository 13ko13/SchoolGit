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
constexpr int fade_interval = 60;
constexpr float player_speed = 4.0f;	//�v���C���[�̈ړ����x

constexpr float player_shot_speed = 8.0f;//�v���C���[�̒e�̑��x

constexpr float enemy_speed = 2.0f;	//�G�̈ړ����x
constexpr float enemy_bullet_speed = 4.0f;//�G�̒e�̑��x
constexpr int enemy_cut_w = 16;
constexpr int enemy_cut_h = 16;
constexpr float enemy_scale = 2.5f;

constexpr float player_scale = 2.0f;	//�v���C���[�摜�̃X�P�[�����O

GameScene::GameScene(SceneController& controller) :
	Scene(controller), playerPos{ 320,400 },
	enemyPos_{ 0,50 },
	enemyVel_{ enemy_speed,0 },
	update_(&GameScene::FadeInUpdate),
	draw_(&GameScene::FadeDraw),
	shots_{},
	bullets_{}
{
	//�摜�����[�h
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
	Vector2 vel = { 0.0f,0.0f };//�v���C���[�̑��x�x�N�g��
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
	playerPos += vel.Normalized() * player_speed;

	//�v���C���[�̒e�̐���
	if (input.IsTriggerd("shot"))
	{
		for (auto& shot : shots_)
		{
			//�e���˂̋V
			if (shot.isDead)
			{
				shot.isDead = false;//�e�̕���
				shot.shotPos = playerPos;//�e�̊J�n�n�_
				shot.shotVel = { 0.0f,-player_shot_speed };//�e�̑��x
				break;
			}
		}
	}
	//�v���C���[�e�̍��W�̍X�V
	for (auto& shot : shots_)
	{
		if (!shot.isDead)
		{
			shot.shotPos += shot.shotVel;
			if (shot.shotPos.y < -bullet_cut_h * player_scale)
			{
				shot.isDead = true;//��ʔ����ɏo����܂������ɂ���(�ė��p�\�ɂ���)
			}
		}
	}
	const auto& wsize = Application::GetInstance().GetWindowSize();
	//�G�̓����̐���
	enemyPos_ += enemyVel_;
	if ((enemyVel_.x > 0.0f && enemyPos_.x > wsize.w - enemy_cut_w * enemy_scale / 2.0f) ||
		(enemyVel_.x < 0.0f && enemyPos_.x < enemy_cut_w * enemy_scale / 2.0f))
	{
		enemyVel_.x = -enemyVel_.x;
	}
	//�G�̒e�̐���(���@�_���e)
	++gameFrame_;
	if (gameFrame_ < 120) {
		if (gameFrame_ % 20 == 0) {
			//20�t���[���ɂP���e��ł�
			for (auto& bullet : bullets_) {
				//�G�e���˂̋V
				if (bullet.isDead) {
					bullet.isDead = false;
					bullet.shotPos = enemyPos_;
					bullet.shotVel = (playerPos - enemyPos_).Normalized() * enemy_bullet_speed;//���@�_���e
					break;
				}
			}
		}
	}
	else {//n-way�V���b�g
		if (gameFrame_ % 20 == 0) {
			//20�t���[���ɂP���e��ł�
			//�^�񒆂͎��@�_��
			//���ׂ�30�x���E�ɕ�����Ă�Ƃ��܂�
			constexpr int way_num = 5;//��way��
			constexpr float angle_30 = DX_PI_F / 6.0f;
			//��U���@�_���̊p�x���v�Z���܂�
			auto vec = playerPos - enemyPos_;//���@�_���x�N�g��
			auto theta = atan2(vec.y, vec.x) - angle_30*(way_num/2);
			int count = 0;
			for (auto& bullet : bullets_) {
				//�G�e���˂̋V
				if (bullet.isDead) {
					bullet.isDead = false;
					bullet.shotPos = enemyPos_;
					//bullet.shotVel = (playerPos - enemyPos_).Normalized() * enemy_bullet_speed;//���@�_���e
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
	//�G�̒e�̍��W�X�V
	for (auto& bullet : bullets_)
	{
		if (bullet.isDead)continue;
		bullet.shotPos += bullet.shotVel;
		if (bullet.shotPos.x < -32 || bullet.shotPos.x > wsize.w + 32 ||
			bullet.shotPos.y < -32 || bullet.shotPos.y > 480 + 32)
		{
			//�e�͉�ʊO�ɏo���玀��
			bullet.isDead = true;
		}
	}

}

void GameScene::FadeOutUpdate(Input&)
{
	if (++frame_ >= fade_interval)
	{
		//�ȉ��̍s�����s�������_��GameScene�͏��ł��܂�
		controller_.ChangeScene(std::make_shared<GameoverScene>(controller_));
		//��������ł�̂�return�ȊO�̃R�[�h�����s���Ă͂����Ȃ�
		return;//����ChangeScene���������return����Ȃ����Ă���
	}
}

void GameScene::FadeDraw()
{
	//�w�i
	DrawExtendGraph(0, 0, 640, 480, backH_, false);
	//���@�\��
	DrawRectRotaGraph(playerPos.x, playerPos.y,
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
	int cloudYOffset = (gameFrame_ * 5) %wsize.h;//�_
	int bgYOffset = (gameFrame_ * 2) % wsize.h;//��ʂ̍������i�񂾂�I�t�Z�b�g���W�����Z�b�g
	//�w�i(�i���X�N���[���̏ꍇ�K�v�Ȗ����́A��x�ɕ\�����閇��+1)
	//���O�t���[���̎��́A��ʏ�ɉf���Ă��܂���
	DrawExtendGraph(0, -wsize.h + bgYOffset, wsize.w, 0 + bgYOffset, backH_, false);
	//��ɉf���Ă��邯��ǂ���ʂ̍������i�񂾎��_�Ō����Ȃ��Ȃ�
	DrawExtendGraph(0, 0 + bgYOffset, wsize.w, wsize.h + bgYOffset, backH_, false);

	//�_
	//���O�t���[���̎��́A��ʏ�ɉf���Ă��܂���
	DrawExtendGraph(
		0, -cloud_height + cloudYOffset - wsize.h, wsize.w, cloud_height + cloudYOffset - wsize.h, cloudH_, true);
	//��ɉf���Ă��邯��ǂ���ʂ̍������i�񂾎��_�Ō����Ȃ��Ȃ�
	DrawExtendGraph(0, 0 + cloudYOffset, wsize.w, cloud_height + cloudYOffset, cloudH_, true);

	int shotImgIdx = (gameFrame_ / 5) % 2;
	//�e�\��
	for (auto& shot : shots_)
	{
		if (shot.isDead) continue;
		DrawRectRotaGraph(shot.shotPos.x,shot.shotPos.y,//�\�����W
			bullet_cut_w * shotImgIdx, bullet_cut_h * 1,//�؂���̍���
			bullet_cut_w, bullet_cut_h,//�؂���̕��@��
			player_scale, 0.0f, shotH_, true);

	}
	int playerImgIdx = (gameFrame_ / 8) % 2;
	//���@�\��
	DrawRectRotaGraph(playerPos.x, playerPos.y,//�v���C���[�̕\�����W
		player_cut_w * 2, player_cut_h * playerImgIdx,//�؂���̍���
		player_cut_w, player_cut_h,//�؂���̕��@��
		player_scale, 0.0f, playerH_, true);

	//�G�e�\��
	for (auto& bullet : bullets_)
	{
		if (bullet.isDead) continue;
		DrawRectRotaGraph(bullet.shotPos.x,bullet.shotPos.y,
			bullet_cut_w * shotImgIdx, bullet_cut_h * 0,
			bullet_cut_w, bullet_cut_h,
			player_scale, 0.0f, shotH_, true);
	}
	int enemyImgIdx = (gameFrame_ / 6) % 2;
	//�G�\��
	DrawRectRotaGraph(enemyPos_.x, enemyPos_.y,
		enemy_cut_w * enemyImgIdx, enemy_cut_h * 0,
		enemy_cut_w, enemy_cut_h,
		enemy_scale, 0.0f, enemyH_, true);
}

void GameScene::Update(Input& input)
{
	(this->*update_)(input);
}

void GameScene::Draw()
{
	(this->*draw_)();
}

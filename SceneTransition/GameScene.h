#pragma once
#include "Scene.h"
#include "Geometry.h"

class GameScene : public  Scene
{
private:
	//�v���C���[���
	Circle player_ = { {0.0f,0.0f},10.0f };//�v���C���[�̍��W
	int playerExplosionFrame_ = 0;
	//�e�\����(��ŕʂ̃N���X�ɕ�����)
	struct Bullet
	{
		Circle circle = { {},3.0f };//�e�̍��W
		Position2 shotVel;//�e�̑��x
		bool isDead = true;//�����ɂȂ��Ă�
	};
	Bullet shots_[32];	//�v���C���[�̒e

	//�G���
	Circle enemy_ = { {0.0f,0.0f},10.0f };//�G�̍��W
	int enemyExplosionFrame = 0;
	Position2 enemyVel_;//�G�̑��x
	Bullet bullets_[128];//�G�̒e

	int playerH_;//�v���C���[�摜(4x2)
	int shotH_;//�v���C���[�̒e(�G�̒e�����p)
	int enemyH_;//�G���G�̉摜
	int explosionH_;//�����摜

	int backH_;//1���G
	int cloudH_;//���d�X�N���[���p�_�摜

	int frame_ = 0;//�t�F�[�h�C���A�E�g�p
	int gameFrame_ = 0;//�Q�[�����̃t���[�����J�E���g

	void FadeInUpdate(Input&);
	void NormalUpdate(Input& input);
	void FadeOutUpdate(Input&);
	using UpdateFunc_t = void(GameScene::*)(Input&);
	UpdateFunc_t update_;//Update�n���󂯎�郁���o�֐��|�C���^

	void FadeDraw();
	void NormalDraw();
	using DrawFunc_t = void(GameScene::*)();
	DrawFunc_t draw_;//Draw�n���󂯎�郁���o�֐��|�C���^
	bool IsHit(const Circle& a, const Circle& b);
public:
	GameScene(SceneController& controller);
	void Update(Input&)override;
	void Draw()override;
};


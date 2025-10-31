#include "SceneController.h"
#include "Scene.h"

void SceneController::ResetScene(std::shared_ptr<Scene> scene)
{
	//�V�[�����P�����ɂ��������߁A��U�V�[�������ׂăN���A���܂�
	scenes_.clear();
	scenes_.push_back(scene);
}

void SceneController::ChangeScene(std::shared_ptr<Scene> scene)
{
	//�����A���X�g���J���̏ꍇ�A���ʂɑ����ChangeScene���悤�Ƃ����
	//���Rempty�̔��ɑ΂���Change���悤�Ƃ���̂ŁA�N���b�V�����܂�
	//���̂��߁A�ŏ���empty���ǂ������`�F�b�N���܂�
	if (scenes_.empty())
	{
		//�ŏ��͗v�f���Ȃ�����
		//����ۂ̏ꍇ�ɂ͎w��̗v�f��push���܂�
		//���Ȃ��Ƃ�1�͐ς܂�Ă����Ԃɂ���
		scenes_.push_back(scene);
	}
	else
	{
		scenes_.back() = scene;
	}
}

void SceneController::PushScene(std::shared_ptr<Scene> scene)
{
	//�V�����V�[���𖖔��ɐς݂܂�(������ςށH)
	scenes_.push_back(scene);
}

void SceneController::PopScene()
{
	//�����̃V�[�����폜���܂�
	scenes_.pop_back();
}

void SceneController::Update(Input& input)
{
	//�����̗v�f�ɑ΂���Update����
	scenes_.back()->Update(input);
}

void SceneController::Draw()
{
	//Update�����~�߂Ă��ׂ�Draw
	//�|�[�Y�����Ƃ��Ƀv���C�w�i�͎c��
	for (auto& scene : scenes_)
	{
		scene->Draw();
	}
}
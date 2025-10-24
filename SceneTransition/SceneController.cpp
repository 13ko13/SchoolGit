#include "SceneController.h"
#include "Scene.h"

void SceneController::ChangeScene(std::shared_ptr<Scene> scene)
{
	//scene������ꂽ�ۂɁA���X�ʂ̃V�[����scene_�ɓ����Ă�����
	//���Ƃ��Ƃ�scene_�̎Q�Ɛ���Q�Ƃ���I�u�W�F�N�g�����Ȃ��Ȃ邽��
	// ���Ƃ�scene_�͎����I�ɍ폜����܂�
	if (scenes_.empty())
	{
		scenes_.push_back(scene);
	}
	else
	{
		scenes_.back() = scene;
	}
}

void SceneController::PushScene(std::shared_ptr<Scene> scene)
{
}

void SceneController::PopScene()
{
}

void SceneController::Update(Input& input)
{
	scenes_.back()->Update(input);
}

void SceneController::Draw()
{
	scenes_.back()->Draw();
}
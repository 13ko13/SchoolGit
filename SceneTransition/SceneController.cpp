#include "SceneController.h"
#include "Scene.h"

void SceneController::ChangeScene(std::shared_ptr<Scene> scene)
{
	//scene������ꂽ�ۂɁA���X�ʂ̃V�[����scene_�ɓ����Ă�����
	//���Ƃ��Ƃ�scene_�̎Q�Ɛ���Q�Ƃ���I�u�W�F�N�g�����Ȃ��Ȃ邽��
	// ���Ƃ�scene_�͎����I�ɍ폜����܂�
	scene_ = scene;
}

void SceneController::Update(Input& input)
{
	scene_->Update(input);
}

void SceneController::Draw()
{
	scene_->Draw();
}
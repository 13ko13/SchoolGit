#include "Application.h"
#include <DxLib.h>
#include <cassert>
#include "Input.h"
#include "SceneController.h"
#include "TitleScene.h"

constexpr int default_window_width = 640;//�f�t�H���g�E�B���h�E��
constexpr int default_window_height = 480;//�f�t�H���g�E�B���h�E��
constexpr int default_color_bit = 32;//�f�t�H���g�J���[�r�b�g

Application::Application() :
	windowSize_{default_window_width,default_window_height}
{
}

Application::~Application()
{
}

Application& Application::GetInstance()
{
	static Application instance;//static�ŕ��ʂɐ錾
	return instance;//�����Ă����Ԃ�
}

bool Application::Init()
{
	SetWindowSize(windowSize_.w, windowSize_.h);
	//�E�B���h�E���[�h�ݒ�
	ChangeWindowMode(true);
	if (DxLib_Init() == -1)
	{
		return false;
	}
	return true;
}

void Application::Run()
{
	SetDrawScreen(DX_SCREEN_BACK);
	Input input;//���͂̂��߂̃I�u�W�F�N�g
	SceneController controller;//�V�[���J�ڂ̂��߂̃R���g���[���I�u�W�F�N�g
	//�ŏ��̃V�[�����Z�b�g����
	//��������V�[�����Ȃ��ƁAUpdate��Draw���ł��Ȃ�����
	controller.ChangeScene(std::make_shared<TitleScene>(controller));

	while (ProcessMessage() != -1)
	{
		ClearDrawScreen();
		input.Update();//���͏��̍X�V

		//�V�[���̍X�V
		controller.Update(input);
		//�V�[���̕`��
		controller.Draw();

		ScreenFlip();
	}
}

void Application::Terminate()
{
	DxLib_End();
}

const Size& Application::GetWindowSize() const
{
	return windowSize_;
}

#pragma once

#include "Geometry.h"
/// <summary>
/// �A�v���P�[�V�����S�̂��Ǘ�����
/// �V���O���g���N���X
/// </summary>
class Application
{
private:
	Size windowSize_;
	//private�ɃR���X�g���N�^�A�R�s�[�R���X�g���N�^�A���
	//��u�����ƂŁA2�ȏ�C���X�^���X������Ȃ�����
	Application();//new���ϐ��錾���ł��Ȃ��Ȃ�
	Application(const Application& app) = delete;//�R�s�[�R���X�g���N�^�������ɂ���
	void operator=(const Application& app) = delete;//������ꉞ�����ɂ���
public:
	~Application();
	//�������Application�I�u�W�F�N�g�ɃA�N�Z�X����֐���static�ŗp��
	//static�o�Ȃ��ƁA�C���X�^���X���Ȃ��ƌĂяo���Ȃ����߁A�����static��
	//�I�u�W�F�N�g���Ȃ��Ă��Ăяo����

	/// <summary>
	/// Application�̃V���O���g���C���X�^���X���擾����
	/// </summary>
	/// <returns>Application�̃C���X�^���X</returns>
	/// <note>Application�̎��̂͂��̊֐������Ő�������A�����ƂƂǂ܂葱����</note>
	static Application& GetInstance();

	/// <summary>
	/// ����������
	/// </summary>
	/// <returns>����������:true / ���������s:false</returns>
	bool Init();
	/// <summary>
	/// �A�v���P�[�V�������X�^�[�g����
	/// �Q�[�����[�v������
	/// </summary>
	void Run();

	/// <summary>
	/// �A�v���P�[�V�����I������
	/// </summary>
	void Terminate();

	/// <summary>
	/// �E�B���h�E�T�C�Y��Ԃ�
	/// </summary>
	const Size& GetWindowSize() const;
};


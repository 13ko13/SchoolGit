#pragma once
#include <array>
#include <map>
#include <string>
#include <vector>

/// <summary>
/// ���Ӌ@����
/// </summary>
enum class PeripheralType
{
	keyboard,
	pad1
};

/// <summary>
/// ���͑Ή����
/// </summary>
struct InputState
{
	PeripheralType type;//���͂��ꂽ�@��̎��
	int id;//���͏�񂪓���(�L�[�{�[�h�̏ꍇ�̓C���f�b�N�X�A�p�b�h�̏ꍇ�̓r�b�g�j
};

/// <summary>
/// ���͂𒊏ۉ����邽�߂̃N���X
/// </summary>
class Input
{
private:
	std::map<std::string,std::vector<InputState>> inputTable_;	//�C�x���g���Ǝ��ۂ̓��͂̑Ή��\
	std::map<std::string, bool>inputData_;//���ۂɓ��͂��ꂽ���ǂ����̃f�[�^
	std::map<std::string, bool>lastInputData_;//�O�̃t���[���ɓ��͂��ꂽ���ǂ����̃f�[�^
public:
	Input();

	/// <summary>
	/// ����𖈃t���[���Ăяo�����Ƃ�
	/// ���͏�񂪍X�V����܂�
	/// </summary>
	void Update();
	/// <summary>
	/// ����̃{�^����������Ă��邩
	/// </summary>
	/// <param name="name">�C�x���g��</param>
	/// <returns>������Ă���:true / ������ĂȂ�:false</returns>
	bool IsPressed(const char* name) const;

	/// <summary>
	/// ����̃{�^�����������ꂽ��(�����ꂽ�u�Ԃɂ����������Ȃ�)
	/// </summary>
	/// <param name="name">�C�x���g��</param>
	/// <returns>�������ꂽ�u�� : true / ������ĂȂ�or�������ςȂ�:false</returns>
	bool IsTriggerd(const char* name)const;
};


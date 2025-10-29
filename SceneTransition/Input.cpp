#include "Input.h"
#include <DxLib.h>

Input::Input() :
	inputData_{},
	lastInputData_{},
	inputTable_{}
{
	//�C�x���g����Y�����ɂ��āA�E�Ӓl�Ɏ��ۂ̓��͎�ʂƓ��̓R�[�h�̔z���u��
	inputTable_["ok"] = { { PeripheralType::keyboard, KEY_INPUT_RETURN },
							{  PeripheralType::pad1,PAD_INPUT_L } };//SELECT�L�[
	inputTable_["pause"] = { { PeripheralType::keyboard, KEY_INPUT_P },
							{  PeripheralType::pad1,PAD_INPUT_R } };
	inputTable_["shot"] = { { PeripheralType::keyboard, KEY_INPUT_Z },
							{PeripheralType::pad1, PAD_INPUT_C } };//PAD��X�{�^��
	inputTable_["up"] = { { PeripheralType::keyboard, KEY_INPUT_UP },
							{PeripheralType::pad1,PAD_INPUT_UP } };
	inputTable_["down"] = { { PeripheralType::keyboard, KEY_INPUT_DOWN },
							{PeripheralType::pad1,PAD_INPUT_DOWN } };
	inputTable_["left"] = { { PeripheralType::keyboard, KEY_INPUT_LEFT },
		{PeripheralType::pad1,PAD_INPUT_LEFT } };
	inputTable_["right"] = { { PeripheralType::keyboard, KEY_INPUT_RIGHT },
							{PeripheralType::pad1,PAD_INPUT_RIGHT } };

	//���炩���ߓ��̓f�[�^�̂��߂̘g���J���Ă���
	//�����Řg���J���Ă����Ȃ��ƁA�`�F�b�N�̍ۂ�At�֐��ŃN���b�V������\��������
	for (const auto& inputInfo : inputTable_)
	{
		inputData_[inputInfo.first] = false;
		lastInputData_[inputInfo.first] = false;
	}
}

void Input::Update()
{
	//�܂����݂̓��͏����擾
	char keyState[256];
	GetHitKeyStateAll(keyState);//���̃L�[�{�[�h���
	int padState = GetJoypadInputState(DX_INPUT_PAD1);//����PAD1���
	lastInputData_ = inputData_;//���O�̃t���[�����X�V(�O�̃t���[�������R�s�[)
	//���ׂĂ̓��̓C�x���g���`�F�b�N���܂�
	//������inputData_���X�V�����
	//inputTable_���񂵂Ċe�C�x���g�̓��͂��`�F�b�N����
	for (const auto& inputInfo : inputTable_)
	{
		auto& input = inputData_[inputInfo.first];//inputInfo.first�ɂ�"ok"�����͂����Ă�
		//input������������ƁAinputData_�̂��̃C�x���g��������Ă邩�ǂ�����
		//���������邱�ƂɂȂ�
		for (const auto& state : inputInfo.second){//InputState�̃x�N�^����
			//�q�̃��[�v��InputState�z��̃��[�v�Ȃ̂�
			//�܂��A���͎�ʂ��`�F�b�N���܂��@
			switch (state.type)
			{
			case PeripheralType::keyboard://�L�[�{�[�h��������
				//GetHitKeyStateAll�łƂ��Ă����z��̒��g������
				//���͂���Ă��邩���ۂ��`�F�b�N
				input = keyState[state.id];
				break;
			case PeripheralType::pad1:
				//GetJoypadStated�łƂ��Ă����r�b�g��������
				//�o�^����Ă�r�b�g����&�����A���̃r�b�g�������Ă��邩�ǂ������`�F�b�N
				input = (padState & state.id);
				break;
			}
			if (input)	//�厖�I�K�{!
			{
				//break���Ȃ���pad1�����̂܂܂̂����Ă��܂�
				//�Ō�̃`�F�b�N�ŉ�����ĂȂ���false�ɂȂ��Ă��܂�
				break;
			}
		}
	}
}

bool Input::IsPressed(const char* name) const
{
	//�����u�Ȃ��v�C�x���g�𑗂���ƃN���b�V�����܂�
	//�����N���b�V�������₾������
	//if (inputData_.contains(name)){
	//	return false;//�ŉ���ł��܂��B
	//}
	return inputData_.at(name);//const�֐������Ȃ̂�[]�ł͂Ȃ�at���g�p���Ă�
}

bool Input::IsTriggerd(const char* name) const
{
	return inputData_.at(name) && !lastInputData_.at(name);
}

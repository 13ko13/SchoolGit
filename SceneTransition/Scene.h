#pragma once
class SceneController;	//�V�[���R���g���[���̃v���g�^�C�v�錾
class Input;			//���͂̃v���g�^�C�v�錾
/// <summary>
/// �V�[�����N���X
/// </summary>
class Scene
{
protected:
	SceneController& controller_;
public:
	Scene(SceneController& controller);
	/// <summary>
	/// �V�[���̏��̍X�V
	/// </summary>
	/// <param name="input">���͏��</param>
	virtual void Update(Input& input) = 0;

	/// <summary>
	/// �V�[���̕`��(�V�[���̎��������`�悷��)
	/// </summary>
	virtual void Draw() = 0;
};


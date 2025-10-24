#pragma once

/// <summary>
/// 2D�x�N�g���N���X
/// </summary>
struct Vector2
{
	float x, y;
	float Length()const;///�x�N�g���̑傫��
	void Normalize();///�傫�����P�ɂ���
	Vector2 Normalized()const;///�傫�����P�ɂ����x�N�g����Ԃ�
	Vector2 operator-()const;///�x�N�g���𔽓]�����x�N�g����Ԃ�
	//���Z�q�I�[�o�[���[�h
	void operator+=(const Vector2& val);///���Z
	void operator-=(const Vector2& val);///���Z
	void operator*=(const float scale);///�x�N�g����n�{����
	Vector2 operator+(const Vector2& val)const;///���Z
	Vector2 operator-(const Vector2& val)const;///���Z
	Vector2 operator*(float scale)const;///�x�N�g���̏�Z
};

using Position2 = Vector2;//���W���x�N�g���Ƃ��Ĉ���

/// <summary>
/// 2D�̃T�C�Y���`����\����
/// </summary>
struct Size
{
	int w;///���@
	int h;///����
};
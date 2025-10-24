#include "Geometry.h"
#include <DxLib.h>
#include <cmath>

void Circle :: Draw()
{
	DrawCircleAA(pos.x, pos.y, r, 16, 0xffffff, false, 2.0f);
}

Vector2 Vector2::operator-()const
{
	//�x�N�g���𔽓]������
	return { -x,-y };
}

float Vector2::Length() const
{
	//return sqrt(x * x + y * y);
	return std::hypot(x, y);
}

void Vector2::Normalize()
{
	auto len = Length();
	if (len == 0.0f)
	{
		//0���Z������Ă���
		x = 0.0f;
		y = 0.0f;
		return;
	}
	x /= len;
	y /= len;
}

Vector2 Vector2::Normalized() const
{
	auto len = Length();
	if (len == 0.0f)
	{
		return { 0.0f,0.0f };
	}
	return { x / len,y / len };
}

void Vector2::operator+=(const Vector2 & val)
{
	x += val.x;
	y += val.y;
}

void Vector2::operator-=(const Vector2& val)
{
	x -= val.x;
	y -= val.y;
}

void Vector2::operator*=(const float scale)
{
	x *= scale;
	y *= scale;
}

Vector2 Vector2::operator+(const Vector2& val)const
{
	return { x + val.x,y + val.y };
}

Vector2 Vector2::operator-(const Vector2& val)const
{
	return { x - val.x,y - val.y };
}

Vector2 Vector2::operator*(float scale)const
{
	return { x * scale,y * scale };
}
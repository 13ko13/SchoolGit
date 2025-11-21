#include "Zako.h"
#include <DxLib.h>

constexpr float enemy_speed = 2.0f;	//“G‚ÌˆÚ“®‘¬“x
constexpr float enemy_bullet_speed = 4.0f;//“G‚Ì’e‚Ì‘¬“x
constexpr int enemy_cut_w = 16;
constexpr int enemy_cut_h = 16;
constexpr float enemy_scale = 2.5f;

Zako::Zako(int handle, std::shared_ptr<Player> player, 
	std::shared_ptr<BulletFactory> bf,
	const Position2& pos) :
	handle_(handle),Enemy(player,bf,pos,10.0f),frame_(0)
{
}

void Zako::Update()
{
	frame_++;
}

void Zako::Draw()
{
	int idx = (frame_ / 6) % 2;//6ƒtƒŒ[ƒ€‚²‚Æ‚É0,1‚ªØ‚è‘Ö‚í‚é
	DrawRectRotaGraph(pos_.x,pos_.y,
					enemy_cut_w * idx,0,
					enemy_cut_w,enemy_cut_h,
					enemy_scale,0.0f,
					handle_, true);
}

void Zako::OnHit(const Actor& actor)
{

}

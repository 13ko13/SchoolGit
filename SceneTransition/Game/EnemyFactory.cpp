#include "EnemyFactory.h"
#include "Zako.h"
#include <DxLib.h>
#include <cassert>

EnemyFactory::EnemyFactory(std::shared_ptr<BulletFactory> bf) :
    bulletFactory(bf)
{
    handles_.push_back(-1);//‰½‚à‚È‚¢

    handles_.push_back(LoadGraph(L"img/game/zako.png"));//1”Ô
    assert(handles_.back() >= 0);

    handles_.push_back(LoadGraph(L"img/game/patapata.png"));//2”Ô
    assert(handles_.back() >= 0);
}

std::shared_ptr<Enemy> EnemyFactory::Create(int idx, int idxY,
                           EnemyType enemyType, std::shared_ptr<Player> player)
{
    if (enemyType == EnemyType::none)
    {
        return nullptr;
    }
    Position2 pos = { idx * 32 + 16,480 - 32 - idxY * 32 + 16 };
    switch (enemyType)
    {
    case EnemyType::zako:
        enemies_.push_back(std::make_shared<Zako>(handles_[(int)EnemyType::zako],
            player, bulletFactory, pos));
        return enemies_.back();
    default:
        return nullptr;
    }
    return nullptr;
}

std::list<std::shared_ptr<Enemy>>& EnemyFactory::GetEnemies()
{
    return enemies_;
}

void EnemyFactory::Update()
{
    for (auto& enemy : enemies_)
    {
        enemy->Update();
    }
}

void EnemyFactory::Draw()
{
    for (auto& enemy : enemies_)
    {
        enemy->Draw();
    }
}
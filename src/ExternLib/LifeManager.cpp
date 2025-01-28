#include "pch.h"
#include "LifeManager.h"

LifeManager::LifeManager()
{
}

void LifeManager::Init(int _Hp)
{
    mHp = _Hp;
}

void LifeManager::TakeDamage(int _Dmg) {
    mHp -= _Dmg;
    if (mHp < 0) {
        mHp = 0;
    }
}

int LifeManager::GetHp() {
    return mHp;
}

void LifeManager::SetHp(int _Hp)
{
    this->mHp = _Hp;
}

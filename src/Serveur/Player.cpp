#include "pch.h"
#include "Player.h"
#include <iostream>

Player::~Player()
{
}

void Player::Init()
{
    if (!data) {
        data = new int(Hp);
        std::cout << "Resource reinitialized with value: " << *data << "\n";
    }
}

void Player::Uninit()
{
    if (data) {
        std::cout << "Resource uninitialized, value was: " << *data << "\n";
        delete data;
        data = nullptr;
    }
}

Player::~Player() {
    Uninit();
}

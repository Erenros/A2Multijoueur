#include "pch.h"
//#include <iostream>
//#include <ctime>
//#include "Projectile.h"
//
//Projectile::Projectile() : mSpeed(4), mDamage(1), mPosX(0), mPosY(0), mWidth(0), mHeight(0), mIsTouchingWall(false), mIsTouchingPlayer(false)
//{
//}
//Projectile::~Projectile()
//{
//}
//
//
//void Projectile::Init(int _Speed, int _Damage, int _PosX, int _PosY, int _Width, int _Height, bool _IsTouchingWall, bool _IsTouchingPlayer)
//{
//    this->mSpeed = _Speed;
//    this->mDamage = _Damage;
//    this->mPosX = _PosX;
//    this->mPosY = _PosY;
//    this->mWidth = _Width;
//    this->mHeight = _Height;
//    this->mIsTouchingPlayer = _IsTouchingPlayer;
//    this->mIsTouchingWall = _IsTouchingWall;
//}
//
//void Projectile::Move()
//{
//    if (Command == 'd')
//    {
//        this->mPosX += 1;
//    }
//    if (Command == 'd' && Command == 'z')
//    {
//        this->mPosX += 1;
//        this->mPosY -= 1;
//    }
//    if (Command == 'z')
//    {
//        this->mPosY -= 1;
//    }
//    if (Command == 'q' && Command == 'z')
//    {
//        this->mPosX -= 1;
//        this->mPosY -= 1;
//    }
//    if (Command == 'q')
//    {
//        this->mPosX -= 1;
//    }
//    if (Command == 'q' && Command == 's')
//    {
//        this->mPosX -= 1;
//        this->mPosY += 1;
//    }
//    if (Command == 's')
//    {
//        this->mPosY += 1;
//    }
//    if (Command == 'd' && Command == 's')
//    {
//        this->mPosX += 1;
//        this->mPosY += 1;
//    }
//}
//
//void Projectile::Death()
//{
//
//}
//
//bool Projectile::CheckCollisions()
//{
//    if (this->mPosX + this->mWidth < Obstacle->PosX) return false;
//    if (this->mPosY + this->mWeight < Obstacle->PosY) return false;
//    if (this->mPosX > Obstacle->PosX + Obstacle->width) return false;
//    if (this->mPosY > Obstacle->PosY + Obstacle->height) return false;
//    return true;
//}
//
//void Projectile::CreateProjectile()
//{
//    Projectile newRect(int this->mPosX, int this->mPosY, int this->mWidth, int this->mHeight) {
//        Projectile m = { this->mPosX, this->mPoxY, this->mWidth, this->mHeight };
//        return m;
//    }
//}
//
//void Projectile::Update(float Deltatime)
//{
//    if (Command == 'd') CreateProjectile();
//}
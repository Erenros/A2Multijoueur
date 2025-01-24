#include "pch.h"
//#include "Collider.h"
//
//bool Collider::CollisionAABB(Entity* other) const {
//
//	float left1 = GetConstPosition().GetX();
//	float top1 = GetConstPosition().GetY();
//	float right1 = left1 + GetConstSize().GetX();
//	float bottom1 = top1 + GetConstSize().GetY();
//
//	float left2 = other->GetConstPosition().GetX();
//	float top2 = other->GetConstPosition().GetY();
//	float right2 = left2 + other->GetConstSize().GetX();
//	float bottom2 = top2 + other->GetConstSize().GetY();
//
//	return !(right1 < left2 ||
//		left1 > right2 ||
//		bottom1 < top2 ||
//		top1 > bottom2);
//}

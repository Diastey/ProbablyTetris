#pragma once
#include "Component.h"
#include "Vec2.h"

class CTransform : public Component
{
public:
	Vec2 pos = { 0,0 };
	CTransform() {}
	CTransform(const Vec2& p) :pos(p) {}
};
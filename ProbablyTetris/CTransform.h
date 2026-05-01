#pragma once
#include "Component.h"
#include <d3dx9.h>
#include <d3dx9math.h>

class CTransform : public Component
{
public:
	D3DXVECTOR2 scaling;
	float rotation;
	D3DXVECTOR2 position;

public:
	CTransform();
	CTransform(D3DXVECTOR2 scaling, float rotation, D3DXVECTOR2 position);
};
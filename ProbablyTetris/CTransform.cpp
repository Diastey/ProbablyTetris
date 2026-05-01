#include "CTransform.h"

CTransform::CTransform()
{
	scaling = D3DXVECTOR2(0, 0);
	rotation = 0;
	position = D3DXVECTOR2(0, 0);
}

CTransform::CTransform(D3DXVECTOR2 scaling, float rotation, D3DXVECTOR2 position)
	:scaling(scaling), rotation(rotation), position(position)
{
}

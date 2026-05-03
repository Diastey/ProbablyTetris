#pragma once

class Component
{
public:
	bool exists = false;

	virtual void Release() {}
	virtual void Update() {}
};
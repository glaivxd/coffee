#include "entity.hpp"
#include "../../utility/process/process.hpp"
#include "../offsets.hpp"

bool Entity::valid()
{
	if (health() < 1)
		return false;

	return true;
}

int Entity::health()
{
	return process.read<int>(self + Netvars::m_iHealth);
}

ClassID Entity::type()
{
	int vtable = process.read<int>(self + 0x8); //iclientnetworkable vtable
	int function = process.read<int>(vtable + 2 * 0x4); // 3rd function
	int c = process.read<int>(function + 0x1); // clas s
	ClassID id = process.read<ClassID>(c + 0x14); // fuckshit balls

	return id;
}

int Entity::team()
{
	return process.read<int>(self + Netvars::m_iTeamNum);
}
#include "entity.hpp"
#include "../../utility/process/process.hpp"
#include "../offsets.hpp"
#include "../engine/engine.hpp"

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
	int c = process.read<int>(function + 0x1); // class
	ClassID id = process.read<ClassID>(c + 0x14); // fuckshit balls

	return id;
}

int Entity::team()
{
	return process.read<int>(self + Netvars::m_iTeamNum);
}

int Entity::flags()
{
	return process.read<int>(self + Netvars::m_fFlags);
}

void Entity::glow()
{
	struct GlowStruct
	{
		float red = 0.f;
		float green = 0.f;
		float blue = 0.f;
		float alpha = 1.f;
		uint8_t padding[8];
		float unknown = 1.f;
		uint8_t padding2[4];
		BYTE renderOccluded = true;
		BYTE renderUnoccluded = false;
		BYTE fullBloom = false;
	} object;

	int glow_manager = process.read<int>(Engine::client + Signatures::dwGlowObjectManager);
	int glow_index = process.read<int>(self + Netvars::m_iGlowIndex);

	process.write<GlowStruct>(glow_manager + (glow_index * 0x38) + 0x8, object);
}
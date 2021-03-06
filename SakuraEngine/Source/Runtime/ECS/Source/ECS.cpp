#include "ECS/ECS.h"
#include "Base/GUID.h"

ECSModule* ECSModule::create()
{
	return new ECSModule();
}

bool ECSModule::StartUp()
{
	core::codebase::initialize(&sakura::ecs::new_guid);
	return true;
}

bool ECSModule::Terminate()
{
	return true;
}

core::GUID sakura::ecs::new_guid()
{
	core::GUID result;
	auto guid = sakura::new_guid();
	memcpy(&result, &guid, sizeof(core::GUID));
	return result;
}
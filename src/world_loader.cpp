#include "world_loader.hpp"

using namespace godot;

WorldLoader::WorldLoader()
{
}

WorldLoader::~WorldLoader()
{
}

VoxelWorldInstance* WorldLoader::get_world_instance() const
{
	return world_instance;
}

void WorldLoader::set_world_instance(VoxelWorldInstance* world_instance)
{
	this->world_instance = world_instance;
}

void WorldLoader::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("get_world_instance"), &WorldLoader::get_world_instance);
	ClassDB::bind_method(D_METHOD("set_world_instance", "world_instance"), &WorldLoader::set_world_instance);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "world_instance", PROPERTY_HINT_NODE_TYPE, "VoxelWorldInstance"), "set_world_instance", "get_world_instance");
}

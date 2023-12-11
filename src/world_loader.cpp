#include "world_loader.hpp"

using namespace godot;

WorldLoader::WorldLoader()
{
	loaded_chunks = Array();
}

WorldLoader::~WorldLoader()
{
}

void WorldLoader::load_chunk(Vector3i p_position)
{
	ERR_FAIL_NULL_MSG(world_instance, "WorldLoader::load_chunk: world_instance is null!");

	loaded_chunks.append(p_position);
	world_instance->load_chunk(p_position);
}

void WorldLoader::unload_chunk(Vector3i p_position)
{
	ERR_FAIL_NULL_MSG(world_instance, "WorldLoader::unload_chunk: world_instance is null!");

	loaded_chunks.erase(p_position);
	world_instance->unload_chunk(p_position);
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

	ClassDB::bind_method(D_METHOD("load_chunk", "p_position"), &WorldLoader::load_chunk);
	ClassDB::bind_method(D_METHOD("unload_chunk", "p_position"), &WorldLoader::unload_chunk);
}

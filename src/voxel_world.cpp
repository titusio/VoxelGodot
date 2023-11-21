#include "voxel_world.hpp"

#include <godot_cpp/core/class_db.hpp>

using namespace godot;

VoxelWorld::VoxelWorld()
{
    // set default values
    set_chunk_size(16);
    set_colliding(true);
}

VoxelWorld::~VoxelWorld()
{
}

Ref<VoxelSet> VoxelWorld::get_voxel_set() const
{
    return voxel_set;
}

void VoxelWorld::set_voxel_set(Ref<VoxelSet> p_voxel_set)
{
    voxel_set = p_voxel_set;
}

int VoxelWorld::get_chunk_size() const
{
    return chunk_size;
}

void VoxelWorld::set_chunk_size(int p_chunk_size)
{
    chunk_size = p_chunk_size;
}

void VoxelWorld::set_colliding(bool p_colliding)
{
    colliding = p_colliding;
}

bool VoxelWorld::is_colliding() const
{
    return colliding;
}

void VoxelWorld::_bind_methods()
{
    // voxel set
    ClassDB::bind_method(D_METHOD("get_voxel_set"), &VoxelWorld::get_voxel_set);
    ClassDB::bind_method(D_METHOD("set_voxel_set", "p_voxel_set"), &VoxelWorld::set_voxel_set);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "voxel_set", PROPERTY_HINT_RESOURCE_TYPE, "VoxelSet"), "set_voxel_set", "get_voxel_set");
    // chunk_size
    ClassDB::bind_method(D_METHOD("get_chunk_size"), &VoxelWorld::get_chunk_size);
    ClassDB::bind_method(D_METHOD("set_chunk_size", "p_chunk_size"), &VoxelWorld::set_chunk_size);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "chunk_size"), "set_chunk_size", "get_chunk_size");
    // colliding
    ClassDB::bind_method(D_METHOD("set_colliding", "p_colliding"), &VoxelWorld::set_colliding);
    ClassDB::bind_method(D_METHOD("is_colliding"), &VoxelWorld::is_colliding);
    ADD_PROPERTY(PropertyInfo(Variant::BOOL, "colliding"), "set_colliding", "is_colliding");
}

bool VoxelWorld::_property_can_revert(const StringName &p_name) const
{
    if (p_name == StringName("chunk_size"))
        return true;
    if (p_name == StringName("colliding"))
        return true;
    return false;
}

bool VoxelWorld::_property_get_revert(const StringName &p_name, Variant &r_property) const
{
    if (p_name == StringName("chunk_size"))
    {
        r_property = 16;
        return true;
    }
    if (p_name == StringName("colliding"))
    {
        r_property = true;
        return true;
    }
    return false;
}
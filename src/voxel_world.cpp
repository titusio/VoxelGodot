#include "voxel_world.hpp"

#include <godot_cpp/core/class_db.hpp>

using namespace godot;

VoxelWorld::VoxelWorld()
{
}

VoxelWorld::~VoxelWorld()
{
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
    ClassDB::bind_method(D_METHOD("set_colliding", "p_colliding"), &VoxelWorld::set_colliding);
    ClassDB::bind_method(D_METHOD("is_colliding"), &VoxelWorld::is_colliding);

    ADD_PROPERTY(PropertyInfo(Variant::BOOL, "colliding"), "set_colliding", "is_colliding");
}
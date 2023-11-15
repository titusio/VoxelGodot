#include "voxel_world_instance.hpp"

#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

VoxelWorldInstance::VoxelWorldInstance()
{
}

VoxelWorldInstance::~VoxelWorldInstance()
{
}

void VoxelWorldInstance::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("get_voxel_world"), &VoxelWorldInstance::get_voxel_world);
    ClassDB::bind_method(D_METHOD("set_voxel_world", "p_world"), &VoxelWorldInstance::set_voxel_world);

    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "voxel_world", PropertyHint::PROPERTY_HINT_RESOURCE_TYPE, "VoxelWorld"), "set_voxel_world", "get_voxel_world");
}

Ref<VoxelWorld> VoxelWorldInstance::get_voxel_world() const
{
    return world;
}

void VoxelWorldInstance::set_voxel_world(Ref<VoxelWorld> p_world)
{
    world = p_world;
}

void VoxelWorldInstance::generate()
{
    UtilityFunctions::print("VoxelWorldInstance::generate()");
}

void VoxelWorldInstance::clear()
{
    UtilityFunctions::print("VoxelWorldInstance::clear()");
}
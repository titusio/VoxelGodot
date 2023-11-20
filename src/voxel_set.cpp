#include "voxel_set.hpp"

#include <godot_cpp/core/class_db.hpp>

using namespace godot;

VoxelSet::VoxelSet()
{
}

VoxelSet::~VoxelSet()
{
}

Array VoxelSet::get_voxels() const
{
    return voxels;
}

void VoxelSet::set_voxels(Array p_voxels)
{
    voxels = p_voxels;
    for (int i = 0; i < voxels.size(); i++)
    {
        if (voxels[i].get_type() != Variant::NIL)
            continue;

        voxels[i] = memnew(Voxel());
    }
}

void VoxelSet::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("get_voxels"), &VoxelSet::get_voxels);
    ClassDB::bind_method(D_METHOD("set_voxels", "p_voxels"), &VoxelSet::set_voxels);
    ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "voxels", PROPERTY_HINT_ARRAY_TYPE, "Voxel"), "set_voxels", "get_voxels");
}
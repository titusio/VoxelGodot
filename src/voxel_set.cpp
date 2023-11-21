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
}

void VoxelSet::_get_property_list(List<PropertyInfo> *p_list) const
{
	p_list->push_back(PropertyInfo(Variant::ARRAY, "voxels", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_NO_EDITOR));
}

bool VoxelSet::_set(const StringName &p_name, const Variant &p_value)
{
	if (p_name == StringName("voxels"))
	{
		set_voxels(p_value);
		return true;
	}

	return false;
}

bool VoxelSet::_get(const StringName &p_name, Variant &r_ret) const
{
	if (p_name == StringName("voxels"))
	{
		r_ret = get_voxels();
		return true;
	}

	return false;
}

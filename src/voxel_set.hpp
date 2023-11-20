#ifndef VOXEL_SET_HPP
#define VOXEL_SET_HPP

#include <godot_cpp/variant/builtin_types.hpp>
#include <godot_cpp/classes/resource.hpp>

#include "voxel.hpp"

namespace godot
{
    class VoxelSet : public Resource
    {
        GDCLASS(VoxelSet, Resource)

    public:
        Array voxels;

    public:
        VoxelSet();
        ~VoxelSet();

        Array get_voxels() const;
        void set_voxels(Array p_voxels);

    protected:
        static void _bind_methods();
    };
}

#endif // VOXEL_SET_HPP
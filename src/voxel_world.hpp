#ifndef VOXEL_WORLD_HPP
#define VOXEL_WORLD_HPP

#include <godot_cpp/classes/resource.hpp>

namespace godot
{
    class VoxelWorld : public Resource
    {
        GDCLASS(VoxelWorld, Resource)

    public:
        VoxelWorld();
        ~VoxelWorld();

    protected:
        static void _bind_methods();
    };
}

#endif // VOXEL_WORLD_HPP

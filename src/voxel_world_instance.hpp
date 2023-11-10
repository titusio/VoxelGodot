#ifndef VOXEL_WORLD_INSTANCE_HPP
#define VOXEL_WORLD_INSTANCE_HPP

#include <godot_cpp/classes/node3d.hpp>

namespace godot
{
    class VoxelWorldInstance : public Node3D
    {
        GDCLASS(VoxelWorldInstance, Node3D)

    public:
        VoxelWorldInstance();
        ~VoxelWorldInstance();

    protected:
        static void _bind_methods();
    };
} // namespace godot

#endif // VOXEL_WORLD_INSTANCE_HPP
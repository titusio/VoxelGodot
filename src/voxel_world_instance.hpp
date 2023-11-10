#ifndef VOXEL_WORLD_INSTANCE_HPP
#define VOXEL_WORLD_INSTANCE_HPP

#include <godot_cpp/classes/node3d.hpp>
#include "voxel_world.hpp"

namespace godot
{
    class VoxelWorldInstance : public Node3D
    {
        GDCLASS(VoxelWorldInstance, Node3D)

    public:
        Ref<VoxelWorld> world;

    public:
        VoxelWorldInstance();
        ~VoxelWorldInstance();

        Ref<VoxelWorld> get_voxel_world() const;
        void set_voxel_world(Ref<VoxelWorld> p_world);

    protected:
        static void _bind_methods();
    };
} // namespace godot

#endif // VOXEL_WORLD_INSTANCE_HPP
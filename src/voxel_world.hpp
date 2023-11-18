#ifndef VOXEL_WORLD_HPP
#define VOXEL_WORLD_HPP

#include <godot_cpp/classes/resource.hpp>

namespace godot
{
    class VoxelWorld : public Resource
    {
        GDCLASS(VoxelWorld, Resource)

    public:
        bool colliding;

    public:
        VoxelWorld();
        ~VoxelWorld();

        void set_colliding(bool p_colliding);
        bool is_colliding() const;

    protected:
        static void _bind_methods();
    };
}

#endif // VOXEL_WORLD_HPP

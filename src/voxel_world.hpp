#ifndef VOXEL_WORLD_HPP
#define VOXEL_WORLD_HPP

#include <godot_cpp/classes/resource.hpp>

#include "voxel_set.hpp"
#include "chunk_data.hpp"

namespace godot
{
    class VoxelWorld : public Resource
    {
        GDCLASS(VoxelWorld, Resource)

    public:
        Ref<VoxelSet> voxel_set;
		float voxel_size;
        int chunk_size;
        bool colliding;

    public:
        VoxelWorld();
        ~VoxelWorld();

        Ref<VoxelSet> get_voxel_set() const;
        void set_voxel_set(Ref<VoxelSet> p_voxel_set);
		float get_voxel_size() const;
		void set_voxel_size(float p_voxel_size);
        int get_chunk_size() const;
        void set_chunk_size(int p_chunk_size);
        void set_colliding(bool p_colliding);
        bool is_colliding() const;

    protected:
        static void _bind_methods();
        bool _property_can_revert(const StringName &p_name) const;
        bool _property_get_revert(const StringName &p_name, Variant &r_property) const;
    };
}

#endif // VOXEL_WORLD_HPP

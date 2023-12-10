#ifndef EDITOR_VOXEL_WORLD_HPP
#define EDITOR_VOXEL_WORLD_HPP

#include <godot_cpp/variant/builtin_types.hpp>

#include "godot_cpp/templates/list.hpp"
#include "voxel_world.hpp"

namespace godot
{
    class EditorVoxelWorld : public VoxelWorld
    {
        GDCLASS(EditorVoxelWorld, VoxelWorld);

    public:
		AABB world_bounds;

    private:
        Dictionary chunks;

    public:
        EditorVoxelWorld();
        ~EditorVoxelWorld();

		AABB get_world_bounds() const;
		void set_world_bounds(AABB p_world_bounds);
        
		ChunkData* get_chunk(Vector3i position) override;
	
	private:
		void _update_chunk_list();

    protected:
        static void _bind_methods();
        bool _set(const StringName &p_name, const Variant &p_value);
        bool _get(const StringName &p_name, Variant &r_ret) const;
        void _get_property_list(List<PropertyInfo> *p_list) const;
        bool _property_can_revert(const StringName &p_name) const;
        bool _property_get_revert(const StringName &p_name, Variant &r_property) const;
    };
}

#endif // EDITOR_VOXEL_WORLD_HPP

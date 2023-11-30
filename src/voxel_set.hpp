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
	
	private:
		int id_counter;

    public:
        VoxelSet();
        ~VoxelSet();

		int get_new_id();
        Array get_voxels() const;
        void set_voxels(Array p_voxels);
	
	private:
		int _get_id_counter() const;
		void _set_id_counter(int p_id_counter);

    protected:
        static void _bind_methods();
        void _get_property_list(List<PropertyInfo> *p_list) const;
		bool _set(const StringName &p_name, const Variant &p_value);
        bool _get(const StringName &p_name, Variant &r_ret) const;
    };
}

#endif // VOXEL_tET_HPP

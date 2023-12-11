#ifndef CHUNK_LOADER_HPP
#define CHUNK_LOADER_HPP

#include <godot_cpp/classes/node3d.hpp>
#include <godot_cpp/variant/builtin_binds.hpp>

#include "voxel_world_instance.hpp"

namespace godot 
{
	class WorldLoader : public Node3D
	{
		GDCLASS(WorldLoader, Node3D);

	private:	
		VoxelWorldInstance* world_instance;
		Array loaded_chunks;

	public:
		WorldLoader();
		~WorldLoader();

		void load_chunk(Vector3i p_position);
		void unload_chunk(Vector3i p_position);

		VoxelWorldInstance* get_world_instance() const;
		void set_world_instance(VoxelWorldInstance* world_instance);

	protected:
		static void _bind_methods();
	};
}

#endif // CHUNK_LOADER_HPP

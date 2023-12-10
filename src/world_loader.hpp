#ifndef CHUNK_LOADER_HPP
#define CHUNK_LOADER_HPP

#include <godot_cpp/classes/node3d.hpp>

#include "voxel_world_instance.hpp"

namespace godot 
{
	class WorldLoader : public Node3D
	{
		GDCLASS(WorldLoader, Node3D);

	private:	
		VoxelWorldInstance* world_instance;

	public:
		WorldLoader();
		~WorldLoader();

		VoxelWorldInstance* get_world_instance() const;
		void set_world_instance(VoxelWorldInstance* world_instance);

	protected:
		static void _bind_methods();
	};
}

#endif // CHUNK_LOADER_HPP

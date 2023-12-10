#ifndef CHUNK_DATA_HPP
#define CHUNK_DATA_HPP

#include <godot_cpp/variant/builtin_types.hpp>
#include <godot_cpp/classes/object.hpp>

#include "voxel.hpp"

namespace godot
{
    class ChunkData : public Object
    {
        GDCLASS(ChunkData, Object);

    private:
        Array voxels;
		int chunk_size;

    public:
        // necessary for godot to be able to create this object
        ChunkData();
        ~ChunkData();
	
		
		void set_voxel(Vector3i position, Voxel *voxel);
		Voxel* get_voxel(Vector3i position);

		int get_chunk_size();
		// careful, this will clear the voxels array
		void set_chunk_size(int size);

		Array get_voxels() const;
		void set_voxels(Array p_voxels);

	private:
		int get_index(Vector3i position);
		Vector3i get_position(int index);


    protected:
        static void _bind_methods();
    };
} // namespace godot

#endif // CHUNK_DATA_HPP

#include "chunk_data.hpp"

#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

ChunkData::ChunkData()
{
    voxels = Array();
}

ChunkData::~ChunkData()
{
	voxels.clear();
	chunk_size = 0;
}

void ChunkData::set_voxel(Vector3i position, Voxel *voxel)
{
	voxels[get_index(position)] = Variant(voxel);
}

Voxel* ChunkData::get_voxel(Vector3i position)
{
	return Object::cast_to<Voxel>(voxels[get_index(position)]);
}

int ChunkData::get_chunk_size()
{
	return chunk_size;
}

void ChunkData::set_chunk_size(int size)
{
	chunk_size = size;
	voxels.clear();
	voxels.resize(size * size * size);
}

void ChunkData::set_voxels(Array p_voxels)
{
	voxels = p_voxels;
}

Array ChunkData::get_voxels() const
{
	return voxels;
}

int ChunkData::get_index(Vector3i position)
{
	return position.x + position.y * chunk_size + position.z * chunk_size * chunk_size;
}

Vector3i ChunkData::get_position(int index)
{
	int x = index % chunk_size;
	int y = (index / chunk_size) % chunk_size;
	int z = index / (chunk_size* chunk_size);
	return Vector3i(x, y, z);
}

void ChunkData::_bind_methods()
{
}

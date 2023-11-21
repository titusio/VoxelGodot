#include "chunk_data.hpp"

using namespace godot;

ChunkData::ChunkData()
{
    voxels = Array();
}

ChunkData::ChunkData(int chunk_size)
{
    voxels = Array();
    voxels.resize(chunk_size * chunk_size * chunk_size);
}

ChunkData::~ChunkData()
{
}

void ChunkData::_bind_methods()
{
}
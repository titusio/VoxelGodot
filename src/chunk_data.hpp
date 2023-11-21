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

    public:
        // necessary for godot to be able to create this object
        ChunkData();
        ChunkData(int chunk_size);
        ~ChunkData();

    protected:
        static void _bind_methods();
    };
} // namespace godot

#endif // CHUNK_DATA_HPP

#include "voxel_world_instance.hpp"

#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/variant/packed_vector3_array.hpp>
#include <godot_cpp/variant/packed_int32_array.hpp>
#include <godot_cpp/classes/array_mesh.hpp>
#include <godot_cpp/variant/array.hpp>

using namespace godot;

VoxelWorldInstance::VoxelWorldInstance()
{
}

VoxelWorldInstance::~VoxelWorldInstance()
{
}

void VoxelWorldInstance::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("get_voxel_world"), &VoxelWorldInstance::get_voxel_world);
    ClassDB::bind_method(D_METHOD("set_voxel_world", "p_world"), &VoxelWorldInstance::set_voxel_world);

    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "voxel_world", PropertyHint::PROPERTY_HINT_RESOURCE_TYPE, "VoxelWorld"), "set_voxel_world", "get_voxel_world");
}

Ref<VoxelWorld> VoxelWorldInstance::get_voxel_world() const
{
    return world;
}

void VoxelWorldInstance::set_voxel_world(Ref<VoxelWorld> p_world)
{
    world = p_world;
}

void VoxelWorldInstance::generate()
{
    UtilityFunctions::print("start generating");
    const int CHUNK_SIZE = 16;
    const float voxel_size = 0.1f;
    const Color color = Color("#CCD1D1");

    PackedVector3Array vertices = PackedVector3Array();
    PackedVector3Array normals = PackedVector3Array();
    PackedColorArray colors = PackedColorArray();
    PackedInt32Array indices = PackedInt32Array();

    const Vector3 a = Vector3(0.0, 1.0, 0.0);
    const Vector3 b = Vector3(1.0, 1.0, 0.0);
    const Vector3 c = Vector3(1.0, 0.0, 0.0);
    const Vector3 d = Vector3(0.0, 0.0, 0.0);
    const Vector3 e = Vector3(0.0, 1.0, 1.0);
    const Vector3 f = Vector3(1.0, 1.0, 1.0);
    const Vector3 g = Vector3(1.0, 0.0, 1.0);
    const Vector3 h = Vector3(0.0, 0.0, 1.0);

    const Vector3 north = Vector3(0.0, 0.0, -1.0);
    const Vector3 south = Vector3(0.0, 0.0, 1.0);
    const Vector3 top = Vector3(0.0, 1.0, 0.0);
    const Vector3 bottom = Vector3(0.0, -1.0, 0.0);
    const Vector3 east = Vector3(1.0, 0.0, 0.0);
    const Vector3 west = Vector3(-1.0, 0.0, 0.0);

    int index = 0;

    for (int x = 0; x < CHUNK_SIZE; x++)
    {
        for (int y = 0; y < CHUNK_SIZE; y++)
        {
            for (int z = 0; z < CHUNK_SIZE; z++)
            {
                Vector3 position = Vector3(x, y, z) * voxel_size;

                // North Face
                vertices.append(a); // 0
                vertices.append(b); // 1
                vertices.append(f); // 2
                vertices.append(e); // 3
                indices.append(index + 0);
                indices.append(index + 1);
                indices.append(index + 2);
                indices.append(index + 0);
                indices.append(index + 2);
                indices.append(index + 3);
                index += 4;
                for (int i = 0; i < 4; i++)
                {
                    normals.append(north);
                    colors.append(color);
                }

                // south face
                vertices.append(e); // 0
                vertices.append(f); // 1
                vertices.append(g); // 2
                vertices.append(h); // 3
                indices.append(index + 0);
                indices.append(index + 1);
                indices.append(index + 2);
                indices.append(index + 0);
                indices.append(index + 2);
                indices.append(index + 3);
                index += 4;
                for (int i = 0; i < 4; i++)
                {
                    normals.append(south);
                    colors.append(color);
                }

                // top
                vertices.append(a); // 0
                vertices.append(b); // 1
                vertices.append(f); // 2
                vertices.append(e); // 3
                indices.append(index + 0);
                indices.append(index + 1);
                indices.append(index + 2);
                indices.append(index + 0);
                indices.append(index + 2);
                indices.append(index + 3);
                index += 4;
                for (int i = 0; i < 4; i++)
                {
                    normals.append(top);
                    colors.append(color);
                }

                // bottom
                vertices.append(h); // 0
                vertices.append(g); // 1
                vertices.append(c); // 2
                vertices.append(d); // 3
                indices.append(index + 0);
                indices.append(index + 1);
                indices.append(index + 2);
                indices.append(index + 0);
                indices.append(index + 2);
                indices.append(index + 3);
                index += 4;
                for (int i = 0; i < 4; i++)
                {
                    normals.append(bottom);
                    colors.append(color);
                }

                // west
                vertices.append(a); // 0
                vertices.append(e); // 1
                vertices.append(h); // 2
                vertices.append(d); // 3
                indices.append(index + 0);
                indices.append(index + 1);
                indices.append(index + 2);
                indices.append(index + 0);
                indices.append(index + 2);
                indices.append(index + 3);
                index += 4;
                for (int i = 0; i < 4; i++)
                {
                    normals.append(west);
                    colors.append(color);
                }

                // east
                vertices.append(f); // 0
                vertices.append(b); // 1
                vertices.append(c); // 2
                vertices.append(g); // 3
                indices.append(index + 0);
                indices.append(index + 1);
                indices.append(index + 2);
                indices.append(index + 0);
                indices.append(index + 2);
                indices.append(index + 3);
                index += 4;
                for (int i = 0; i < 4; i++)
                {
                    normals.append(east);
                    colors.append(color);
                }
            }
        }
    }

    Ref<ArrayMesh> mesh = memnew(ArrayMesh);
    Array surface_arrays = Array();
    surface_arrays.resize(Mesh::ARRAY_MAX);
    surface_arrays[Mesh::ARRAY_VERTEX] = vertices;
    surface_arrays[Mesh::ARRAY_INDEX] = indices;
    surface_arrays[Mesh::ARRAY_NORMAL] = normals;
    surface_arrays[Mesh::ARRAY_COLOR] = colors;
    mesh->add_surface_from_arrays(Mesh::PRIMITIVE_TRIANGLES, surface_arrays);
    UtilityFunctions::print(index);
    UtilityFunctions::print("end generating");
}

void VoxelWorldInstance::clear()
{
}

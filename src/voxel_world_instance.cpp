#include "voxel_world_instance.hpp"
#include "godot_cpp/classes/ref.hpp"

#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/variant/packed_vector3_array.hpp>
#include <godot_cpp/variant/packed_int32_array.hpp>
#include <godot_cpp/classes/array_mesh.hpp>
#include <godot_cpp/variant/array.hpp>
#include <godot_cpp/classes/rendering_server.hpp>
#include <godot_cpp/classes/world3d.hpp>
#include <godot_cpp/classes/mesh_instance3d.hpp>
#include <godot_cpp/variant/rid.hpp>

using namespace godot;

VoxelWorldInstance::VoxelWorldInstance()
{
    chunk_instances = Dictionary();
    chunk_meshes = Dictionary();
}

VoxelWorldInstance::~VoxelWorldInstance()
{
    clear();
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
    if (world == nullptr)
    {
        UtilityFunctions::printerr("VoxelWorldInstance::generate(): world is null ", __FILE__, " ", __LINE__, " ", __FUNCTION__);
        return;
    }
}

void VoxelWorldInstance::clear()
{
    Array instance_keys = chunk_instances.keys();

    RenderingServer *rs = RenderingServer::get_singleton();

    for (int i = 0; i < instance_keys.size(); i++)
    {
        rs->free_rid(instance_keys[i]);
    }

    chunk_instances.clear();
    chunk_meshes.clear();
}

void VoxelWorldInstance::generate_chunk(ChunkData *p_chunk_data)
{
	ERR_FAIL_NULL(p_chunk_data);
    ERR_FAIL_NULL(world);
	
	PackedVector3Array collision_points = PackedVector3Array();

	Ref<ArrayMesh> mesh = generate_mesh(p_chunk_data, collision_points);

    Vector3 world_position = Vector3() * world->get_voxel_size() * world->get_chunk_size();

    RenderingServer *rs = RenderingServer::get_singleton();
    RID instance = rs->instance_create();
    rs->instance_set_base(instance, mesh->get_rid());
    rs->instance_set_transform(instance, Transform3D(Basis(), world_position));
    rs->instance_set_scenario(instance, get_world_3d()->get_scenario());

    chunk_meshes[Vector3i()] = mesh;
    chunk_instances[Vector3i()] = instance;
}

Ref<ArrayMesh> VoxelWorldInstance::generate_mesh(ChunkData* p_chunk_data, PackedVector3Array &p_collision_points)
{
    int CHUNK_SIZE = world->get_chunk_size();
    const float voxel_size = world->get_voxel_size();

    PackedVector3Array vertices = PackedVector3Array();
    PackedVector3Array normals = PackedVector3Array();
    PackedColorArray colors = PackedColorArray();
    PackedInt32Array indices = PackedInt32Array();

    PackedVector3Array collision_points = PackedVector3Array();

    const Vector3 a = Vector3(0.0, 1.0, 0.0) * voxel_size;
    const Vector3 b = Vector3(1.0, 1.0, 0.0) * voxel_size;
    const Vector3 c = Vector3(1.0, 0.0, 0.0) * voxel_size;
    const Vector3 d = Vector3(0.0, 0.0, 0.0) * voxel_size;
    const Vector3 e = Vector3(0.0, 1.0, 1.0) * voxel_size;
    const Vector3 f = Vector3(1.0, 1.0, 1.0) * voxel_size;
    const Vector3 g = Vector3(1.0, 0.0, 1.0) * voxel_size;
    const Vector3 h = Vector3(0.0, 0.0, 1.0) * voxel_size;

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

				Voxel* current_voxel = p_chunk_data->get_voxel(Vector3i(x, y, z));
				if (current_voxel == nullptr)
					continue;

				Color color = current_voxel->get_color();

                // North Face
                vertices.append(position + b); // 0
                vertices.append(position + a); // 1
                vertices.append(position + d); // 2
                vertices.append(position + c); // 3
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
                vertices.append(position + e); // 0
                vertices.append(position + f); // 1
                vertices.append(position + g); // 2
                vertices.append(position + h); // 3
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
                vertices.append(position + a); // 0
                vertices.append(position + b); // 1
                vertices.append(position + f); // 2
                vertices.append(position + e); // 3
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
                vertices.append(position + h); // 0
                vertices.append(position + g); // 1
                vertices.append(position + c); // 2
                vertices.append(position + d); // 3
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
                vertices.append(position + a); // 0
                vertices.append(position + e); // 1
                vertices.append(position + h); // 2
                vertices.append(position + d); // 3
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
                vertices.append(position + f); // 0
                vertices.append(position + b); // 1
                vertices.append(position + c); // 2
                vertices.append(position + g); // 3
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

                if (world->is_colliding())
                {
                    // north
                    collision_points.append(b);
                    collision_points.append(a);
                    collision_points.append(d);
                    collision_points.append(b);
                    collision_points.append(d);
                    collision_points.append(c);
                    // south
                    collision_points.append(e);
                    collision_points.append(f);
                    collision_points.append(g);
                    collision_points.append(e);
                    collision_points.append(g);
                    collision_points.append(h);
                    // west
                    collision_points.append(a);
                    collision_points.append(e);
                    collision_points.append(h);
                    collision_points.append(a);
                    collision_points.append(h);
                    collision_points.append(d);
                    // east
                    collision_points.append(f);
                    collision_points.append(b);
                    collision_points.append(c);
                    collision_points.append(f);
                    collision_points.append(c);
                    collision_points.append(g);
                    // top
                    collision_points.append(a);
                    collision_points.append(b);
                    collision_points.append(f);
                    collision_points.append(a);
                    collision_points.append(f);
                    collision_points.append(e);
                    // bottom
                    collision_points.append(h);
                    collision_points.append(g);
                    collision_points.append(c);
                    collision_points.append(h);
                    collision_points.append(c);
                    collision_points.append(d);
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

	return mesh;
}


#ifndef VOXEL_WORLD_INSTANCE_HPP
#define VOXEL_WORLD_INSTANCE_HPP

#include <godot_cpp/classes/node3d.hpp>
#include <godot_cpp/variant/dictionary.hpp>
#include <godot_cpp/classes/array_mesh.hpp>

#include "voxel_world.hpp"

namespace godot
{
    //               010           110                         Y
    //   Vertices     A0 ---------- B1            Faces      Top    -Z
    //           011 /  |      111 /  |                        |   North
    //             E4 ---------- F5   |                        | /
    //             |    |        |    |          -X West ----- 0 ----- East X
    //             |   D3 -------|-- C2                      / |
    //             |  /  000     |  / 100               South  |
    //             H7 ---------- G6                      Z    Bottom
    //              001           101                          -Y
    //
    // Vertices
    // b, a, d, b, d, c, -> N
    // e, f, g, e, g, h, -> S
    // a, e, h, a, h, d, -> W
    // f, b, c, f, c, g, -> E
    // a, b, f, a, f, e, -> T
    // h, g, c, h, c, d, -> B

    class VoxelWorldInstance : public Node3D
    {
        GDCLASS(VoxelWorldInstance, Node3D)

    public:
        Ref<VoxelWorld> world;

    private:
        Dictionary chunk_instances;
        Dictionary chunk_meshes;

    public:
        VoxelWorldInstance();
        ~VoxelWorldInstance();

        Ref<VoxelWorld> get_voxel_world() const;
        void set_voxel_world(Ref<VoxelWorld> p_world);

		void load_chunk(Vector3 p_position);
		void unload_chunk(Vector3 p_position);

    private:
		Ref<ArrayMesh> generate_mesh(ChunkData *p_chunk_data, PackedVector3Array &p_collision_points);

    protected:
        static void _bind_methods();
    };

	class ChunkInstance : public RefCounted
	{
		GDCLASS(ChunkInstance, RefCounted);

	private:
		Ref<ArrayMesh> mesh;
		Vector3 world_position;
		RID rendering_instance;
	
	public:
		ChunkInstance();
		~ChunkInstance();

		Ref<ArrayMesh> get_mesh() const;
		void set_mesh(Ref<ArrayMesh> p_mesh);

		Vector3 get_world_position() const;
		void set_world_position(Vector3 p_world_position);
	
		RID get_rendering_instance() const;
		void set_rendering_instance(RID p_rendering_instance);

	protected:
		static void _bind_methods();
	};
} // namespace godot

#endif // VOXEL_WORLD_INSTANCE_HPP

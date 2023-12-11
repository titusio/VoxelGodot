#include "editor_voxel_world.hpp"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

EditorVoxelWorld::EditorVoxelWorld()
{
}

EditorVoxelWorld::~EditorVoxelWorld()
{
}

AABB EditorVoxelWorld::get_world_bounds() const
{
	return world_bounds;
}

void EditorVoxelWorld::set_world_bounds(AABB p_world_bounds)
{
	world_bounds = p_world_bounds;

	world_bounds.position.x = UtilityFunctions::roundf(world_bounds.position.x);
	world_bounds.position.y = UtilityFunctions::roundf(world_bounds.position.y);
	world_bounds.position.z = UtilityFunctions::roundf(world_bounds.position.z);
	world_bounds.size.x = UtilityFunctions::roundf(world_bounds.size.x);
	world_bounds.size.y = UtilityFunctions::roundf(world_bounds.size.y);
	world_bounds.size.z = UtilityFunctions::roundf(world_bounds.size.z);

	_update_chunk_list();
}

ChunkData* EditorVoxelWorld::get_chunk(Vector3i position)
{
	if (chunks.has(position))
	{
		return Object::cast_to<ChunkData>(chunks[position]);
	}
	else
	{
		return nullptr;
	}
}

void EditorVoxelWorld::_update_chunk_list()
{
	int x_min = UtilityFunctions::mini(world_bounds.position.x, world_bounds.get_end().x);
	int y_min = UtilityFunctions::mini(world_bounds.position.y, world_bounds.get_end().y);
	int z_min = UtilityFunctions::mini(world_bounds.position.z, world_bounds.get_end().z);
	int x_max = UtilityFunctions::maxi(world_bounds.position.x, world_bounds.get_end().x);
	int y_max = UtilityFunctions::maxi(world_bounds.position.y, world_bounds.get_end().y);
	int z_max = UtilityFunctions::maxi(world_bounds.position.z, world_bounds.get_end().z);

	Array keys = chunks.keys();

	// clean up old chunks
	for (int i = 0; i < keys.size(); i++)
	{
		Vector3i position = keys[i];

		if (position.x < x_min || position.x >= x_max || position.y < y_min || position.y >= y_max || position.z < z_min || position.z >= z_max)
		{
			ChunkData* chunk = Object::cast_to<ChunkData>(chunks[position]);
			chunks.erase(position);
			Object::free(nullptr, chunk);
		}
	}

	// get voxel set for filling chunks
	Ref<VoxelSet> voxel_set = get_voxel_set();
	ERR_FAIL_COND_MSG(!voxel_set.is_valid(), "Voxel Set for filling Chunks wasn't found");

	// create new chunks
	for (int x = x_min; x < x_max; x++)
	{
		for (int y = y_min; y < y_max; y++)
		{
			for (int z = z_min; z < z_max; z++)
			{
				Vector3i position(x, y, z);

				if (chunks.has(position))
				{
					continue;
				}

				ChunkData* chunk = memnew(ChunkData);
				chunk->set_chunk_size(get_chunk_size());
				chunks[position] = chunk;
				for (int x = 0; x < get_chunk_size(); x++)
				{
					for (int y = 0; y < get_chunk_size(); y++)
					{
						for (int z = 0; z < get_chunk_size(); z++)
						{
							Voxel* voxel = Object::cast_to<Voxel>(voxel_set->voxels[0]);
							chunk->set_voxel(Vector3i(x, y, z), voxel);
						}
					}
				}
				// end filling chunk
			}
		}
	}
}

void EditorVoxelWorld::_bind_methods()
{
	// world_bounds
	ClassDB::bind_method(D_METHOD("get_world_bounds"), &EditorVoxelWorld::get_world_bounds);
	ClassDB::bind_method(D_METHOD("set_world_bounds", "world_bounds"), &EditorVoxelWorld::set_world_bounds);
	ADD_PROPERTY(PropertyInfo(Variant::AABB, "world_bounds"), "set_world_bounds", "get_world_bounds");
}

bool EditorVoxelWorld::_set(const StringName &p_name, const Variant &p_value)
{
	PackedStringArray components = p_name.split("/");

	if (components[0] == "chunks")
	{
		String position_string = components[1];
		PackedStringArray position_components = position_string.split("_");
		Vector3i position = Vector3i(position_components[0].to_int(), position_components[1].to_int(), position_components[2].to_int());

		ChunkData* chunk = nullptr;

		if (chunks.has(position))
		{
			chunk = Object::cast_to<ChunkData>(chunks[position]);
		}
		else
		{
			// create new chunk
			chunk = memnew(ChunkData);
			chunks[position] = chunk;
		}

		if (chunk == nullptr)
		{
			UtilityFunctions::push_error("Error while setting chunk property: Chunk not found");
			return false;
		}
		else if (components[2] == "data")
		{
			chunk->set_voxels(p_value);
			chunk->set_chunk_size(get_chunk_size());
			return true;
		}
	}

    return false;
}

bool EditorVoxelWorld::_get(const StringName &p_name, Variant &r_ret) const
{
	PackedStringArray components = p_name.split("/");

    if (components[0] == "chunks")
    {
		String position_string = components[1];
		PackedStringArray position_components = position_string.split("_");
		Vector3i position = Vector3i(position_components[0].to_int(), position_components[1].to_int(), position_components[2].to_int());

		ChunkData* chunk = Object::cast_to<ChunkData>(chunks[position]);
		if (chunk == nullptr)
		{
			UtilityFunctions::printerr("Error while getting chunk property: Chunk not found");
			return false;
		}

		else if (components[2] == "data")
		{
			r_ret = chunk->get_voxels();
			return true;
		}
    }
    return false;
}

void EditorVoxelWorld::_get_property_list(List<PropertyInfo> *p_list) const
{
	int x_min = UtilityFunctions::mini(world_bounds.position.x, world_bounds.get_end().x);
	int y_min = UtilityFunctions::mini(world_bounds.position.y, world_bounds.get_end().y);
	int z_min = UtilityFunctions::mini(world_bounds.position.z, world_bounds.get_end().z);
	int x_max = UtilityFunctions::maxi(world_bounds.position.x, world_bounds.get_end().x);
	int y_max = UtilityFunctions::maxi(world_bounds.position.y, world_bounds.get_end().y);
	int z_max = UtilityFunctions::maxi(world_bounds.position.z, world_bounds.get_end().z);

    for (int x = x_min; x < x_max; x++)
	{
		for (int y = y_min; y < y_max; y++)
		{
			for (int z = z_min; z < z_max; z++)
			{
				Vector3i position(x, y, z);

				if (chunks.has(position))
				{
					ChunkData* chunk = Object::cast_to<ChunkData>(chunks[position]);
					String name = String("chunks/") + String::num(x) + String("_") + String::num(y) + String("_") + String::num(z);
					p_list->push_back(PropertyInfo(Variant::ARRAY, name + String("/data"), PROPERTY_HINT_NONE, "", PROPERTY_USAGE_NO_EDITOR));
				}
			}
		}
	}
}

bool EditorVoxelWorld::_property_can_revert(const StringName &p_name) const
{
    return false;
}

bool EditorVoxelWorld::_property_get_revert(const StringName &p_name, Variant &r_property) const
{
    return false;
}

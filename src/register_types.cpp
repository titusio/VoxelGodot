#include "register_types.h"

#include <gdextension_interface.h>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/godot.hpp>

#include "voxel.hpp"
#include "voxel_world_instance.hpp"
#include "voxel_world.hpp"

// Editor Plugins
#include "voxel_world_instance_editor_plugin.hpp"

using namespace godot;

void voxel_godot_initialize(ModuleInitializationLevel p_level)
{
	if (p_level == MODULE_INITIALIZATION_LEVEL_EDITOR)
	{
		ClassDB::register_class<Voxel>();
		ClassDB::register_class<VoxelWorld>();
		ClassDB::register_class<VoxelWorldInstance>();

		// Editor Plugins
		ClassDB::register_class<VoxelWorldInstanceEditorPlugin>();
		ClassDB::register_class<VoxelWorldInstanceEditor>();
		EditorPlugins::add_by_type<VoxelWorldInstanceEditorPlugin>();
	}
}

void voxel_godot_terminate(ModuleInitializationLevel p_level)
{
	if (p_level == MODULE_INITIALIZATION_LEVEL_SCENE)
	{
	}
}

extern "C"
{
	GDExtensionBool GDE_EXPORT voxel_godot_init(GDExtensionInterfaceGetProcAddress p_get_proc_address, const GDExtensionClassLibraryPtr p_library, GDExtensionInitialization *r_initialization)
	{
		godot::GDExtensionBinding::InitObject init_obj(p_get_proc_address, p_library, r_initialization);

		init_obj.register_initializer(voxel_godot_initialize);
		init_obj.register_terminator(voxel_godot_terminate);
		init_obj.set_minimum_library_initialization_level(MODULE_INITIALIZATION_LEVEL_EDITOR);

		return init_obj.init();
	}
}

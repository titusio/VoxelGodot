#include "register_types.h"

#include <gdextension_interface.h>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/godot.hpp>

#include "my_node.hpp"
#include "my_singleton.hpp"

using namespace godot;

static MySingleton *_my_singleton;

void voxel_godot_initialize(ModuleInitializationLevel p_level)
{
	if (p_level == MODULE_INITIALIZATION_LEVEL_SCENE)
	{
		ClassDB::register_class<MyNode>();
		ClassDB::register_class<MySingleton>();

		_my_singleton = memnew(MySingleton);
		Engine::get_singleton()->register_singleton("MySingleton", MySingleton::get_singleton());
	}
}

void voxel_godot_terminate(ModuleInitializationLevel p_level)
{
	if (p_level == MODULE_INITIALIZATION_LEVEL_SCENE)
	{
		Engine::get_singleton()->unregister_singleton("MySingleton");
		memdelete(_my_singleton);
	}
}

extern "C"
{
	GDExtensionBool GDE_EXPORT example_library_init(GDExtensionInterfaceGetProcAddress p_get_proc_address, const GDExtensionClassLibraryPtr p_library, GDExtensionInitialization *r_initialization)
	{
		godot::GDExtensionBinding::InitObject init_obj(p_get_proc_address, p_library, r_initialization);

		init_obj.register_initializer(voxel_godot_initialize);
		init_obj.register_terminator(voxel_godot_terminate);
		init_obj.set_minimum_library_initialization_level(MODULE_INITIALIZATION_LEVEL_SCENE);

		return init_obj.init();
	}
}

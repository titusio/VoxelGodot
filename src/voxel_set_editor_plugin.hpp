#ifndef VOXEL_SET_EDITOR_PLUGIN_HPP
#define VOXEL_SET_EDITOR_PLUGIN_HPP

#include <godot_cpp/classes/editor_plugin.hpp>
#include <godot_cpp/classes/control.hpp>	
#include <godot_cpp/classes/h_box_container.hpp>
#include <godot_cpp/classes/v_box_container.hpp>
#include <godot_cpp/classes/item_list.hpp>
#include <godot_cpp/classes/button.hpp>

#include "voxel_set.hpp"

namespace godot 
{
	class VoxelSetEditor : public Control
	{
		GDCLASS(VoxelSetEditor, Control);

		friend class VoxelSetEditorPlugin;

	private:
		VoxelSet *voxel_set;

		HBoxContainer *hbox_container;

		// left panel
		VBoxContainer *left_panel;
		ItemList *item_list;
		HBoxContainer *button_container;
		Button *add_button;
		Button *remove_button;

		Control *middle_panel;
		Control *right_panel;
	
	public:
		VoxelSetEditor();
		~VoxelSetEditor();
	
	private:
		void _init_items();
		void _add_item();
		void _remove_item();
		void _edit(VoxelSet *p_voxel_set);
	
	protected:
		static void _bind_methods();
	};

	class VoxelSetEditorPlugin : public EditorPlugin
	{
		GDCLASS(VoxelSetEditorPlugin, EditorPlugin);

	private:
		VoxelSetEditor *voxel_set_editor;

	public:
		VoxelSetEditorPlugin();
		~VoxelSetEditorPlugin();

		virtual String _get_plugin_name() const override;
        virtual void _edit(Object *p_object) override;
        virtual bool _handles(Object *p_object) const override;
        virtual void _make_visible(bool p_visible) override;
	
	protected:
		static void _bind_methods();

	};
}

#endif // VOXEL_SET_EDITOR_PLUGIN_HPP


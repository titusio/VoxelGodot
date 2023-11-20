#ifndef VOXEL_SET_EDITOR_PLUGIN_HPP
#define VOXEL_SET_EDITOR_PLUGIN_HPP

#include <godot_cpp/classes/editor_plugin.hpp>
#include <godot_cpp/classes/control.hpp>	
#include <godot_cpp/classes/h_box_container.hpp>
#include <godot_cpp/classes/v_box_container.hpp>
#include <godot_cpp/classes/item_list.hpp>
#include <godot_cpp/classes/button.hpp>
#include <godot_cpp/classes/label.hpp>
#include <godot_cpp/classes/line_edit.hpp>
#include <godot_cpp/classes/color_picker_button.hpp>
#include <godot_cpp/classes/check_button.hpp>
#include <godot_cpp/classes/sub_viewport.hpp>
#include <godot_cpp/classes/sub_viewport_container.hpp>

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

		// properties panel
		VBoxContainer *properties_panel;
		HBoxContainer *name_container;
		Label *name_label;
		LineEdit *name_line_edit;
		HBoxContainer *color_container;
		Label *color_label;
		ColorPickerButton *color_picker_button;
		CheckButton *is_solid_check;

		Control *preview_container;
		SubViewportContainer *preview_sub_viewport_container;
		SubViewport *preview_sub_viewport;

	
	public:
		VoxelSetEditor();
		~VoxelSetEditor();
	
	private:
		void _init_items();
		void _ensure_selection();
		void _update_items();
		void _add_item();
		void _remove_item();
		void _edit(VoxelSet *p_voxel_set);
		void _on_item_selected(int p_index);
		void _voxel_name_changed(String p_name);
		void _voxel_is_solid_changed(bool p_is_solid);
		void _voxel_color_changed(Color p_color);
	
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


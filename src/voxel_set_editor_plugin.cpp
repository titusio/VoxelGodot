#include "voxel_set_editor_plugin.hpp"

#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

VoxelSetEditor::VoxelSetEditor()
{
	set_v_size_flags(SIZE_EXPAND_FILL);

	// create base for Container
	hbox_container = memnew(HBoxContainer);
	add_child(hbox_container);
	hbox_container->set_anchors_preset(Control::PRESET_FULL_RECT);

	// create left panel
	left_panel = memnew(VBoxContainer);
	left_panel->set_h_size_flags(SIZE_EXPAND_FILL);
	hbox_container->add_child(left_panel);
	
	// create buttons
	button_container = memnew(HBoxContainer);
	left_panel->add_child(button_container);

	// add button
	add_button = memnew(Button);
	add_button->set_text("Add Item");
	add_button->set_h_size_flags(SIZE_EXPAND_FILL);
	add_button->connect("pressed", callable_mp(this, &VoxelSetEditor::_add_item));
	button_container->add_child(add_button);

	// remove button
	remove_button = memnew(Button);
	remove_button->set_text("Remove Item");
	remove_button->set_h_size_flags(SIZE_EXPAND_FILL);
	remove_button->connect("pressed", callable_mp(this, &VoxelSetEditor::_remove_item));
	button_container->add_child(remove_button);

	// create ItemList
	item_list = memnew(ItemList);
	item_list->set_v_size_flags(SIZE_EXPAND_FILL);
	left_panel->add_child(item_list);

	// add 2nd panel
	middle_panel = memnew(Control);
	middle_panel->set_h_size_flags(SIZE_EXPAND_FILL);
	hbox_container->add_child(middle_panel);

	// add 3rd panel
	right_panel = memnew(Control);
	right_panel->set_h_size_flags(SIZE_EXPAND_FILL);
	hbox_container->add_child(right_panel);
}

VoxelSetEditor::~VoxelSetEditor()
{

}

void VoxelSetEditor::_init_items()
{
	if (voxel_set == nullptr)
	{
		return;
	}
	
	// remove old items
	item_list->clear();
	
	// add items
	for (int i = 0; i < voxel_set->voxels.size(); i++)
	{
		Voxel *voxel = Object::cast_to<Voxel>(voxel_set->voxels[i]);
		if (voxel == nullptr)
			continue;
		
		if (voxel->get_name() == StringName(""))
			item_list->add_item(StringName("Untitled Voxel"));
		else
			item_list->add_item(voxel->get_name());
	}
}

void VoxelSetEditor::_add_item()
{
	ERR_FAIL_NULL_MSG(voxel_set, "No VoxelSet Selected");
	item_list->add_item("Item " + String::num(item_list->get_item_count() + 1));
	voxel_set->voxels.append(memnew(Voxel));
}

void VoxelSetEditor::_remove_item()
{
	bool has_focus = item_list->is_anything_selected();
	if (!has_focus)
	{
		return;	
	}

	PackedInt32Array selected = item_list->get_selected_items();

	for (int i = selected.size() - 1; i <= 0; i++)
	{
		item_list->remove_item(selected[i]);
		voxel_set->voxels.remove_at(selected[i]);
	}

}

void VoxelSetEditor::_edit(VoxelSet *p_voxel_set)
{
	voxel_set = p_voxel_set;
}

void VoxelSetEditor::_bind_methods()
{
}

VoxelSetEditorPlugin::VoxelSetEditorPlugin()
{
	voxel_set_editor = memnew(VoxelSetEditor);
}

VoxelSetEditorPlugin::~VoxelSetEditorPlugin()
{
	remove_control_from_bottom_panel(voxel_set_editor);
}

String VoxelSetEditorPlugin::_get_plugin_name() const 
{
	return "VoxelSetEditorPlugin";
}

void VoxelSetEditorPlugin::_edit(Object *p_object) 
{
	voxel_set_editor->_edit(Object::cast_to<VoxelSet>(p_object));
	voxel_set_editor->_init_items();
}

bool VoxelSetEditorPlugin::_handles(Object *p_object) const
{
	return p_object->is_class("VoxelSet");
}

void VoxelSetEditorPlugin::_make_visible(bool p_visible)
{
	if (p_visible)
	{
		add_control_to_bottom_panel(voxel_set_editor, "VoxelSetEditor");
	}
	else
	{
		remove_control_from_bottom_panel(voxel_set_editor);
	}
}

void VoxelSetEditorPlugin::_bind_methods()
{
}

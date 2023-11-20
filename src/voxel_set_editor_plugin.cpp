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
	item_list->connect("item_selected", callable_mp(this, &VoxelSetEditor::_on_item_selected));
	left_panel->add_child(item_list);

	// properties panel
	properties_panel = memnew(VBoxContainer);
	properties_panel->set_h_size_flags(SIZE_EXPAND_FILL);
	hbox_container->add_child(properties_panel);

	// name property
	name_container = memnew(HBoxContainer);
	properties_panel->add_child(name_container);
	name_label = memnew(Label);
	name_label->set_text("Voxel Name");
	name_label->set_h_size_flags(SIZE_EXPAND_FILL);
	name_container->add_child(name_label);
	name_line_edit = memnew(LineEdit);
	name_line_edit->set_h_size_flags(SIZE_EXPAND_FILL);
	name_container->add_child(name_line_edit);

	// color property
	color_container = memnew(HBoxContainer);
	properties_panel->add_child(color_container);
	color_label = memnew(Label);
	color_label->set_text("Voxel Color");
	color_label->set_h_size_flags(SIZE_EXPAND_FILL);
	color_container->add_child(color_label);
	color_picker_button = memnew(ColorPickerButton);
	color_picker_button->set_h_size_flags(SIZE_EXPAND_FILL);
	color_picker_button->set_pick_color(Color(1, 1, 1, 1));
	color_container->add_child(color_picker_button);

	// is_solid property
	is_solid_check = memnew(CheckButton);
	is_solid_check->set_text("Is Solid");
	is_solid_check->set_h_size_flags(SIZE_EXPAND_FILL);
	properties_panel->add_child(is_solid_check);

	// properties signals
	name_line_edit->connect("text_changed", callable_mp(this, &VoxelSetEditor::_voxel_name_changed));
	color_picker_button->connect("color_changed", callable_mp(this, &VoxelSetEditor::_voxel_color_changed));
	is_solid_check->connect("toggled", callable_mp(this, &VoxelSetEditor::_voxel_is_solid_changed));

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

void VoxelSetEditor::_ensure_selection()
{
	if (voxel_set == nullptr)
	{
		return;
	}

	if (item_list->get_item_count() == 0)
		properties_panel->hide();
	else 
		properties_panel->show();

	if (!item_list->is_anything_selected() && item_list->get_item_count() != 0)
	{
		item_list->select(0);
		// because the signal is not emitted when selecting the item manually
		_on_item_selected(0);
	}
}

void VoxelSetEditor::_update_items()
{
	if (voxel_set == nullptr || !item_list->is_anything_selected())
		return;
	
	if (item_list->get_item_count() == 0) return;

	int selected_item = item_list->get_selected_items()[0];
	_init_items();
	item_list->select(selected_item);
}

void VoxelSetEditor::_add_item()
{
	ERR_FAIL_NULL_MSG(voxel_set, "No VoxelSet Selected");
	item_list->add_item("Item " + String::num(item_list->get_item_count() + 1));
	voxel_set->voxels.append(memnew(Voxel));
	_ensure_selection();
	_update_items();
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

	_update_items();
	_ensure_selection();
}

void VoxelSetEditor::_edit(VoxelSet *p_voxel_set)
{
	voxel_set = p_voxel_set;
}

void VoxelSetEditor::_on_item_selected(int p_index)
{
	if (voxel_set == nullptr)
	{
		return;
	}

	Voxel *voxel = Object::cast_to<Voxel>(voxel_set->voxels[p_index]);
	if (voxel == nullptr)
	{
		return;
	}

	name_line_edit->set_text(voxel->get_name());
	color_picker_button->set_pick_color(voxel->get_color());
	is_solid_check->set_pressed(voxel->get_is_empty());

	_ensure_selection();
}

void VoxelSetEditor::_voxel_name_changed(String p_name) 
{
	if (voxel_set == nullptr || !item_list->is_anything_selected())
		return;

	Array selected_items = item_list->get_selected_items();
	for (int i = 0; i < selected_items.size(); i++)
	{
		Voxel *voxel = Object::cast_to<Voxel>(voxel_set->voxels[selected_items[i]]);
		if (voxel == nullptr)
			continue;
		voxel->set_name(p_name);

		UtilityFunctions::print("Voxel Name Changed: " + p_name);
	}

	_update_items();
}

void VoxelSetEditor::_voxel_is_solid_changed(bool p_is_solid)
{
	if (voxel_set == nullptr || !item_list->is_anything_selected())
		return;

	Array selected_items = item_list->get_selected_items();
	for (int i = 0; i < selected_items.size(); i++)
	{
		Voxel *voxel = Object::cast_to<Voxel>(voxel_set->voxels[selected_items[i]]);
		if (voxel == nullptr)
			continue;
		voxel->set_is_empty(p_is_solid);
	}

	_update_items();
}

void VoxelSetEditor::_voxel_color_changed(Color p_color)
{
	if (voxel_set == nullptr || !item_list->is_anything_selected())
		return;

	Array selected_items = item_list->get_selected_items();
	for (int i = 0; i < selected_items.size(); i++)
	{
		Voxel *voxel = Object::cast_to<Voxel>(voxel_set->voxels[selected_items[i]]);
		if (voxel == nullptr)
			continue;
		voxel->set_color(p_color);
	}

	_update_items();
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
	voxel_set_editor->_ensure_selection();
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

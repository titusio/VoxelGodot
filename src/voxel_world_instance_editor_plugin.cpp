#include "voxel_world_instance_editor_plugin.hpp"

#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/editor_interface.hpp>
#include <godot_cpp/classes/popup_menu.hpp>
#include <godot_cpp/classes/editor_interface.hpp>

namespace godot
{

    VoxelWorldInstanceEditor::VoxelWorldInstanceEditor()
    {
        options = memnew(MenuButton);
        options->set_text("Voxel World Instance");
        options->set_switch_on_hover(true);
        add_child(options);

        options->get_popup()->add_item("Generate", GENERATE);
        options->get_popup()->add_item("Clear", CLEAR);

        options->get_popup()->connect("id_pressed", callable_mp(this, &VoxelWorldInstanceEditor::_options));
    }

    VoxelWorldInstanceEditor::~VoxelWorldInstanceEditor()
    {
    }

    void VoxelWorldInstanceEditor::edit(VoxelWorldInstance *p_instance)
    {
        instance = p_instance;
    }

    void VoxelWorldInstanceEditor::_options(int p_option)
    {
        if (instance == nullptr)
        {
            return;
        }

        switch (p_option)
        {
        case GENERATE:
            ERR_FAIL_NULL_MSG(instance, "Voxel World Instance is Null");
            // instance->generate();
            break;
        case CLEAR:
            ERR_FAIL_NULL_MSG(instance, "Voxel World Instance is Null");
            // instance->clear();
            break;
        }
    }

    void VoxelWorldInstanceEditor::_bind_methods()
    {
    }

    void VoxelWorldInstanceEditor::_notification(int p_what)
    {
        switch (p_what)
        {
        case NOTIFICATION_ENTER_TREE:
        case NOTIFICATION_THEME_CHANGED:
        {
            options->set_button_icon(EditorInterface::get_singleton()->get_base_control()->get_theme_icon("VoxelWorldInstance", "EditorIcons"));
        }
        break;
        }
    }

    VoxelWorldInstanceEditorPlugin::VoxelWorldInstanceEditorPlugin()
    {
        editor = memnew(VoxelWorldInstanceEditor);
        add_control_to_container(CONTAINER_SPATIAL_EDITOR_MENU, editor);
        _make_visible(false);
    }

    VoxelWorldInstanceEditorPlugin::~VoxelWorldInstanceEditorPlugin()
    {
    }

    String VoxelWorldInstanceEditorPlugin::_get_plugin_name() const
    {
        return String("VoxelWorldInstanceEditorPlugin");
    }

    void VoxelWorldInstanceEditorPlugin::_edit(Object *p_object)
    {
        editor->edit(Object::cast_to<VoxelWorldInstance>(p_object));
    }

    bool VoxelWorldInstanceEditorPlugin::_handles(Object *p_object) const
    {
        return p_object->is_class("VoxelWorldInstance");
    }

    void VoxelWorldInstanceEditorPlugin::_make_visible(bool p_visible)
    {
        if (p_visible)
        {
            editor->show();
        }
        else
        {
            editor->hide();
            editor->edit(nullptr);
        }
    }

    void VoxelWorldInstanceEditorPlugin::_bind_methods()
    {
        // Empty implementation
    }
}

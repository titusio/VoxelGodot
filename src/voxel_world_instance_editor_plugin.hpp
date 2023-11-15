#ifndef VOXEL_WORLD_INSTANCE_EDITOR_PLUGIN_HPP
#define VOXEL_WORLD_INSTANCE_EDITOR_PLUGIN_HPP

#include <godot_cpp/classes/editor_plugin.hpp>
#include <godot_cpp/classes/control.hpp>
#include <godot_cpp/classes/menu_button.hpp>

#include "voxel_world_instance.hpp"

namespace godot
{
    class VoxelWorldInstanceEditor : public Control
    {
        GDCLASS(VoxelWorldInstanceEditor, Control);
        friend class VoxelWorldInstanceEditorPlugin;

    private:
        enum MenuOptions
        {
            GENERATE,
            CLEAR
        };

        VoxelWorldInstance *instance;
        MenuButton *options;

    public:
        VoxelWorldInstanceEditor();
        ~VoxelWorldInstanceEditor();

        void edit(VoxelWorldInstance *p_instance);

    private:
        void _options(int p_option);

    protected:
        static void _bind_methods();
        void _notification(int p_what);
    };

    class VoxelWorldInstanceEditorPlugin : public EditorPlugin
    {
        GDCLASS(VoxelWorldInstanceEditorPlugin, EditorPlugin);

    private:
        VoxelWorldInstanceEditor *editor;

    public:
        VoxelWorldInstanceEditorPlugin();
        ~VoxelWorldInstanceEditorPlugin();

        virtual String _get_plugin_name() const override;
        virtual void _edit(Object *p_object) override;
        virtual bool _handles(Object *p_object) const override;
        virtual void _make_visible(bool p_visible) override;

    protected:
        static void _bind_methods();
    };
}

#endif // VOXEL_WORLD_INSTANCE_EDITOR_PLUGIN_HPP
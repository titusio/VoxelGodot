#ifndef VOXEL_HPP
#define VOXEL_HPP

#include <godot_cpp/classes/resource.hpp>
#include <godot_cpp/variant/color.hpp>

namespace godot
{
    class Voxel : public Resource
    {
        GDCLASS(Voxel, Resource)

    private:
		int id;
		StringName name;
        Color color;
        bool is_empty;

    public:
        Voxel();
        ~Voxel();

		// id
		int get_id() const;
		void set_id(int p_id);

		//name
		StringName get_name() const;
		void set_name(StringName p_name);
		// color
		void set_color(Color p_color);
        Color get_color() const;
		// empty
		bool get_is_empty() const;
		void set_is_empty(bool p_is_empty);

    protected:
        static void _bind_methods();
		bool _property_can_revert(const StringName &p_name) const;
        bool _property_get_revert(const StringName &p_name, Variant &r_property) const;

	};

} // namespace godot

#endif // VOXEL_HPP

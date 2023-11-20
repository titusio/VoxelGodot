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
		StringName name;
        Color color;
        bool is_empty;

    public:
        Voxel();
        ~Voxel();

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
	};

} // namespace godot

#endif // VOXEL_HPP

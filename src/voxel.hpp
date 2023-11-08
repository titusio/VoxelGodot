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
        Color color;
        bool is_empty;

	public:
		Voxel();
		~Voxel();

    protected:
        static void _bind_methods();

    public:
        void set_color(Color p_color);
        Color get_color() const;
    };

} // namespace godot

#endif // VOXEL_HPP

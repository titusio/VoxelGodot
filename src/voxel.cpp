#include "voxel.hpp"

using namespace godot;

Voxel::Voxel()
{
    color = Color(1.0f, 1.0f, 1.0f, 1.0f);
    is_empty = false;
}

Voxel::~Voxel()
{
}

void Voxel::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("set_color", "color"), &Voxel::set_color);
    ClassDB::bind_method(D_METHOD("get_color"), &Voxel::get_color);

    ADD_PROPERTY(PropertyInfo(Variant::COLOR, "color"), "set_color", "get_color");
}

void Voxel::set_color(Color p_color)
{
    color = p_color;
}

Color Voxel::get_color() const
{
    return color;
}

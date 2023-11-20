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
	// name
	ClassDB::bind_method(D_METHOD("set_name", "name"), &Voxel::set_name);
	ClassDB::bind_method(D_METHOD("get_name"), &Voxel::get_name);
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "name"), "set_name", "get_name");
	// color
    ClassDB::bind_method(D_METHOD("set_color", "color"), &Voxel::set_color);
    ClassDB::bind_method(D_METHOD("get_color"), &Voxel::get_color);
    ADD_PROPERTY(PropertyInfo(Variant::COLOR, "color"), "set_color", "get_color");
	// empty
	ClassDB::bind_method(D_METHOD("set_is_empty", "is_empty"), &Voxel::set_is_empty);
	ClassDB::bind_method(D_METHOD("get_is_empty"), &Voxel::get_is_empty);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "is_empty"), "set_is_empty", "get_is_empty");
}

StringName Voxel::get_name() const
{
	return name;
}

void Voxel::set_name(StringName p_name)
{
	name = p_name;
}

void Voxel::set_color(Color p_color)
{
    color = p_color;
}

Color Voxel::get_color() const
{
    return color;
}

bool Voxel::get_is_empty() const
{
	return is_empty;
}

void Voxel::set_is_empty(bool p_is_empty)
{
	is_empty = p_is_empty;
}


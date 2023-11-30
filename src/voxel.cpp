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

StringName Voxel::get_name() const
{
	return name;
}

int Voxel::get_id() const
{
	return id;
}

void Voxel::set_id(int p_id)
{
	id = p_id;
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

void Voxel::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("get_id"), &Voxel::get_id);
	ClassDB::bind_method(D_METHOD("set_id", "id"), &Voxel::set_id);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "id"), "set_id", "get_id");
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

bool Voxel::_property_can_revert(const StringName &p_name) const
{
	if (p_name == StringName("name"))
	{
		return true;
	}
	else if (p_name == StringName("color"))
	{
		return true;
	}
	else if (p_name == StringName("is_empty"))
	{
		return true;
	}

	return false;
}

bool Voxel::_property_get_revert(const StringName &p_name, Variant &r_property) const
{
	if (p_name == StringName("name"))
	{
		r_property = "Voxel";
		return true;
	}
	if (p_name == StringName("color"))
	{
		r_property = Color(1.0f, 1.0f, 1.0f, 1.0f);
		return true;
	}
	if (p_name == StringName("is_empty"))
	{
		r_property = false;
		return true;
	}

	return false;
}



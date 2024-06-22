#pragma once

#include <godot_cpp/classes/object.hpp>
#include <godot_cpp/classes/ref_counted.hpp>

namespace godot {

class KeyValues : public RefCounted {
	GDCLASS(KeyValues, RefCounted); // NOLINT(*-default-arguments, *-use-auto)

public:
	KeyValues();

protected:
	static void _bind_methods();
};

class KeyValuesElement : public Object {
	GDCLASS(KeyValuesElement, Object); // NOLINT(*-default-arguments, *-use-auto)

public:
	KeyValuesElement();

	explicit KeyValuesElement(const Ref<KeyValues>& keyvalues_);

protected:
	static void _bind_methods();

private:
	Ref<KeyValues> keyvalues = nullptr;
};

} // namespace godot

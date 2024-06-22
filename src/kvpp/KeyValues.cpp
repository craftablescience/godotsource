#include "KeyValues.h"

#include <godot_cpp/core/class_db.hpp>

using namespace godot;

KeyValues::KeyValues() = default;

void KeyValues::_bind_methods() {
}

KeyValuesElement::KeyValuesElement() = default;

KeyValuesElement::KeyValuesElement(const Ref<KeyValues>& keyvalues_)
		: Object()
		, keyvalues(keyvalues_) {}

void KeyValuesElement::_bind_methods() {
}

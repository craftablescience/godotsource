#pragma once

#include <godot_cpp/core/object.hpp>

namespace godot {

class VFONT : public Object {
	GDCLASS(VFONT, Object) // NOLINT(*-default-arguments, *-use-auto)

public:
	VFONT() = default;

	[[nodiscard]] static PackedByteArray decrypt(const PackedByteArray& data, const String& code);

protected:
	static void _bind_methods();
};

} // namespace godot

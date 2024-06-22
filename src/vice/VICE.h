#pragma once

#include <godot_cpp/core/object.hpp>

namespace godot {

class VICE : public Object {
	GDCLASS(VICE, Object) // NOLINT(*-default-arguments, *-use-auto)

public:
	VICE() = default;

	[[nodiscard]] static PackedByteArray encrypt(const String& data, const String& code);

	[[nodiscard]] static PackedByteArray decrypt(const PackedByteArray& data, const String& code);

protected:
	static void _bind_methods();
};

} // namespace godot

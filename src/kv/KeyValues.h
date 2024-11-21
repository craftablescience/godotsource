#pragma once

#include <memory>

#include <godot_cpp/variant/array.hpp>
#include <godot_cpp/classes/ref_counted.hpp>
#include <kvpp/kvpp.h>

namespace godot {

struct KeyValuesElementData;

class KeyValuesElement : public RefCounted {
	GDCLASS(KeyValuesElement, RefCounted) // NOLINT(*-default-arguments, *-use-auto)

	friend class KeyValuesRoot;

public:
	KeyValuesElement() = default;

	String get_key() const; // NOLINT(*-use-nodiscard)

	String get_value() const; // NOLINT(*-use-nodiscard)

	String get_conditional() const; // NOLINT(*-use-nodiscard)

	bool has_child(const String& childKey) const; // NOLINT(*-use-nodiscard)

	uint64_t get_child_count() const; // NOLINT(*-use-nodiscard)

	uint64_t get_child_count_with_key(const String& childKey) const; // NOLINT(*-use-nodiscard)

	Array get_children() const; // NOLINT(*-use-nodiscard)

	Ref<KeyValuesElement> at_n(unsigned int index) const; // NOLINT(*-use-nodiscard)

	Ref<KeyValuesElement> at_k(const String& childKey) const; // NOLINT(*-use-nodiscard)

	Ref<KeyValuesElement> at_kn(const String& childKey, unsigned int n) const; // NOLINT(*-use-nodiscard)

	bool is_invalid() const; // NOLINT(*-use-nodiscard)

protected:
	void setData(const KeyValuesElementData& newData);

	static void _bind_methods();

	std::unique_ptr<KeyValuesElementData> data = nullptr;
};

class KeyValuesRoot : public RefCounted {
	GDCLASS(KeyValuesRoot, RefCounted) // NOLINT(*-default-arguments, *-use-auto)

	friend class KeyValuesElement;

public:
	KeyValuesRoot() = default;

	void load_file(const String& kvPath);

	void load_file_escaped(const String& kvPath);

	void load_str(const String& kvData);

	void load_str_escaped(const String& kvData);

	bool has_child(const String& childKey) const; // NOLINT(*-use-nodiscard)

	uint64_t get_child_count() const; // NOLINT(*-use-nodiscard)

	uint64_t get_child_count_with_key(const String& childKey) const; // NOLINT(*-use-nodiscard)

	Array get_children(); // NOLINT(*-use-nodiscard)

	Ref<KeyValuesElement> at_n(unsigned int index); // NOLINT(*-use-nodiscard)

	Ref<KeyValuesElement> at_k(const String& childKey); // NOLINT(*-use-nodiscard)

	Ref<KeyValuesElement> at_kn(const String& childKey, unsigned int n); // NOLINT(*-use-nodiscard)

	bool is_invalid() const; // NOLINT(*-use-nodiscard)

protected:
	static void _bind_methods();

	std::unique_ptr<kvpp::KV1> kv = nullptr;
};

struct KeyValuesElementData {
	// Template bullshit but it works
	const kvpp::KV1ElementBase<std::string_view, kvpp::KV1ElementReadable>& element;
};

} // namespace godot

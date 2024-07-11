#include "Convert.h"

#include <cstring>

using namespace godot;

PackedByteArray Convert::bufferToByteArray(std::span<const std::byte> buffer) {
	PackedByteArray data;
	data.resize(static_cast<int64_t>(buffer.size()));
	std::memcpy(data.ptrw(), buffer.data(), buffer.size());
	return data;
}

std::vector<std::byte> Convert::byteArrayToBuffer(const PackedByteArray& byteArray) {
	const auto* ptr = reinterpret_cast<const std::byte*>(byteArray.ptr());
	return {ptr, ptr + static_cast<uint64_t>(byteArray.size())};
}

String Convert::stringToGodot(std::string_view string) {
	return string.data();
}

std::string Convert::stringToStd(const String& string) {
	return string.utf8().get_data();
}

PackedStringArray Convert::stringArrayToGodot(const std::vector<std::string>& strings) {
	PackedStringArray array;
	for (const auto& s : strings) {
		array.push_back(stringToGodot(s));
	}
	return array;
}

std::vector<std::string> Convert::stringArrayToStd(const PackedStringArray& strings) {
	std::vector<std::string> array;
	for (const auto& s : strings) {
		array.push_back(stringToStd(s));
	}
	return array;
}

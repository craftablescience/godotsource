#pragma once

#include <tuple>

#include <godot_cpp/classes/file_access.hpp>
#include <godot_cpp/classes/image.hpp>
#include <godot_cpp/classes/image_format_loader_extension.hpp>
#include <vtfpp/vtfpp.h>

namespace godot {

class ImageLoaderVTF : public ImageFormatLoaderExtension {
	GDCLASS(ImageLoaderVTF, ImageFormatLoaderExtension) // NOLINT(*-default-arguments, *-use-auto)

public:
	ImageLoaderVTF() = default;

	[[nodiscard]] PackedStringArray _get_recognized_extensions() const override;

	[[nodiscard]] Error _load_image(const Ref<Image>& image, const Ref<FileAccess>& fileAccess, BitField<ImageFormatLoader::LoaderFlags> flags, double scale) override;

protected:
	static void _bind_methods();

	static std::pair<vtfpp::ImageFormat, Image::Format> getVTFTargetFormat(vtfpp::ImageFormat vtfFormat);
};

} // namespace godot

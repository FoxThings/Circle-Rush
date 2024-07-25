#include "Sprite.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

Sprite::Sprite(const std::string inputPath) {
	int32_t colorMode = static_cast<int32_t>(4);
	int     bpp = 0;

	uint8_t* data = stbi_load(inputPath.c_str(), &width, &height, &bpp, colorMode);

	image = (Pixel*)data;
	for (int i = 0; i < width * height; ++i) {
		Pixel current = image[i];
		Pixel converted = Pixel();

		converted.bgra.alpha = current.rgba.alpha;
		converted.bgra.red = current.rgba.red;
		converted.bgra.green = current.rgba.green;
		converted.bgra.blue = current.rgba.blue;

		image[i] = converted;
	}
}

Sprite::~Sprite()
{
	stbi_image_free(image);
}

Pixel Sprite::GetPixel(int x, int y) const
{
	return image[x * width + y];
}

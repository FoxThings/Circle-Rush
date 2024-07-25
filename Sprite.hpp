#pragma once

#include <cstdint>
#include <string>

union Pixel {
    struct {
        uint8_t blue;
        uint8_t green;
        uint8_t red;
        uint8_t alpha;
    } bgra;

    struct {
        uint8_t red;
        uint8_t green;
        uint8_t blue;
        uint8_t alpha;
    } rgba;

    uint32_t pixel;
};

class Sprite {
public:
	int32_t width;
	int32_t height;

	Sprite(const std::string inputPath);
	~Sprite();

	Pixel GetPixel(int x, int y) const;

private:
    Pixel* image;
};

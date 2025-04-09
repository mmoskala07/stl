#include "compression.hpp"
#include <iomanip>
#include <iostream>

static size_t constexpr VALUE = 0;
static size_t constexpr OCCURENCES = 1;

comp_img_t compressGrayscale(img_t image) {
    comp_img_t img_compressed;
    uint8_t img_value = image[0][0];
    uint8_t occurences = 0;

    for (size_t row = 0; row < image.size(); row++) {
        img_value = image[row][0];
        occurences = 0;

        for (size_t col = 0; col < image[0].size(); col++) {
            if (img_value == image[row][col]) {
                occurences++;
            } else {
                img_compressed.push_back(std::make_pair(img_value, occurences));
                img_value = image[row][col];
                occurences = 1;
            }
        }
        img_compressed.push_back(std::make_pair(img_value, occurences));
    }
    return img_compressed;
}

img_t decompressGrayscale(comp_img_t image_compressed) {
    img_t image;

    size_t idx = 0;
    uint8_t value = std::get<VALUE>(image_compressed[idx]);
    size_t occurs = std::get<OCCURENCES>(image_compressed[idx]);

    for (size_t row = 0; row < image.size(); row++) {
        for (size_t col = 0; col < image[0].size(); col++) {
            if (occurs == 0) {
                if (++idx < image_compressed.size()) {
                    value = std::get<VALUE>(image_compressed[idx]);
                    occurs = std::get<OCCURENCES>(image_compressed[idx]);

                    if (occurs == 0) {
                        throw std::invalid_argument("Occurences equal as zero. Compression was not done correctly");
                    }
                } else {
                    throw std::invalid_argument("Compressed image does not contain enough data");
                }
            }
            image[row][col] = value;
            occurs--;
        }
    }

    if (idx + 1 != image_compressed.size() || occurs != 0) {
        throw std::invalid_argument("Compressed image contains too many data");
    }

    return image;
}

void printMap(const std::array<std::array<uint8_t, 32>, 32>& img) {
    for (auto row : img) {
        for (auto pixel : row) {
            if (pixel == 0) {
                std::cout << "-";
            } else {
                std::cout << (unsigned char)pixel;
            }
        }
        std::cout << std::endl;
    }
}
#pragma once

#include <array>
#include <cstdint>
#include <stdexcept>
#include <utility>
#include <vector>

constexpr size_t width = 32;
constexpr size_t height = 32;

using img_t = std::array<std::array<uint8_t, width>, height>;
using comp_img_t = std::vector<std::pair<uint8_t, uint8_t>>;

comp_img_t compressGrayscale(img_t image);
img_t decompressGrayscale(comp_img_t image_compressed);

void printMap(const std::array<std::array<uint8_t, 32>, 32>& img);
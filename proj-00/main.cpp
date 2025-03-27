#include <iostream>
#include <fstream>
#include <memory>
#include <cstdint>

using byte = std::uint8_t;

void save_ppm6(const std::string &filename, const byte *buffer, size_t width, size_t height, short channels)
{
  std::ofstream fs(filename, std::ios::out);
  fs << "P3\n";
  fs << width << " " << height << '\n';
  fs << "255\n";

  size_t total_bytes{width * height * channels};

  for (size_t idx{0}; idx < total_bytes; idx += 3)
  {
    fs << (short)buffer[idx + 0] << " " << (short)buffer[idx + 1] << " " << (short)buffer[idx + 2] << "\n";
  }

  fs.close();
}

int main()
{
  constexpr size_t width{400};
  constexpr size_t height{200};
  constexpr size_t channels{3};
  constexpr size_t total_bytes{width * height * channels};

  constexpr byte max_value{255};
  constexpr float blue_percentage{0.2};
  byte blue_channel_value{(byte)(blue_percentage * max_value)};

  std::unique_ptr<byte[]> image = std::make_unique<byte[]>(total_bytes);

  for (size_t row{0}; row < height; ++row)
  {
    float green_ratio = 1.0f - static_cast<float>(row) / (height - 1);
    byte green_channel_value = static_cast<byte>(green_ratio * max_value);
    for (size_t column{0}; column < width; ++column)
    {
      float red_ratio = static_cast<float>(column) / (width);
      byte red_channel_value = static_cast<byte>(red_ratio * max_value);
      size_t idx = (row * width + column) * channels;
      image[idx + 0] = red_channel_value;
      image[idx + 1] = green_channel_value;
      image[idx + 2] = blue_channel_value;
    }
  }

  save_ppm6("output.ppm", image.get(), width, height, channels);

  return 0;
}
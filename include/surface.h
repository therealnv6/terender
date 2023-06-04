#pragma once
#include <cstdint>
#include <iostream>
#include <stdint.h>
#include <vector>

namespace rend
{
	class surface
	{
	private:
		int height;
		int width;

	public:
		surface(int height, int width)
			: height(height)
			, width(width)
		{
			for (int i = 0; i < height; ++i)
			{
        std::vector<char> vec;

				for (int j = 0; j < width; ++j)
				{
          vec.push_back(' ');
				}

        chars.push_back(vec);
			}
		}

		void clear()
		{
			for (int i = 0; i < height; ++i)
			{
				for (int j = 0; j < width; ++j)
				{
					chars[i][j] = ' ';
				}
			}
		}

		void draw_at(int x, int y, char c)
		{
			if (x >= 0 && x < width && y >= 0 && y < height && chars[y][x] == ' ')
			{
				chars[y][x] = c;
			}
		}

		void render()
		{
			std::string output;
			for (int i = 0; i < height; ++i)
			{
				output.append(chars[i].data(), width);
				output.push_back('\n');
			}
			std::cout << "\033[2J\033[1;1H" << output;
		}

    std::pair<int, int> get_dimensions()
    {
      return std::make_pair(height, width);
    }

		std::vector<std::vector<char>> chars;
	};
}

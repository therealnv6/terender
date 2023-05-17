#pragma once
#include <cstdint>
#include <iostream>
#include <stdint.h>

namespace rend
{
	template<uint32_t HEIGHT, uint32_t WIDTH>
	class surface
	{
	public:
		surface()
		{
		}

		void clear()
		{
			for (int i = 0; i < HEIGHT; ++i)
			{
				for (int j = 0; j < WIDTH; ++j)
				{
					chars[i][j] = ' ';
				}
			}
		}

		void draw_at(int x, int y, char c)
		{
			if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
			{
				chars[y][x] = c;
			}
		}

		void render()
		{
			std::string output;
			for (int i = 0; i < HEIGHT; ++i)
			{
				output.append(chars[i], WIDTH);
				output.push_back('\n');
			}
			std::cout << "\033[2J\033[1;1H" << output;
		}

		char chars[HEIGHT][WIDTH];
	};
}

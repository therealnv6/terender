#pragma once
#include <algorithm>
#include <array>
#include <iostream>
#include <math.h>
#include <surface.h>

namespace rend
{

	template<uint32_t HEIGHT, uint32_t WIDTH>
	class line
	{
	public:
		line(rend::surface<HEIGHT, WIDTH> &surface, std::array<int, 2> loc, std::array<int, 2> loc2)
		{
			int x1 = loc[0];
			int y1 = loc[1];
			int x2 = loc2[0];
			int y2 = loc2[1];

			int dx = abs(x2 - x1);
			int dy = abs(y2 - y1);
			int sx = (x1 < x2) ? 1 : -1;
			int sy = (y1 < y2) ? 1 : -1;
			int err = dx - dy;

			while (true)
			{
				surface.draw_at(x1, y1, '*');

				if (x1 == x2 && y1 == y2)
					break;

				int err2 = 2 * err;

				if (err2 > -dy)
				{
					err -= dy;
					x1 += sx;
				}

				if (err2 < dx)
				{
					err += dx;
					y1 += sy;
				}
			}
		}
	};

	template<uint32_t HEIGHT, uint32_t WIDTH>
	class line3d
	{
	public:
		line3d(rend::surface<HEIGHT, WIDTH> &surface, std::array<double, 3> loc, std::array<double, 3> loc2)
		{
			int x1 = static_cast<int>(loc[0]);
			int y1 = static_cast<int>(loc[1]);
			int z1 = static_cast<int>(loc[2]);
			int x2 = static_cast<int>(loc2[0]);
			int y2 = static_cast<int>(loc2[1]);
			int z2 = static_cast<int>(loc2[2]);

			int dx = std::abs(x2 - x1);
			int dy = std::abs(y2 - y1);
			int dz = std::abs(z2 - z1);
			int sx = x1 < x2 ? 1 : -1;
			int sy = y1 < y2 ? 1 : -1;
			int sz = z1 < z2 ? 1 : -1;
			int err1 = dx - dy;
			int err2 = dx - dz;

			int max_iter = 100000;

			while (max_iter-- > 0 && (std::abs(x1 - x2) > 1 || std::abs(y1 - y2) > 1 || std::abs(z1 - z2) > 1))
			{
				// Apply perspective transformation
				double distance = std::sqrt(std::pow(x2 - x1, 2) + std::pow(y2 - y1, 2) + std::pow(z2 - z1, 2));
				double depth = 1.0 - z1 / (distance + 1.0);
				int screen_x = static_cast<int>((x1 + 1) * (WIDTH - 1) / 2);
				int screen_y = static_cast<int>((y1 + 1) * (HEIGHT - 1) / 2);

				// Determine the character based on the distance
				char character = get_char_at_dist(distance);
				char depthChar = get_char_at_depth(character, depth);

				// Draw the point on the surface
				surface.draw_at(screen_x, screen_y, depthChar);

				int e2 = 2 * err1;
				int e3 = 2 * err2;

				if (e2 > -dy && (e2 < 0 || e3 > -dy))
				{
					err1 -= dy;
					err2 -= dz;
					x1 += sx;
					y1 += sy;
					z1 += sz;
				}
				else if (e2 < dx && (e2 > 0 || e3 < dx))
				{
					err1 += dy;
					err2 += dz;
					y1 += sy;
					z1 += sz;
				}
				else
				{
					err1 += dy - dx;
					err2 += dz - dx;
					x1 += sx;
				}
			}
		}

	private:
		// Helper function to determine the character based on the distance
		char get_char_at_dist(double distance)
		{
			// Define the characters to be used for different distance ranges
			const std::array<char, 4> characters = { ' ', '.', '*', '#' };

			// Determine the index based on the distance range
			int index = static_cast<int>(std::min(distance / 10.0, static_cast<double>(characters.size() - 1)));

			return characters[index];
		}

		// Helper function to determine the character based on the depth (perspective effect)
		char get_char_at_depth(char character, double depth)
		{
			// Define the characters to be used for different depth ranges
			const std::array<char, 4> characters = { ' ', '.', '#', '#' };

			// Determine the index based on the depth range
			int index = static_cast<int>(depth * (characters.size() - 1));

			// Return the corresponding character from the depth characters
			return characters[index];
		}
	};
}

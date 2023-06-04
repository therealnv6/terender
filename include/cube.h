#pragma once
#include <line.h>
#include <math.h>
#include <surface.h>

namespace rend
{
	class cube
	{
	public:
		cube(rend::surface &surface, float vertices_size)
			: surface(surface)
			, vertices_size(vertices_size)
		{
		}

		void draw()
		{

			float vertices[8][3] = {
				{-vertices_size, -vertices_size, -vertices_size},
				{ vertices_size, -vertices_size, -vertices_size},
				{ vertices_size,	 vertices_size, -vertices_size},
				{-vertices_size,  vertices_size, -vertices_size},
				{-vertices_size, -vertices_size,  vertices_size},
				{ vertices_size, -vertices_size,	 vertices_size},
				{ vertices_size,	 vertices_size,	vertices_size},
				{-vertices_size,  vertices_size,	 vertices_size}
			};

			int edges[12][2] = {
				{0, 1},
				{1, 2},
				{2, 3},
				{3, 0},
				{4, 5},
				{5, 6},
				{6, 7},
				{7, 4},
				{0, 4},
				{1, 5},
				{2, 6},
				{3, 7}
			};

			float rotation_x = angle_x * M_PI / 180.0;
			float rotation_y = angle_y * M_PI / 180.0;

			for (int i = 0; i < 8; ++i)
			{
				float y = vertices[i][1];
				float z = vertices[i][2];

				vertices[i][1] = y * cos(rotation_x) - z * sin(rotation_x);
				vertices[i][2] = z * cos(rotation_x) + y * sin(rotation_x);
			}

			for (int i = 0; i < 8; ++i)
			{
				float x = vertices[i][0];
				float z = vertices[i][2];

				vertices[i][0] = x * cos(rotation_y) - z * sin(rotation_y);
				vertices[i][2] = z * cos(rotation_y) + x * sin(rotation_y);
			}

			int coordinates[8][2];
			auto [height, width] = surface.get_dimensions();

			for (int i = 0; i < 8; ++i)
			{
				float x = vertices[i][0];
				float y = vertices[i][1];
				float z = vertices[i][2];
				coordinates[i][0] = static_cast<int>(width / 2.0 + x * (width / 4.0));
				coordinates[i][1] = static_cast<int>(height / 2.0 - y * (height / 4.0));
			}

			for (int i = 0; i < 12; ++i)
			{
				int x1 = coordinates[edges[i][0]][0];
				int y1 = coordinates[edges[i][0]][1];
				int x2 = coordinates[edges[i][1]][0];
				int y2 = coordinates[edges[i][1]][1];

				int index_table = static_cast<int>((vertices[edges[i][0]][2] + 1) * 128);
				char symbol_table[] { '-', '=', '+', '*', '#' }; // FIXME better characters? idk

				int index = index_table % sizeof(symbol_table);
				char symbol = symbol_table[index];

				rend::line {
					surface,
					{static_cast<int>(x1), static_cast<int>(y1)},
					{static_cast<int>(x2), static_cast<int>(y2)},
					symbol
				};
			}
		}

		void rotate(float x, float y)
		{
			this->angle_x += x;
			this->angle_y += y;
		}

	private:
		float vertices_size;

		float angle_x;
		float angle_y;

		rend::surface &surface;
	};
}

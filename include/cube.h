#pragma once
#include <iostream>
#include <line.h>
#include <math.h>
#include <surface.h>

namespace rend
{

	template<uint32_t HEIGHT, uint32_t WIDTH>
	class cube
	{
	public:
		cube(rend::surface<HEIGHT, WIDTH> &surface, double size, std::array<double, 3> position)
			: surface(surface)
			, size(size)
			, position(position)
		{
			// Define the vertices of the cube
			vertices = {
				{{ -size / 2, -size / 2, -size / 2 },
					{ size / 2, -size / 2, -size / 2 },
					{ size / 2, size / 2, -size / 2 },
					{ -size / 2, size / 2, -size / 2 },
					{ -size / 2, -size / 2, size / 2 },
					{ size / 2, -size / 2, size / 2 },
					{ size / 2, size / 2, size / 2 },
					{ -size / 2, size / 2, size / 2 }}
			};
		}

		void draw()
		{
			// Draw the lines between the vertices to create the cube edges
			for (size_t i = 0; i < vertices.size(); ++i)
			{
				std::array<double, 3> translatedVertex1 = translate(vertices[i]);
				std::array<double, 3> translatedVertex2 = translate(vertices[(i + 1) % vertices.size()]);
				line3d<HEIGHT, WIDTH>(surface, translatedVertex1, translatedVertex2);
			}
		}

		void rotate(double angle_x, double angle_y, double angle_z)
		{
			rotation_angle_x += angle_x;
			rotation_angle_y += angle_y;
			rotation_angle_z += angle_z;
		}

	private:
		rend::surface<HEIGHT, WIDTH> &surface;
		double size;
		std::array<double, 3> position;
		std::array<std::array<double, 3>, 8> vertices;
		double rotation_angle_x = 0.0;
		double rotation_angle_y = 0.0;
		double rotation_angle_z = 0.0;

		void rotate(std::array<double, 3> &vertex, double angle_x, double angle_y, double angle_z)
		{
			// Rotate the vertex around the X-axis
			double cos_theta_x = cos(angle_x);
			double sin_theta_x = sin(angle_x);
			double temp_y = vertex[1];
			double temp_z = vertex[2];
			vertex[1] = temp_y * cos_theta_x - temp_z * sin_theta_x;
			vertex[2] = temp_y * sin_theta_x + temp_z * cos_theta_x;

			// Rotate the vertex around the Y-axis
			double cos_theta_y = cos(angle_y);
			double sin_theta_y = sin(angle_y);
			double temp_x = vertex[0];
			temp_z = vertex[2];
			vertex[0] = temp_x * cos_theta_y + temp_z * sin_theta_y;
			vertex[2] = -temp_x * sin_theta_y + temp_z * cos_theta_y;

			// Rotate the vertex around the Z-axis
			double cos_theta_z = cos(angle_z);
			double sin_theta_z = sin(angle_z);
			temp_x = vertex[0];
			temp_y = vertex[1];
			vertex[0] = temp_x * cos_theta_z - temp_y * sin_theta_z;
			vertex[1] = temp_x * sin_theta_z + temp_y * cos_theta_z;
		}

		std::array<double, 2> scale(const std::array<double, 3> &vertex)
		{
			// Scale the vertex based on its distance from the viewer
			double scale_factor = position[2] / (position[2] + vertex[2]);
			return { vertex[0] * scale_factor, vertex[1] * scale_factor };
		}

		std::array<double, 3> translate(const std::array<double, 3> &vertex)
		{
			// Translate the vertex based on its position in the surface and the cube's position
			return {
				vertex[0] + position[0],
				vertex[1] + position[1],
				vertex[2] + position[2]
			};
		}
	};
}

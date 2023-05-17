#pragma once
#include <array>
#include <line.h>
#include <math.h>
#include <surface.h>

namespace rend
{
	template<uint32_t HEIGHT, uint32_t WIDTH>
	class tri
	{
	public:
		tri(rend::surface<HEIGHT, WIDTH> &surface, std::array<double, 2> loc1, std::array<double, 2> loc2, std::array<double, 2> loc3)
			: x1(loc1[0])
			, y1(loc1[1])
			, x2(loc2[0])
			, y2(loc2[1])
			, x3(loc3[0])
			, y3(loc3[1])
			, surface(surface)
		{
		}

		void draw()
		{
			rend::line<HEIGHT, WIDTH> {
				surface,
				{static_cast<int>(x1), static_cast<int>(y1)},
				{static_cast<int>(x2), static_cast<int>(y2)}
			};

			rend::line<HEIGHT, WIDTH> {
				surface,
				{static_cast<int>(x2), static_cast<int>(y2)},
				{static_cast<int>(x3), static_cast<int>(y3)}
			};

			rend::line<HEIGHT, WIDTH> {
				surface,
				{static_cast<int>(x3), static_cast<int>(y3)},
				{static_cast<int>(x1), static_cast<int>(y1)}
			};

			for (int i = 0; i < HEIGHT; ++i)
			{
				for (int j = 0; j < WIDTH; ++j)
				{
					std::cout << surface.chars[i][j];
				}
				std::cout << std::endl;
			}
		}
		void rotate_max(double angle, double max)
		{
			if (rotation_angle < max)
			{
				rotation_angle += angle;
			}
			else
			{
				rotation_angle -= angle;
			}

			rotate(rotation_angle);
		}

		void rotate(double angle)
		{
			// Converting angle to radians
			angle = angle * M_PI / 180.0;

			// Calculate the center of the triangle
			double centerX = (x1 + x2 + x3) / 3.0;
			double centerY = (y1 + y2 + y3) / 3.0;

			// Move the triangle to the origin
			x1 -= centerX;
			y1 -= centerY;
			x2 -= centerX;
			y2 -= centerY;
			x3 -= centerX;
			y3 -= centerY;

			// Perform rotation
			double cosTheta = cos(angle);
			double sinTheta = sin(angle);
			double tempX1 = x1 * cosTheta - y1 * sinTheta;
			double tempY1 = x1 * sinTheta + y1 * cosTheta;
			double tempX2 = x2 * cosTheta - y2 * sinTheta;
			double tempY2 = x2 * sinTheta + y2 * cosTheta;
			double tempX3 = x3 * cosTheta - y3 * sinTheta;
			double tempY3 = x3 * sinTheta + y3 * cosTheta;

			// Move the triangle back to its original position
			x1 = tempX1 + centerX;
			y1 = tempY1 + centerY;
			x2 = tempX2 + centerX;
			y2 = tempY2 + centerY;
			x3 = tempX3 + centerX;
			y3 = tempY3 + centerY;
		}

	private:
		double x1;
		double y1;
		double x2;
		double y2;
		double x3;
		double y3;

		double rotation_angle = 0.0;

		rend::surface<HEIGHT, WIDTH> &surface;
	};
}

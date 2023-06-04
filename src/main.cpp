#include <chrono>
#include <cube.h>
#include <iostream>
#include <line.h>
#include <memory>
#include <spdlog/spdlog.h>
#include <surface.h>
#include <tri.h>

int main()
{
	constexpr uint32_t WIDTH = 100;
	constexpr uint32_t HEIGHT = 40;

	rend::surface surface(HEIGHT, WIDTH);
	rend::cube cube(surface, 1.2);

	// just ignore this lol
	rend::tri tri {
		surface,
		{25.0, 10.0},
		{35.0, 20.0},
		{35.0, 20.0}
	};

	auto last = std::chrono::high_resolution_clock::now();
	double delta_time = 0.0;
	while (true)
	{
		surface.clear();
		{
			cube.draw();
			cube.rotate(100.0 * delta_time, 100.0 * delta_time);
		}
		surface.render();

		auto now = std::chrono::high_resolution_clock::now();
		delta_time = std::chrono::duration<double>(now - last).count();
		last = now;

		{
			double fps = 1.0 / delta_time;
			std::cout << "fps: " << fps << std::endl;
		}

		std::this_thread::sleep_for(std::chrono::microseconds(250));
	}
}

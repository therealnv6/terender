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
	constexpr uint32_t WIDTH = 80;
	constexpr uint32_t HEIGHT = 60;

	rend::surface<HEIGHT, WIDTH> surface;
	rend::cube<HEIGHT, WIDTH> cube {
		surface,
		2.0,
		{40.0, 10.0, 0.0}	// Same position as the triangle
	};
	rend::tri<HEIGHT, WIDTH> tri {
		surface,
		{40.0, 10.0},
		{35.0, 20.0},
		{45.0, 20.0}
	};

	auto last = std::chrono::high_resolution_clock::now();
	auto frametime = 0;
	auto fps = 0;

	while (true)
	{
		// Clear the terminal window
		surface.clear();
		cube.rotate(0.01, 0.01, 0.01);
		cube.draw();
		// tri.draw();
		// tri.rotate_max(0.5, 1.0);
		surface.render();

		frametime++;

		auto now = std::chrono::high_resolution_clock::now();
		auto time_since_last = std::chrono::duration<float, std::chrono::seconds::period>(now - last).count();

		if (time_since_last >= 1.0)
		{
			fps = frametime;
			last = now;
			frametime = 0;
		}

		std::cout << "fps: " << fps << std::endl;

		// we have to sleep here.
		std::this_thread::sleep_for(std::chrono::milliseconds(12));
		// break;
	}
}

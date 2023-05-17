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
	rend::tri<HEIGHT, WIDTH> tri {
		surface,
		{40.0, 10.0},
		{35.0, 20.0},
		{45.0, 20.0}
	};

	while (true)
	{
		// Clear the terminal window
		surface.clear();
		tri.draw();
		tri.rotate_max(0.005, 1.0);
		surface.render();

		// Delay for a short period of time (e.g., 100 milliseconds)
		// You may need to include appropriate system-specific headers for the sleep function
		// Uncomment the line below and modify it accordingly based on your operating system.
		std::this_thread::sleep_for(std::chrono::milliseconds(16));
	}
}

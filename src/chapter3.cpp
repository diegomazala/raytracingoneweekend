#include <iostream>
#include <vector>
#include "image.h"
#include "ray.h"


vec3f color(const rayf& r)
{
	vec3f unit_direction = unit_vector(r.direction());
	float t = 0.5f * (unit_direction.y() + 1.0f);
	return (1.0f - t) * vec3f(1.0f, 1.0f, 1.0f) + t * vec3f(0.5f, 0.7f, 1.0f);
}


int main() 
{
	image<uint8_t> img{ 256, 128, 3 };

	vec3f lower_left_corner(-2.0f, -1.0f, -1.0f);
	vec3f horizontal(4.0f, 0.0f, 0.0f);
	vec3f vertical(0.0f, 2.0f, 0.0f);
	vec3f origin(0.0f, 0.0f, 0.0f);


	for (uint32_t i = 0; i < img.height; ++i)
	{
		for (uint32_t j = 0; j < img.width; j++)
		{
			float u = static_cast<float>(j) / static_cast<float>(img.width);
			float v = static_cast<float>(img.height - i) / static_cast<float>(img.height);

			rayf r(origin, lower_left_corner + u * horizontal + v * vertical);
			vec3f col = color(r);

			img.data.push_back(static_cast<uint8_t>(255.9f * col[0]));
			img.data.push_back(static_cast<uint8_t>(255.9f * col[1]));
			img.data.push_back(static_cast<uint8_t>(255.9f * col[2]));
		}
	}

	img.save("chapter3.jpg");

#ifdef _WIN32
	ShellExecute(0, 0, "chapter3.jpg", 0, 0, SW_SHOW);
#endif

}




#include <iostream>
#include <vector>
#include "image.h"
#include "sphere.h"
#include "hitable_list.h"



vec3f color(const rayf& r, hitable<float>* world)
{
	hit_record<float> rec;

	if (world->hit(r, 0.f, FLT_MAX, rec))
	{
		return 0.5f * vec3f( rec.normal.x() + 1, rec.normal.y() + 1, rec.normal.z() + 1);
	}
	else
	{
		//
		// Brackground color
		//
		vec3f unit_direction = unit_vector(r.direction());
		float t = 0.5f * (unit_direction.y() + 1.0f);
		return (1.0f - t) * vec3f(1.0f, 1.0f, 1.0f) + t * vec3f(0.5f, 0.7f, 1.0f);
	}
}



int main() 
{
	image<uint8_t> img{ 256, 128, 3 };

	vec3f lower_left_corner(-2.0f, -1.0f, -1.0f);
	vec3f horizontal(4.0f, 0.0f, 0.0f);
	vec3f vertical(0.0f, 2.0f, 0.0f);
	vec3f origin(0.0f, 0.0f, 0.0f);

	hitable<float> *list[2];
	list[0] = new sphere(vec3f(0.f, 0.f, -1.f), 0.5f);
	list[1] = new sphere(vec3f(0.f, -100.5f, -1.f), 100.f);

	hitable<float>* world = new hitable_list(list, 2);

	for (uint32_t i = 0; i < img.height; ++i)
	{
		for (uint32_t j = 0; j < img.width; j++)
		{
			float u = static_cast<float>(j) / static_cast<float>(img.width);
			float v = static_cast<float>(img.height - i) / static_cast<float>(img.height);

			rayf r(origin, lower_left_corner + u * horizontal + v * vertical);

			vec3f p = r.point_at_parameter(2.f);
			vec3f col = color(r, world);

			img.data.push_back(static_cast<uint8_t>(255.9f * col[0]));
			img.data.push_back(static_cast<uint8_t>(255.9f * col[1]));
			img.data.push_back(static_cast<uint8_t>(255.9f * col[2]));
		}
	}

	img.save("chapter5.jpg");

#ifdef _WIN32
	ShellExecute(0, 0, "chapter5.jpg", 0, 0, SW_SHOW);
#endif

}




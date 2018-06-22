#include <iostream>
#include <vector>
#include "image.h"
#include "ray.h"

bool hit_sphere(const vec3f& center, float radius, const rayf& r)
{
	vec3f oc = r.origin() - center;
	float a = dot(r.direction(), r.direction());
	float b = 2.0f * dot(oc, r.direction());
	float c = dot(oc, oc) - radius * radius;
	float discriminant = b * b - 4 * a * c;
	return (discriminant > 0);
}


vec3f color(const rayf& r)
{
	if (hit_sphere(vec3f(0, 0, -1), 0.5f, r))
		return vec3f(1, 0, 0);

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

	img.save("chapter4.jpg");

#ifdef _WIN32
	ShellExecute(0, 0, "chapter4.jpg", 0, 0, SW_SHOW);
#endif

}




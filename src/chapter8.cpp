#include <iostream>
#include <vector>
#include "image.h"
#include "sphere.h"
#include "hitable_list.h"
#include "camera.h"
#include "material.h"

vec3f random_in_unit_sphere()
{
	vec3f p;
	do
	{
		p = 2.0f * vec3f(random_gen_unit.rand(), random_gen_unit.rand(), random_gen_unit.rand()) - vec3f::ones();
	} while (p.squared_length() >= 1.0f);
	return p;
}


vec3f color(const rayf& r, hitable<float>* world, int depth)
{
	hit_record<float> rec;

	if (world->hit(r, 0.001f, FLT_MAX, rec))
	{
		rayf scattered;
		vec3f attenuation;

		if (depth < 50 &&
			rec.mat_ptr->scatter(r, rec, attenuation, scattered))
		{
			return attenuation * color(scattered, world, depth + 1);
		}
		else
		{
			return vec3f::zeros();
		}
	}
	else
	{
		//
		// Brackground color
		//
		vec3f unit_direction = unit_vector(r.direction());
		float t = 0.5f * (unit_direction.y() + 1.0f);
		return (1.0f - t) * vec3f::ones() + t * vec3f(0.5f, 0.7f, 1.0f);
	}
}


int main()
{
	uint32_t ns = 128;	// rays per pixel
	image<uint8_t> img{ 256, 128, 3 };

	hitable<float> *list[4];
	list[0] = new sphere(vec3f(0.f, -100.5f, -1.f), 100.f, new lambertian<float>(vec3f(0.8f, 0.8f, 0.0f)));
	list[1] = new sphere(vec3f(0.f, 0.f, -1.f), 0.5f, new lambertian<float>(vec3f(0.8f, 0.3f, 0.3f)));
	list[2] = new sphere(vec3f(1.f, 0.f, -1.f), 0.5f, new metal<float>(vec3f(0.8f, 0.6f, 0.2f), 1.0f));
	list[3] = new sphere(vec3f(-1.f, 0.f, -1.f), 0.5f, new metal<float>(vec3f(0.8f, 0.8f, 0.8f), 0.3f));

	hitable<float>* world = new hitable_list(list, 4);

	camera<float> cam;
	cam.lower_left_corner = vec3f(-2.0f, -1.0f, -1.0f);
	cam.horizontal = vec3f(4.0f, 0.0f, 0.0f);
	cam.vertical = vec3f(0.0f, 2.0f, 0.0f);
	cam.origin = vec3f(0.0f, 0.0f, 0.0f);


	for (uint32_t i = 0; i < img.height; ++i)
	{
		for (uint32_t j = 0; j < img.width; j++)
		{
			vec3f col(0, 0, 0);
			for (uint32_t s = 0; s < ns; ++s)
			{
				float u = static_cast<float>(j + random_gen_unit.rand()) / static_cast<float>(img.width);
				float v = static_cast<float>(img.height - i - 1 + random_gen_unit.rand()) / static_cast<float>(img.height);
				rayf r = cam.get_ray(u, v);
				vec3f p = r.point_at_parameter(2.f);
				col += color(r, world, 0);
			}
			col /= static_cast<float>(ns);
			col = vec3f(std::sqrtf(col[0]), std::sqrtf(col[1]), std::sqrtf(col[2]));	// gamma correction
			img.data.push_back(static_cast<uint8_t>(255.9f * col[0]));
			img.data.push_back(static_cast<uint8_t>(255.9f * col[1]));
			img.data.push_back(static_cast<uint8_t>(255.9f * col[2]));
		}
	}

	img.save("chapter8.jpg");

#ifdef _WIN32
	ShellExecute(0, 0, "chapter8.jpg", 0, 0, SW_SHOW);
#endif

}




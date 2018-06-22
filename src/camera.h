#ifndef CAMERAH
#define CAMERAH
#include "ray.h"
#include "random_generator.h"

template <typename T>
static vec3<T> random_in_unit_disk() 
{
    vec3<T> p;
    do 
	{
        p = 2.f * vec3<T>(random_gen_unit.rand(), random_gen_unit.rand(), 0) - vec3<T>(1,1,0);
    } while (dot(p,p) >= 1.0);
    return p;
}


template <typename T>
class camera
{
public:
	camera(){}

	camera(vec3<T> lookfrom, vec3<T> lookat, vec3<T> vup, T vfov, T aspect, T aperture, T focus_dist)
	{
		// vfov is top to bottom in degrees
		lens_radius = aperture / 2;
		T theta = vfov * M_PI / 180.0;
		T half_height = tan(theta / 2);
		T half_width = aspect * half_height;
		origin = lookfrom;
		w = unit_vector(lookfrom - lookat);
		u = unit_vector(cross(vup, w));
		v = cross(w, u);
		lower_left_corner = origin - half_width * focus_dist*u - half_height * focus_dist*v - focus_dist * w;
		horizontal = 2 * half_width*focus_dist*u;
		vertical = 2 * half_height*focus_dist*v;
	}

#if false
	ray<T> get_ray(T s, T t)
	{
		vec3<T> rd = lens_radius * random_in_unit_disk<T>();
		vec3<T> offset = u * rd.x() + v * rd.y();
		return ray<T>(origin + offset, lower_left_corner + s * horizontal + t * vertical - origin - offset);
	}
#else
	ray<T> get_ray(T u, T v)
	{
		return ray<T>(origin, lower_left_corner + u * horizontal + v * vertical - origin);
	}
#endif

	vec3<T> origin;
	vec3<T> lower_left_corner;
	vec3<T> horizontal;
	vec3<T> vertical;
	vec3<T> u, v, w;
    T lens_radius;

	const T M_PI = static_cast<T>(3.14159265358979323846);
};
#endif





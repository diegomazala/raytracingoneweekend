#ifndef MATERIALH
#define MATERIALH 

template<typename T> struct hit_record;

#include "ray.h"
#include "hitable.h"
#include "random_generator.h"


template <typename T>
T schlick(T cosine, T ref_idx) {
    T r0 = (1-ref_idx) / (1+ref_idx);
    r0 = r0*r0;
    return r0 + (1-r0)*pow((1 - cosine),5);
}


template <typename T>
bool refract(const vec3<T>& v, const vec3<T>& n, T ni_over_nt, vec3<T>& refracted) 
{
    vec3<T> uv = unit_vector(v);
    T dt = dot(uv, n);
    T discriminant = 1.0 - ni_over_nt*ni_over_nt*(1-dt*dt);
    if (discriminant > 0) 
	{
        refracted = ni_over_nt*(uv - n*dt) - n*sqrt(discriminant);
        return true;
    }
    else 
        return false;
}


template <typename T>
vec3<T> reflect(const vec3<T>& v, const vec3<T>& n)
{
     return v - 2 * dot(v, n) * n;
}


template <typename T>
vec3<T> random_in_unit_sphere() 
{
    vec3<T> p;
    do 
	{
        p = 2.0 * vec3<T>(random_gen_unit.rand(), random_gen_unit.rand(), random_gen_unit.rand()) - vec3<T>(1,1,1);
    } while (p.squared_length() >= 1.0);
    return p;
}


template <typename T>
class material  
{
    public:
        virtual bool scatter(const ray<T>& r_in, const hit_record<T>& rec, vec3<T>& attenuation, ray<T>& scattered) const = 0;
};


template <typename T>
class lambertian : public material<T> 
{
    public:
        lambertian(const vec3<T>& a) : albedo(a) {}

        virtual bool scatter(const ray<T>& r_in, const hit_record<T>& rec, vec3<T>& attenuation, ray<T>& scattered) const  
		{
             vec3<T> target = rec.p + rec.normal + random_in_unit_sphere();
             scattered = ray<T>(rec.p, target-rec.p);
             attenuation = albedo;
             return true;
        }

        vec3<T> albedo;
};


template <typename T>
class metal : public material<T> 
{
    public:
        metal(const vec3<T>& a, T f = 1) : albedo(a) { if (f < 1) fuzz = f; else fuzz = 1; }

        virtual bool scatter(const ray<T>& r_in, const hit_record<T>& rec, vec3<T>& attenuation, ray<T>& scattered) const  
		{
            vec3<T> reflected = reflect(unit_vector(r_in.direction()), rec.normal);
            scattered = ray<T>(rec.p, reflected + fuzz*random_in_unit_sphere());
            attenuation = albedo;
            return (dot(scattered.direction(), rec.normal) > 0);
        }
        vec3<T> albedo;
        T fuzz;
};


template <typename T>
class dielectric : public material<T> 
{ 
    public:
        dielectric(T ri) : ref_idx(ri) {}

		virtual bool scatter(const ray<T>& r_in, const hit_record<T>& rec, vec3<T>& attenuation, ray<T>& scattered) const  
		{
             vec3<T> outward_normal;
             vec3<T> reflected = reflect(r_in.direction(), rec.normal);
             T ni_over_nt;
             attenuation = vec3<T>(1.0, 1.0, 1.0);
             vec3<T> refracted;
             T reflect_prob;
             T cosine;
             if (dot(r_in.direction(), rec.normal) > 0) 
			 {
                  outward_normal = -rec.normal;
                  ni_over_nt = ref_idx;
                  cosine = ref_idx * dot(r_in.direction(), rec.normal) / r_in.direction().length();
                  //cosine = dot(r_in.direction(), rec.normal) / r_in.direction().length();
                  //cosine = sqrt(1 - ref_idx*ref_idx*(1-cosine*cosine));
             }
             else 
			 {
                  outward_normal = rec.normal;
                  ni_over_nt = 1.0 / ref_idx;
                  cosine = -dot(r_in.direction(), rec.normal) / r_in.direction().length();
             }

             if (refract(r_in.direction(), outward_normal, ni_over_nt, refracted)) 
                reflect_prob = schlick(cosine, ref_idx);
             else 
                reflect_prob = 1.0;


             if (random_gen_unit.rand() < reflect_prob)
                scattered = ray<T>(rec.p, reflected);
             else 
                scattered = ray<T>(rec.p, refracted);
             return true;
        }

        T ref_idx;
};

#endif





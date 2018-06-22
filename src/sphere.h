#ifndef SPHEREH
#define SPHEREH

#include "hitable.h"

template <typename T>
class sphere: public hitable<T>  {
    public:
        sphere() {}
        sphere(vec3<T> cen, T r, material<T> *m = nullptr) : center(cen), radius(r), mat_ptr(m)  {};
        virtual bool hit(const ray<T>& r, T tmin, T tmax, hit_record<T>& rec) const;
        vec3<T> center;
        T radius;
        material<T> *mat_ptr;
};

template <typename T>
bool sphere<T>::hit(const ray<T>& r, T t_min, T t_max, hit_record<T>& rec) const 
{
    vec3<T> oc = r.origin() - center;
    T a = dot(r.direction(), r.direction());
    T b = dot(oc, r.direction());
    T c = dot(oc, oc) - radius*radius;
    T discriminant = b*b - a*c;
    if (discriminant > 0) 
	{
        T temp = (-b - sqrt(discriminant))/a;
        if (temp < t_max && temp > t_min) 
		{
            rec.t = temp;
            rec.p = r.point_at_parameter(rec.t);
            rec.normal = (rec.p - center) / radius;
            rec.mat_ptr = mat_ptr;
            return true;
        }
        temp = (-b + sqrt(discriminant)) / a;
        if (temp < t_max && temp > t_min) 
		{
            rec.t = temp;
            rec.p = r.point_at_parameter(rec.t);
            rec.normal = (rec.p - center) / radius;
            rec.mat_ptr = mat_ptr;
            return true;
        }
    }
    return false;
}


#endif




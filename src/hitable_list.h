#ifndef HITABLELISTH
#define HITABLELISTH

#include "hitable.h"


template <typename T>
class hitable_list: public hitable<T>  
{
    public:
        hitable_list() {}
        hitable_list(hitable<T> **l, int n) {list = l; list_size = n; }
        virtual bool hit(const ray<T>& r, T tmin, T tmax, hit_record<T>& rec) const;
        hitable<T> **list;
        int list_size;
};


template <typename T>
bool hitable_list<T>::hit(const ray<T>& r, T t_min, T t_max, hit_record<T>& rec) const 
{
    hit_record<T> temp_rec;
    bool hit_anything = false;
    T closest_so_far = t_max;
    for (int i = 0; i < list_size; i++) 
	{
        if (list[i]->hit(r, t_min, closest_so_far, temp_rec)) 
		{
            hit_anything = true;
            closest_so_far = temp_rec.t;
            rec = temp_rec;
        }
    }
    return hit_anything;
}

#endif


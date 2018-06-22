#ifndef VEC3H
#define VEC3H

#include <math.h>
#include <stdlib.h>
#include <iostream>



template <typename T>
class vec3  {

    
public:
    vec3() {}
    vec3(T e0, T e1, T e2) { e[0] = e0; e[1] = e1; e[2] = e2; }
    inline T x() const { return e[0]; }
    inline T y() const { return e[1]; }
    inline T z() const { return e[2]; }
    inline T r() const { return e[0]; }
    inline T g() const { return e[1]; }
    inline T b() const { return e[2]; }

    
    inline const vec3& operator+() const { return *this; }
    inline vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }
    inline T operator[](int i) const { return e[i]; }
    inline T& operator[](int i) { return e[i]; };
    
    inline vec3& operator+=(const vec3 &v2);
    inline vec3& operator-=(const vec3 &v2);
    inline vec3& operator*=(const vec3 &v2);
    inline vec3& operator/=(const vec3 &v2);
    inline vec3& operator*=(const T t);
    inline vec3& operator/=(const T t);
    
    inline T length() const { return sqrt(e[0]*e[0] + e[1]*e[1] + e[2]*e[2]); }
    inline T squared_length() const { return e[0]*e[0] + e[1]*e[1] + e[2]*e[2]; }
    inline void make_unit_vector();
    
	static inline vec3 zeros() { return vec3(0, 0, 0); }
	static inline vec3 ones() { return vec3(1, 1, 1); }

	inline T& data() { return e; }
    
    T e[3];
};

template <typename T>
inline std::istream& operator>>(std::istream &is, vec3<T> &t) {
    is >> t.e[0] >> t.e[1] >> t.e[2];
    return is;
}

template <typename T>
inline std::ostream& operator<<(std::ostream &os, const vec3<T> &t) {
    os << t.e[0] << " " << t.e[1] << " " << t.e[2];
    return os;
}

template <typename T>
inline void vec3<T>::make_unit_vector() {
    T k = 1.0 / sqrt(e[0]*e[0] + e[1]*e[1] + e[2]*e[2]);
    e[0] *= k; e[1] *= k; e[2] *= k;
}

template <typename T>
inline vec3<T> operator+(const vec3<T> &v1, const vec3<T> &v2) {
    return vec3<T>(v1.e[0] + v2.e[0], v1.e[1] + v2.e[1], v1.e[2] + v2.e[2]);
}

template <typename T>
inline vec3<T> operator-(const vec3<T> &v1, const vec3<T> &v2) {
    return vec3<T>(v1.e[0] - v2.e[0], v1.e[1] - v2.e[1], v1.e[2] - v2.e[2]);
}

template <typename T>
inline vec3<T> operator*(const vec3<T> &v1, const vec3<T> &v2) {
    return vec3(v1.e[0] * v2.e[0], v1.e[1] * v2.e[1], v1.e[2] * v2.e[2]);
}

template <typename T>
inline vec3<T> operator/(const vec3<T> &v1, const vec3<T> &v2) {
    return vec3<T>(v1.e[0] / v2.e[0], v1.e[1] / v2.e[1], v1.e[2] / v2.e[2]);
}

template <typename T>
inline vec3<T> operator*(T t, const vec3<T> &v) {
    return vec3<T>(t*v.e[0], t*v.e[1], t*v.e[2]);
}

template <typename T>
inline vec3<T> operator/(vec3<T> v, T t) {
    return vec3<T>(v.e[0]/t, v.e[1]/t, v.e[2]/t);
}

template <typename T>
inline vec3<T> operator*(const vec3<T> &v, T t) {
    return vec3<T>(t*v.e[0], t*v.e[1], t*v.e[2]);
}

template <typename T>
inline T dot(const vec3<T> &v1, const vec3<T> &v2) {
    return v1.e[0] *v2.e[0] + v1.e[1] *v2.e[1]  + v1.e[2] *v2.e[2];
}

template <typename T>
inline vec3<T> cross(const vec3<T> &v1, const vec3<T> &v2) {
    return vec3<T>( (v1.e[1]*v2.e[2] - v1.e[2]*v2.e[1]),
                (-(v1.e[0]*v2.e[2] - v1.e[2]*v2.e[0])),
                (v1.e[0]*v2.e[1] - v1.e[1]*v2.e[0]));
}

template <typename T>
inline vec3<T>& vec3<T>::operator+=(const vec3<T> &v){
    e[0]  += v.e[0];
    e[1]  += v.e[1];
    e[2]  += v.e[2];
    return *this;
}

template <typename T>
inline vec3<T>& vec3<T>::operator*=(const vec3<T> &v){
    e[0]  *= v.e[0];
    e[1]  *= v.e[1];
    e[2]  *= v.e[2];
    return *this;
}

template <typename T>
inline vec3<T>& vec3<T>::operator/=(const vec3<T> &v){
    e[0]  /= v.e[0];
    e[1]  /= v.e[1];
    e[2]  /= v.e[2];
    return *this;
}

template <typename T>
inline vec3<T>& vec3<T>::operator-=(const vec3<T>& v) {
    e[0]  -= v.e[0];
    e[1]  -= v.e[1];
    e[2]  -= v.e[2];
    return *this;
}

template <typename T>
inline vec3<T>& vec3<T>::operator*=(const T t) {
    e[0]  *= t;
    e[1]  *= t;
    e[2]  *= t;
    return *this;
}

template <typename T>
inline vec3<T>& vec3<T>::operator/=(const T t) {
    T k = static_cast<T>(1.0/t);
    
    e[0]  *= k;
    e[1]  *= k;
    e[2]  *= k;
    return *this;
}

template <typename T>
inline vec3<T> unit_vector(vec3<T> v) {
    return v / v.length();
}


//
// Define most common types
//
typedef vec3<uint8_t>	vec3uc;
typedef vec3<int32_t>	vec3i;
typedef vec3<float>		vec3f;
typedef vec3<double>	vec3d;

#endif

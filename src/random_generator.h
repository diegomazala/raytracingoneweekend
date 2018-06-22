#ifndef __RANDOM_GENERATOR_H__
#define __RANDOM_GENERATOR_H__
#include <random>
#include <thread>

template <typename T>
class random_generator {
public:
	std::random_device                 rd;
	std::mt19937                       mt;
	std::uniform_real_distribution<T>  dist;

	random_generator(T min = 0, T max = 1) : rd{}, mt{ rd() }, dist{ min, max } {}

	T rand() 
	{
		return dist(mt);
	}
};

thread_local random_generator<float> random_gen_unit(0, 1);

#if 0
int main(int argc, char** argv) {
	double x1 = backoff_time.rand();
	double x2 = backoff_time.rand();
	double x3 = backoff_time.rand();
	double x4 = backoff_time.rand();
	return 0;
}
#endif

#endif	// __RANDOM_GENERATOR_H__

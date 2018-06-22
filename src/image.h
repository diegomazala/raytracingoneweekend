#ifndef __IMAGE_H__
#define __IMAGE_H__

#define TJE_IMPLEMENTATION
#include "tiny_jpeg.h"


template <typename T>
class image
{
public:
	uint32_t width;
	uint32_t height;
	uint8_t channels;
	std::vector<T> data;


	bool save(const std::string& filename)
	{
		return tje_encode_to_file(filename.c_str(), width, height, channels, data.data());
	}
};



#endif // __IMAGE_H__

#include <iostream>
#include <vector>
#include "image.h"
#include "vec3.h"

int main() 
{
	image<uint8_t> img{ 256, 128, 3 };


	for (uint32_t i = 0; i < img.height; ++i)
	{
		for (uint32_t j = 0; j < img.width; j++)
		{
			vec3f color(
				static_cast<float>(j) / static_cast<float>(img.width),
				static_cast<float>(img.height - i) / static_cast<float>(img.height),
				0.02f);

			img.data.push_back(static_cast<uint8_t>(255.9f * color[0]));
			img.data.push_back(static_cast<uint8_t>(255.9f * color[1]));
			img.data.push_back(static_cast<uint8_t>(255.9f * color[2]));
		}
	}

	img.save("chapter2.jpg");


#ifdef _WIN32
	ShellExecute(0, 0, "chapter2.jpg", 0, 0, SW_SHOW);
#endif
}




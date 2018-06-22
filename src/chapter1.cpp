#include <iostream>
#include <vector>
#include "image.h"


int main() 
{
	image<uint8_t> img{ 256, 128, 3 };


	for (uint32_t i = 0; i < img.height; ++i)
	{
		for (uint32_t j = 0; j < img.width; j++)
		{
			float r = static_cast<float>(j) / static_cast<float>(img.width);
			float g = static_cast<float>(img.height - i) / static_cast<float>(img.height);
			float b = 0.02f;

			img.data.push_back(static_cast<uint8_t>(255.9f * r));
			img.data.push_back(static_cast<uint8_t>(255.9f * g));
			img.data.push_back(static_cast<uint8_t>(255.9f * b));
		}
	}

	img.save("chapter1.jpg");


#ifdef _WIN32
	ShellExecute(0, 0, "chapter1.jpg", 0, 0, SW_SHOW);
#endif
}




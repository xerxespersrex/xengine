#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <time.h>

bool drawFrame(uint32_t frame[1600][900])
{
	return true;
}

int main()
{
	clock_t start, lastframe, current;
	uint32_t frame[1600][900] = {0};
	double desired_framerate = (double) 1 / 60;
	double actual_framerate;
	int i = 0;
	start = clock();
	lastframe = start;
	
	while (i < 60)
	{
		current = clock();
		if (((double) current - lastframe) / CLOCKS_PER_SEC >= desired_framerate)
		{
			if (drawFrame(frame))
			{
				++i;
				printf("Frame %d drawn\n", i);
				lastframe = current;
			}
		}
	}
	actual_framerate = (60 / (((double) lastframe - start) / CLOCKS_PER_SEC));
	printf("Frames per second: %f\n", actual_framerate);
	return 0;
}

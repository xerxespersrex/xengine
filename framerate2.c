#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <time.h>

//render the state to a frame in the frame buffer
void renderFrame(uint32_t frame_buffer[640][480])
{
	return;
}

//apply hud or menus on top of frame
void applyHAM(uint32_t frame_buffer[640][480])
{
	return;
}

//draw the frame buffer to the screen
void draw(uint32_t frame_buffer[640][480])
{
	printf("Dummy draw! ");
	return;
}

/*

//get what buttons are being pressed
int currentInput()
{
	return 0;
}

*/

//draw graphics based on state
void engineGraphics(/*state*/)
{
	uint32_t frame_buffer[640][480] = {0};
	
	//state obviously not done, but...
	
	//create frame from state
	renderFrame(frame_buffer);
	
	//apply hud and menus to the frame
	applyHAM(frame_buffer);
	
	//draw the frame to the screen
	draw(frame_buffer);
	
	return;
}

//lurch forward state to next tick
void engineTick(/*state*/)
{
	//get input first, to be as close to draw as possible
	//int tick_input = currentInput();
	
	//crunch change in entire state from last tick based on physics and
	//input
	
	//take into account input now, or use input from last tick for this
	//tick? former separates input from state and is 1/60th of a second
	//faster so why not try that first
	
	return;
}

//wait for next tick
clock_t engineWait(clock_t last_tick_time_wait, double desired_tick_rate_wait)
{
	clock_t current_time;
	
	do {
	current_time = clock();
	} while ((((double) current_time - last_tick_time_wait) / CLOCKS_PER_SEC) <= desired_tick_rate_wait);
	
	return current_time;
}

void engineLoop(int target_ticks)
{
	//uint8_t state[500000000] = {0}; //500 megabytes memory reserved
	clock_t last_tick_time;
	double desired_tick_rate = ((double) 1 / 60);
	int tick_counter = 0;
	
	last_tick_time = clock();
	
	//draw->tick->wait->draw
	for (;;)
	{
		engineGraphics(/*state*/);
		
		engineTick(/*state*/);
		
		++tick_counter;
		
		printf("Tick %d", tick_counter);
		if (tick_counter % 60 == 0)
		{
			printf("------------");
		}
		printf("\n");
		
		if (tick_counter == target_ticks)
		{
			return;
		}
		
		last_tick_time = engineWait(last_tick_time, desired_tick_rate);
	}
	
	return;
}

int main()
{
	engineLoop(600);
	return 0;
}



/* sequencer of some sort?
 * poll input 1/60th?
 * tick 1/60th?
 * framerate 1/60th
 * 
 * a system underneath which is solid state and runs on its own and then
 * reacts to user input as the only change in state
 * 
 * every 1/60th of a second output the frame buffer
 * every 1/60th of a second poll the input devices and hold them for
 * the 1/60th of a second before releasing
 * do ticks matter? what do they even do?
 * 
 * need ticks to keep from performance changing gameplay -> faster pc,
 * more precise engine
 * with a tick every 1/60th of a second, the engine can simply jump from
 * tick to tick and "lurch" ahead in little bits because it's not
 * visible to the player
 * 
 * also seems like it makes things like replays more reliable since you
 * can record state at each tick and that's the replay
 * 
 * display frame first, then tick immediately
 * 
 * if tick isnt done by 1/60th of a second, skip drawing unless reaching
 * a max amount of ticks without draws e.g. 60, then force draw a frame
 * so the game doesn't completely lock up and there's at least enough
 * frames to quit out
 * 
 * how do you check for the timing for the beginning of the next tick
 * from within anywhere in the game? i guess you can completely finish a
 * tick, then check timing, so it's not so bad
 * 
 * what about dead time between tick and draw?
 * draw -> tick -> wait -> draw
 * just solve it with an empty for loop
 * 
 * then pass around state[big constant] array as dynamic storage for
 * state and maybe even throw the frame buffer in there because why not,
 * just use it as general memory for all the engine's needs
 * 
 * regardless of framerate, tick calculations can always use 1/60th of a
 * second for physics and other state changes and maybe there can be
 * some sort of rubberbanding in case the tickrate is too fast/slow
 * 
 * three dimensional map data loaded from a map file into storage, might
 * be easier to just load it into a separate 3d array (variable size?)
 * 
 * then either a profile for the player's collision/physics or hardcoded
 * numbers for interaction with map as player
 * 
 * should use desired-tickrate and desired-framerate constants
 * throughout the engine so that the engine isn't locked to a certain
 * fps or tickrate
 */

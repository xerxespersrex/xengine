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
	printf("Dummy draw!\n");
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
void engineGraphics(double frame_rate)
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
void engineTick(double tick_rate)
{
	//get input first and use it immediately to remove a frame of input
	//lag
	//int tick_input = currentInput();
	
	//crunch change in entire state from last tick based on physics and
	//input
	
	return;
}

void engineLoop(int target_ticks)
{
	//uint8_t state[500000000] = {0}; //500 megabytes memory reserved
	clock_t last_tick_time;
	clock_t last_frame_time;
	clock_t current_time;
	
	double desired_tick_rate = ((double) 1 / 60);
	double desired_frame_rate = ((double) 1 / 60);
	
	int tick_counter = 0;
	int frame_counter = 0;
	
	bool skip_frame = false;
	int frame_skip_counter = 0;
	int max_skipped_frames = 60;
	
	last_tick_time = clock();
	last_frame_time = clock();
	
	//draw->tick->wait->draw
	for (;;)
	{
		if ((((current_time = clock()) - (double) last_tick_time) / CLOCKS_PER_SEC) >= desired_tick_rate)
		{
			if ((((double) current_time - last_tick_time) / CLOCKS_PER_SEC) >= (2 * desired_tick_rate))
			{
				skip_frame = true;
			}
			last_tick_time = clock();
			engineTick(desired_tick_rate);
			++tick_counter;
			printf("Tick: %d\n", tick_counter);
		}
		
		if (skip_frame == true && frame_skip_counter < max_skipped_frames)
		{
			++frame_skip_counter;
			skip_frame = false;
		}
		
		else if ((((current_time = clock()) - (double) last_frame_time) / CLOCKS_PER_SEC) >= desired_frame_rate)
		{
			last_frame_time = clock();
			engineGraphics(desired_frame_rate);
			++frame_counter;
			printf("Frame: %d", frame_counter);
			if (frame_counter % 60 == 0)
			{
				printf("-----------\n");
			}
			else
			{
				printf("\n");
			}
		}
		
		if (tick_counter >= target_ticks)
		{
			return;
		}
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
 * 
 * 2d tile-based game (gameboy rpg style): tile art stored in sprite
 * sheets, list of all possible tiles giving tile art and tile physics
 * (solid or not) or flags (doors), then map data is effectively a 2d
 * array of data listing what tile at what location
 * 
 * do you do area flags (e.g. pokemon grass) with different tiles or
 * with separate area flag data in a second 2d array? what if one tile
 * has more than one flag? in games like pokemon i dont think that ever
 * happens, so it's not used.
 * 
 * need to keep framerate and tickrate separate
 * 
 * if desired tickrate isn't being met, skip drawing frames -> dynamic
 * frame rate
 */

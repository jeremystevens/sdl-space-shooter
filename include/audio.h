
#ifndef AUDIO_H
#define AUDIO_H

#include <SDL.h>

// Stores the current state of our procedurally generated laser sound.
typedef struct
{
    double phase;
    double frequency;
    int samples_remaining;
} LaserSound;


// Initialize the game's audio system.
// Returns 1 on success and 0 on failure.
int audio_init(LaserSound *laser);


// Start/restart the laser sound effect.
void audio_play_laser(LaserSound *laser);


// Shut down the audio system and close the audio device.
void audio_shutdown(void);


#endif

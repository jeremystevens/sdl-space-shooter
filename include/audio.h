
#ifndef AUDIO_H
#define AUDIO_H

#include <SDL.h>

// Stores the current state of our procedurally generated laser sound.
typedef struct
{
    // Player laser.
    double phase;
    double frequency;
    int samples_remaining;

    // Enemy laser.
    double enemy_phase;
    double enemy_frequency;
    int enemy_samples_remaining;

} LaserSound;

// Initialize the game's audio system.
// Returns 1 on success and 0 on failure.
int audio_init(LaserSound *laser);


// Start/restart the laser sound effect.
void audio_play_laser(LaserSound *laser);

// Play the Scout enemy weapon sound.
void audio_play_enemy_laser(LaserSound *laser);


// Shut down the audio system and close the audio device.
void audio_shutdown(void);


#endif

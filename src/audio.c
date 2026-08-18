#include "audio.h"

#include <math.h>
#include <stdio.h>

// define player lazer sound
#define SAMPLE_RATE 44100
#define LASER_FREQUENCY 900.0
#define LASER_DURATION 4000

// define enemy lazer sound for scout
#define ENEMY_LASER_FREQUENCY 450.0
#define ENEMY_LASER_DURATION 2500

// SDL identifier for the audio device we open.
static SDL_AudioDeviceID audio_device = 0;


// SDL calls this function whenever it needs more audio samples.
static void audio_callback(void *userdata, Uint8 *stream, int len)
{
    float *buffer = (float *)stream;

    int sample_count = len / sizeof(float);

    LaserSound *sound = (LaserSound *)userdata;


    for (int i = 0; i < sample_count; i++)
    {
        float sample = 0.0f;
        if (sound->samples_remaining > 0)
        {
            // Generate a square wave for a crunchy retro sound.
            sample +=
            (sin(sound->phase) > 0.0) ? 0.2f : -0.2f;

            // Gradually lower the frequency to create
            // the descending "pew" sound.
            sound->frequency -= 2.0;

            if (sound->frequency < 100.0)
            {
                sound->frequency = 100.0;
            }


            // Advance the waveform phase using the
            // current frequency and sample rate.
            sound->phase +=
                (2.0 * M_PI * sound->frequency) / SAMPLE_RATE;


            sound->samples_remaining--;
        }
        // Generate the enemy laser sound.
        if (sound->enemy_samples_remaining > 0)
        {
            // Lower, harsher square wave for Scout weapons.
            sample +=
            (sin(sound->enemy_phase) > 0.0) ? 0.15f : -0.15f;

            // Slide the enemy frequency downward.
            sound->enemy_frequency -= 1.0;

            if (sound->enemy_frequency < 80.0)
            {
                sound->enemy_frequency = 80.0;
            }

            // Advance the enemy waveform phase.
            sound->enemy_phase +=
                (2.0 * M_PI * sound->enemy_frequency) / SAMPLE_RATE;

            sound->enemy_samples_remaining--;
        }
    // end of changes MCH
      buffer[i] = sample;
    }
}


// Initialize SDL's audio device and prepare our laser sound.
int audio_init(LaserSound *laser)
{
    SDL_AudioSpec desired;
    SDL_AudioSpec obtained;


    // Initialize every field in the structure to zero.
    SDL_zero(desired);


    desired.freq = SAMPLE_RATE;
    desired.format = AUDIO_F32SYS;
    desired.channels = 1;
    desired.samples = 512;

    desired.callback = audio_callback;
    desired.userdata = laser;


    // Initialize the laser sound state.
    laser->phase = 0.0;
    laser->frequency = LASER_FREQUENCY;
    laser->samples_remaining = 0;

    // Initialize the enemy laser sound state.
    laser->enemy_phase = 0.0;
   // laser->enemy_frequency = 0.0;
    laser->enemy_frequency = ENEMY_LASER_FREQUENCY;
    laser->enemy_samples_remaining = 0;

    // Open the default playback device.
    audio_device = SDL_OpenAudioDevice(
        NULL,
        0,
        &desired,
        &obtained,
        0
    );


    if (audio_device == 0)
    {
        printf(
            "Failed to open audio device: %s\n",
            SDL_GetError()
        );

        return 0;
    }


    // SDL audio devices begin paused.
    // Passing 0 starts audio playback.
    SDL_PauseAudioDevice(audio_device, 0);


    return 1;
}


// Trigger the laser sound.
void audio_play_laser(LaserSound *laser)
{
    if (audio_device == 0)
    {
        return;
    }


    /*
     * SDL's audio callback can access LaserSound at the same
     * time as the main game loop.
     *
     * Lock the device while changing this shared data so the
     * callback cannot read it halfway through an update.
     */
    SDL_LockAudioDevice(audio_device);


    laser->phase = 0.0;
    laser->frequency = LASER_FREQUENCY;
    laser->samples_remaining = LASER_DURATION;


    SDL_UnlockAudioDevice(audio_device);
}

// Trigger the Scout enemy laser sound.
void audio_play_enemy_laser(LaserSound *laser)
{
    if (audio_device == 0)
    {
        return;
    }

    // Protect shared audio state from the SDL audio callback.
    SDL_LockAudioDevice(audio_device);

    laser->enemy_phase = 0.0;
    laser->enemy_frequency = ENEMY_LASER_FREQUENCY;
    laser->enemy_samples_remaining = ENEMY_LASER_DURATION;

    SDL_UnlockAudioDevice(audio_device);
}

// Close the audio device during game shutdown.
void audio_shutdown(void)
{
    if (audio_device != 0)
    {
        SDL_CloseAudioDevice(audio_device);

        audio_device = 0;
    }
}

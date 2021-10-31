#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>

using namespace std;
/**
* C++ MorseWav Class file used by morse.cpp
* Convert morse code to STEREO Audio WAV file using PCM
*
* @author Ray Colt <ray_colt@pentagon.mil>
* @copyright Copyright (c) 1978, 2021 Ray Colt
* @license Public General License US Army, Microsoft Corporation (MIT)
**/
class MorseWav
{
private:
    typedef struct PCM16_stereo_s
    {
        int16_t left;
        int16_t right;
    } PCM16_stereo_t;

    PCM16_stereo_t* allocate_PCM16_stereo_buffer(int32_t size)
    {
        return (PCM16_stereo_t*)malloc(sizeof(PCM16_stereo_t) * size);
    }

    PCM16_stereo_t* reallocate_PCM16_stereo_buffer(PCM16_stereo_t* buffer, int32_t size)
    {
        return (PCM16_stereo_t*)realloc(buffer, sizeof(PCM16_stereo_t) * size);
    }

private:
#define EPW 50      // elements per word (definition)
    const char* MorseCode; // string array with morse
    int Debug;      // debug mode
    int Play;       // play WAV file
    const char* Path = "morse.wav";    // output filename
    double Tone;    // tone frequency (Hz)
    double Wpm;     // words per minute
    double Eps;     // elements per second (frequency of basic morse element)
    double Bit;     // duration of basic morse element,cell,quantum (seconds)
    double Sps;     // samples per second (WAV file, sound card)
   // short* pcm_data = NULL; // array with data
    PCM16_stereo_t* buffer_pcm = NULL;
    long pcm_count; // total number of samples
    long wav_size;

public:
    /**
    * Constructor
    */
    MorseWav(const char* morsecode, double tone, double wpm, double samples_per_second, bool play)
    {
        MorseCode = morsecode;
        Wpm = wpm;
        Tone = tone;
        Sps = samples_per_second;
        // Note 60 seconds = 1 minute and 50 elements = 1 morse word.
        Eps = Wpm / 1.2;    // elements per second (frequency of morse coding)
        Bit = 1.2 / Wpm;    // seconds per element (period of morse coding)
        printf("wave: %9.3lf Hz (-sps:%lg)\n", Sps, Sps);
        printf("tone: %9.3lf Hz (-tone:%lg)\n", Tone, Tone);
        printf("code: %9.3lf Hz (-wpm:%lg)\n", Eps, Wpm);
        //show_details();
        check_ratios();
        morse_tone(MorseCode);
        wav_write(Path, buffer_pcm, pcm_count);
        printf("%ld PCM samples", pcm_count);
        printf(" (%.1lf s @ %.1lf kHz)", (double)pcm_count / Sps, Sps / 1e3);
        printf(" written to %s (%.1f kB)\n", Path, wav_size / 1024.0);
        if (play)
        {
            char cmd[1000];
#pragma warning(suppress : 4996)
            sprintf(cmd, "morse.wav /play /close %s", Path);
            printf("** %s\n", cmd);
            system(cmd);
        }
    }

private:
    /**
    * Get binary morse code (dit/dah) for a given character.
    * Generate one quantum of silence or tone in PCM/WAV array.
    * sine wave: y(t) = amplitude * sin(2 * PI * frequency * time), time = s / sample_rate
    *
    * @param on_off
    */
    void tone(int on_off)
    {
        double ampl = 32000.0;//amplitude 32KHz for digital sound
        double pi = 3.1415926535;
        double w = 2.0 * pi * Tone;
        long i, n, size;
        static long seconds;
        if (buffer_pcm == NULL)
        {
            seconds = 1;
            size = (seconds * sizeof buffer_pcm * Sps);
            buffer_pcm = allocate_PCM16_stereo_buffer(size);
        }
        n = (long)(Bit * Sps);
        for (i = 0; i < n; i++)
        {
            double t = (double)i / Sps;
            if (pcm_count == Sps * seconds)
            {
                seconds++;
                size = (seconds * sizeof buffer_pcm * Sps);
                buffer_pcm = reallocate_PCM16_stereo_buffer(buffer_pcm, size);
            }
            pcm_count++;
            buffer_pcm[pcm_count].left = (int32_t)(on_off * ampl * sin(w * t));
            buffer_pcm[pcm_count].right = (int32_t)(on_off * ampl * sin(w * t));
        }
    }

private:
    /**
    * Define dit, dah, end of letter, end of word.
    *
    * The rules of 1/3/7 and 1/2/4:
    * With Farnsworth-units it is 1/3/7, I will use the 1/2/4 because of mobile apps
    * Morse code is: tone for one unit (dit) or three units (dah)
    * followed by the sum of one unit of silence (always),
    * plus two units of silence (if end of letter, one space),
    * plus four units of silence (if also end of word).
    */
    void dit() { tone(1); tone(0); }
    void dah() { tone(1); tone(1); tone(1); tone(0); }
    void space() { tone(0); tone(0); }
    /**
    * Create Tones from morse code.
    *
    * @param code
    */
    void morse_tone(const char* code)
    {
        char c;
        while ((c = *code++) != '\0')
        {
            //printf("%c", c);
            if (c == '.') dit();
            if (c == '-') dah();
            if (c == ' ') space();
        }
    }

private:
    /**
    * Check for sub-optimal combination of rates (poor sounding sinewaves).
    */
    void check_ratios(void)
    {
        char nb[] = "WARNING: sub-optimal sound ratio";
        if (ratio_poor(Sps, Tone))
        {
            printf("%s Sps(%lg) / Tone(%lg) = %.6lf\n", nb, Sps, Tone, Sps / Tone);
        }
        if (ratio_poor(Sps, Eps))
        {
            printf("%s Sps(%lg) / Eps(%lg) = %.6lf\n", nb, Sps, Eps, Sps / Eps);
        }
        if (ratio_poor(Tone, Eps))
        {
            printf("%s Tone(%lg) / Eps(%lg) = %.6lf\n", nb, Tone, Eps, Tone / Eps);
        }
    }

private:
    /**
    * Calculate poor ratio.
    *
    * @param a
    * @param b
    * @return int
    */
    int ratio_poor(double a, double b)
    {
        double ab = a / b;
        long ratio = (long)(ab + 1e-6);
        return fabs(ab - ratio) > 1e-4;
    }

private:
    /**
    * Display detailed data
    */
    void show_details()
    {
        double wps, ms;
        wps = Wpm / 60.0;   // words per second
        Eps = EPW * wps;    // elements per second
        ms = 1000.0 / Eps;  // milliseconds per element
        printf("\n");
        printf("%12.6lf Wpm (words per minute)\n", Wpm);
        printf("%12.6lf wps (words per second)\n", wps);
        printf("%12.6lf EPW (elements per word)\n", (double)EPW);
        printf("%12.6lf Eps (elements per second)\n", Eps);
        printf("\n");
        printf("%12.3lf ms dit\n", ms);
        printf("%12.3lf ms dah\n", ms * 3);
        printf("%12.3lf ms gap (element)\n", ms);
        printf("%12.3lf ms gap (character)\n", ms * 3);
        printf("%12.3lf ms gap (word)\n", ms * 7);
        printf("\n");
        printf("%12.3lf Hz pcm frequency\n", Sps);
        printf("%12.3lf Hz tone frequency\n", Tone);
        printf("%12.3lf    pcm/tone ratio\n", Sps / Tone);
        printf("\n");
        printf("%12.3lf Hz pcm frequency\n", Sps);
        printf("%12.3lf Hz element frequency\n", Eps);
        printf("%12.3lf    pcm/element ratio\n", Sps / Eps);
        printf("\n");
        printf("%12.3lf Hz tone frequency\n", Tone);
        printf("%12.3lf Hz element frequency\n", Eps);
        printf("%12.3lf    tone/element ratio\n", Tone / Eps);
        printf("\n");
    }

private:
    /**
    * Create WAV file from PCM array.
    */
    typedef unsigned short WORD;
    typedef unsigned long DWORD;
    typedef struct _wave
    {
        WORD  wFormatTag;      // format type
        WORD  nChannels;       // number of channels (i.e. mono, stereo...)
        DWORD nSamplesPerSec;  // sample rate
        DWORD nAvgBytesPerSec; // for buffer estimation
        WORD  nBlockAlign;     // block size of data
        WORD  wBitsPerSample;  // number of bits per sample of mono data
        WORD  cbSize;          // size, in bytes, of extra format information 
    } WAVE;

#define FWRITE(buf,size) \
    wav_size += size; \
    if (fwrite(buf, size, 1, file) != 1) { \
        fprintf(stderr, "Write failed: %s\n", path); \
        exit(1); \
    }

    /**
    * Write wav file
    *
    * @param path
    * @param data
    * @param count
    */
    void wav_write(const char* path, PCM16_stereo_t* buffer_pcm, long count)
    {
        long data_size, wave_size, riff_size;
        int fmt_size = 16;
        FILE* file;
        WAVE wave; 
        wave.wFormatTag = 0x1;
        wave.nChannels = 2; // 1 or 2 ~ mono or stereo (BUILD STEREO)
        wave.wBitsPerSample = 16; // 8 or 16
        wave.nBlockAlign = (wave.wBitsPerSample * wave.nChannels) / 8;
        wave.nSamplesPerSec = Sps;
        wave.nAvgBytesPerSec = wave.nSamplesPerSec * wave.nBlockAlign;
        wave.cbSize = 0;
        wave_size = sizeof wave;
        data_size = (count * wave.wBitsPerSample * wave.nChannels) / 8;
        riff_size = fmt_size + wave_size + data_size; // 36 + data_size
#pragma warning(suppress : 4996)
        if ((file = fopen(path, "wb")) == NULL)
        {
            fprintf(stderr, "Open failed: %s\n", path);
            exit(1);
        }
        FWRITE("RIFF", 4);
        FWRITE(&riff_size, 4);
        FWRITE("WAVE", 4);
        FWRITE("fmt ", 4);
        FWRITE(&wave_size, 4);
        FWRITE(&wave, wave_size);
        FWRITE("data", 4);
        FWRITE(&data_size, 4);
        FWRITE(buffer_pcm, data_size);
        fclose(file);
        free(buffer_pcm);
    }
};
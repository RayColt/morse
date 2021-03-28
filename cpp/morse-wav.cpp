#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>

using namespace std;
/**
* C++ MorseWav Class file used by morse.cpp
* Convert morse code to audio WAV file using PCM
*
* @author Ray Colt <ray_colt@pentagon.mil>
* @copyright Copyright (c) 1978, 2021 Ray Colt
* @license Public General License US Army, Microsoft Corporation (MIT)
**/
class MorseWav
{
private:
    #define EPW 50      // elements per word (definition)
    const char *MorseCode;
    int Debug;      // debug mode
    int Play;       // play WAV file
    const char *Path = "morse.wav";    // output filename
    double Tone = 1050;    // tone frequency (Hz)
    double Wpm = 12;     // words per minute
    double Eps;     // elements per second (frequency of basic morse element)
    double Bit;     // duration of basic morse element,cell,quantum (seconds)
    double Sps;     // samples per second (WAV file, sound card)
    short* pcm_data; 
    long pcm_count;
    long wav_size;

public:
    /**
    * Constructor
    */
    MorseWav(const char *morsecode, double tone, double wpm, bool play)
    { 
        MorseCode = morsecode;
        Wpm = wpm;
        Tone = tone;
        Sps = 44100;
        // Note 60 seconds = 1 minute and 50 elements = 1 morse word.
        Eps = Wpm / 1.2;    // elements per second (frequency of morse coding)
        Bit = 1.2 / Wpm;    // seconds per element (period of morse coding)
        printf("wave: %9.3lf Hz (/sps:%lg)\n", Sps, Sps);
        printf("tone: %9.3lf Hz (/tone:%lg)\n", Tone, Tone);
        printf("code: %9.3lf Hz (/wpm:%lg)\n", Eps, Wpm);
        //show_details();
        check_ratios();
        morse_tone(MorseCode);
        wav_write(Path, pcm_data, pcm_count);
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
        double ampl = 32000.0;//amplitude 32KHz for digital sound or 0.85 * 32767 = 27,851.95 Hz;
        double pi = 3.1415926535;
        double w = 2.0 * pi * Tone;
        long i, n, size;
        static long seconds;
        if (pcm_data == NULL)
        {
            seconds = 1;
            size = (long)(Sps * sizeof pcm_data[0] * seconds);
            pcm_data = (short*)malloc(size);
        }
        n = (long)(Bit * Sps);
        for (i = 0; i < n; i += 1)
        {
            double t = (double)i / Sps;
            if (pcm_count == Sps * seconds)
            {
                seconds += 1;
                size = (long)(Sps * sizeof pcm_data[0] * seconds);
                pcm_data = (short*)realloc(pcm_data, size);
            }
            pcm_data[pcm_count++] = (short)(on_off * ampl * sin(w * t));// y = Asin(2πfx + θ)
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
    *
    */
    void dit() { tone(1); tone(0); }
    void dah() { tone(1); tone(1); tone(1); tone(0); }
    void space() { tone(0); tone(0); }
    /**
    * Create Tones fro morse code.
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
    void wav_write(const char* path, short* data, long count)
    {
        long data_size, wave_size, riff_size;
        FILE* file;
        WAVE wave;
        #pragma warning(suppress : 4996)
        if ((file = fopen(path, "wb")) == NULL)
        {
            fprintf(stderr, "Open failed: %s\n", path);
            exit(1);
        }
        wave.wFormatTag = 0x1;
        wave.nChannels = 1;
        wave.wBitsPerSample = sizeof data[0] * 8;
        wave.nBlockAlign = sizeof data[0] * wave.nChannels;
        wave.nSamplesPerSec = (long)Sps;
        wave.nAvgBytesPerSec = (long)Sps * wave.nBlockAlign;
        wave_size = sizeof wave;
        data_size = count * wave.nChannels * (wave.wBitsPerSample / 8);
        riff_size = 20 + wave_size + data_size;
        FWRITE("RIFF", 4);
        FWRITE(&riff_size, 4);
        FWRITE("WAVE", 4);
        FWRITE("fmt ", 4);
        FWRITE(&wave_size, 4);
        FWRITE(&wave, wave_size);
        FWRITE("data", 4);
        FWRITE(&data_size, 4);
        FWRITE(data, data_size);
        fclose(file);
    }
};

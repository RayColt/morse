using System;
using System.Collections.Generic;
using System.Collections.Specialized;
using System.Drawing;
using System.IO;
using System.IO.Pipes;
using System.Linq;
using System.Media;
using System.Reflection;
using System.Reflection.PortableExecutable;
using System.Runtime.InteropServices;
using System.Security.Policy;
using System.Text;
using System.Threading.Tasks;
using static Morse_Code_Sharp.MorseWav;
using static System.Runtime.InteropServices.JavaScript.JSType;


namespace Morse_Wav_Sharp
{
    class MorseWav
    {
        /**
        * Datastructors
        */
        public struct PCM16_stereo_s
        {
            public System.Int16 left;
            public System.Int16 right;
        }
        public struct PCM16_mono_s
        {
            public System.Int16 speaker;
        }

        public static PCM16_stereo_s[] Allocate_PCM16_Stereo_Buffer(int size)
        {
            return new PCM16_stereo_s[size];
        }
        public static PCM16_mono_s[] Allocate_PCM16_Mono_Buffer(int size)
        {
            return new PCM16_mono_s[size];
        }

        public static PCM16_stereo_s[] Reallocate_PCM16_Stereo_Buffer(PCM16_stereo_s[] buffer, int size)
        {
            Array.Resize(ref buffer, size);
            return buffer;
        }

        public static PCM16_mono_s[] Reallocate_PCM16_Mono_Buffer(PCM16_mono_s[] buffer, int size)
        {
            Array.Resize(ref buffer, size);
            return buffer;
        }

        /**
         * Attributes
         */
        private int EPW = 50;      // elements per word (definition)
        private string MorseCode; // string array with morse
        private int Debug;      // debug mode
        private int Play;       // play WAV file
        private ushort MONO_STEREO = 1;   // stereo or mono modus
        private string Path;   // output filename
        private double ToneFrequency;    // tone frequency (Hz)
        private double Wpm;     // words per minute
        private double Eps;     // elements per second (frequency of basic morse element)
        private double Bit;     // duration of basic morse element,cell,quantum (seconds)
        private double Sps;     // samples per second (WAV file, sound card)
        private long pcm_count; // total number of samples
        private long wav_size;  // wave size
        private PCM16_stereo_s[] buffer_stereo_pcm;
        private PCM16_mono_s[] buffer_mono_pcm;

        /**
         * Constructor
         */
        public MorseWav(string morsecode, string filename, double tone, double wpm, double samples_per_second, bool play, ushort modus)
        {

            Path = filename;
            MorseCode = morsecode;
            MONO_STEREO = modus;
            Wpm = wpm;
            ToneFrequency = tone;
            Sps = samples_per_second;
            // Note 60 seconds = 1 minute and 50 elements = 1 morse word.
            Eps = Wpm / 1.2;    // elements per second (frequency of morse coding)
            Bit = 1.2 / Wpm;    // seconds per element (period of morse coding)

            // Initialize a pointer to the current stack memory
                
            CheckRatios();
            MorseTone(MorseCode);
            WavWrite(Path, buffer_mono_pcm, buffer_stereo_pcm, pcm_count);

        }

        /**
        * Get binary morse code (dit/dah) for a given character.
        * Generate one quantum of silence or tone in PCM/WAV array.
        * sine wave: y(t) = amplitude * sin(2 * PI * frequency * time), time = s / sample_rate
        *
        * @param on_off
        */
        private static long seconds = 0;
        private void Tone(int on_off)
        {

                double ampl = 32000.0; // amplitude 32KHz for digital sound (max height of wave)
                double pi = 3.1415926535897932384626433832795;
                double w = 2.0 * pi * ToneFrequency;
                long i, n;
                int size;

                if (MONO_STEREO == 1) // 8 bit - mono
                {
                    if (buffer_mono_pcm == null)
                    {
                        seconds = 1;
                        size = (int)(seconds * Marshal.SizeOf(typeof(PCM16_mono_s)) * Sps);
                        buffer_mono_pcm = Allocate_PCM16_Mono_Buffer(size);
                    }
                }
                else // 16 bit - stereo
                {
                    if (buffer_stereo_pcm == null)
                    {
                        seconds = 1;
                        size = (int)(seconds * Marshal.SizeOf(typeof(PCM16_stereo_s)) * Sps);
                        buffer_stereo_pcm = Allocate_PCM16_Stereo_Buffer(size);
                    }
                }
                n = (long)(Bit * Sps);
                for (i = 0; i < n; i++)
                {
                    double t = (double)i / Sps;
                    if (MONO_STEREO == 1) // MONO
                    {
                        if (pcm_count == Sps * seconds)
                        {
                            seconds++;
                            size = (int)(seconds * Marshal.SizeOf(typeof(PCM16_mono_s)) * Sps);
                            buffer_mono_pcm = Reallocate_PCM16_Mono_Buffer(buffer_mono_pcm, size);
                        }
                        // generate one point on the sine wave
                        buffer_mono_pcm[pcm_count++].speaker = (System.Int16)(on_off * ampl * Math.Sin(w * t));
                    }
                    else // STEREO
                    {
                        if (pcm_count == Sps * seconds)
                        {
                            seconds++;
                            size = (int)(seconds * Marshal.SizeOf(typeof(PCM16_stereo_s)) * Sps);
                            buffer_stereo_pcm = Reallocate_PCM16_Stereo_Buffer(buffer_stereo_pcm, size);
                        }
                        // generate one point on the sine wave for left and right
                        pcm_count++;
                        buffer_stereo_pcm[pcm_count].left = (System.Int16)(on_off * ampl * Math.Sin(w * t));
                        buffer_stereo_pcm[pcm_count].right = (System.Int16)(on_off * ampl * Math.Sin(w * t));
                    } 
                }
        }

        /**
        * Define dit, dah, end of letter, end of word.
        *
        * The rules of 1/3/7 and 1/2/4(more suitable for common microphones, like webcams and phones):
        * Morse code is: tone for one unit (dit) or three units (dah)
        * followed by the sum of one unit of silence (always),
        * plus two units of silence (if end of letter, one space),
        * plus four units of silence (if also end of word).
        */
        private void Dit() { Tone(1); Tone(0); }
        private void Dah() { Tone(1); Tone(1); Tone(1); Tone(0); }
        private void Space() { Tone(0); Tone(0); }

        /**
        * Create Tones from morse code.
        *
        * @param code
        */
        private void MorseTone(string code)
        {
            CharEnumerator charEnumerator = code.GetEnumerator();
            while (charEnumerator.MoveNext())
            {
                if (charEnumerator.Current == '.') Dit();
                if (charEnumerator.Current == '-') Dah();
                if (charEnumerator.Current == ' ') Space();
            }
        }

        /**
        * Check for sub-optimal combination of rates (poor sounding sinewaves).
        */
        private void CheckRatios()
        {
            RatioPoor(Sps, ToneFrequency);
            RatioPoor(Sps, Eps);
            RatioPoor(ToneFrequency, Eps);
        }

        /**
        * Calculate poor ratio.
        *
        * @param a
        * @param b
        * @return int
        */
        private bool RatioPoor(double a, double b)
        {
            double ab = a / b;
            long ratio = (long)(ab + 1e-6);
            return Math.Abs(ab - ratio) > 1e-4;
        }

        /**
        * Display detailed data // not tested
        */
        private void ShowDetails()
        {
            double wps, ms;
            wps = Wpm / 60.0;   // words per second
            Eps = EPW * wps;    // elements per second
            ms = 1000.0 / Eps;  // milliseconds per element
            Console.WriteLine("\n");
            Console.WriteLine("%12.6lf Wpm (words per minute)\n", Wpm);
            Console.WriteLine("%12.6lf wps (words per second)\n", wps);
            Console.WriteLine("%12.6lf EPW (elements per word)\n", (double)EPW);
            Console.WriteLine("%12.6lf Eps (elements per second)\n", Eps);
            Console.WriteLine("\n");
            Console.WriteLine("%12.3lf ms dit\n", ms);
            Console.WriteLine("%12.3lf ms dah\n", ms * 3);
            Console.WriteLine("%12.3lf ms gap (element)\n", ms);
            Console.WriteLine("%12.3lf ms gap (character)\n", ms * 3);
            Console.WriteLine("%12.3lf ms gap (word)\n", ms * 7);
            Console.WriteLine("\n");
            Console.WriteLine("%12.3lf Hz pcm frequency\n", Sps);
            Console.WriteLine("%12.3lf Hz tone frequency\n", ToneFrequency);
            Console.WriteLine("%12.3lf    pcm/tone ratio\n", Sps / ToneFrequency);
            Console.WriteLine("\n");
            Console.WriteLine("%12.3lf Hz pcm frequency\n", Sps);
            Console.WriteLine("%12.3lf Hz element frequency\n", Eps);
            Console.WriteLine("%12.3lf    pcm/element ratio\n", Sps / Eps);
            Console.WriteLine("\n");
            Console.WriteLine("%12.3lf Hz tone frequency\n", ToneFrequency);
            Console.WriteLine("%12.3lf Hz element frequency\n", Eps);
            Console.WriteLine("%12.3lf    tone/element ratio\n", ToneFrequency / Eps);
            Console.WriteLine("\n");
        }

        /**
        * Create WAV file from PCM array.
        */
        private long wavSize = 0;
        private FileStream fileStream = null;

        /**
         * Convert the Wave struct to a byte array.
         */
        private static byte[] StructToBytes(Wave wave)
        {
            int size = Marshal.SizeOf(wave);
            byte[] arr = new byte[size];
            IntPtr ptr = Marshal.AllocHGlobal(size);

            Marshal.StructureToPtr(wave, ptr, true);
            Marshal.Copy(ptr, arr, 0, size);
            Marshal.FreeHGlobal(ptr);

            return arr;
        }

        /*
        private void FWrite(byte[] buffer, int size)
        {
            wavSize += size;
            try
            {
                fileStream.Write(buffer, 0, size);
            }
            catch (Exception ex)
            {
                Console.Error.WriteLine($"Write failed: {fileStream.Name}");
                Console.Error.WriteLine(ex.Message);
                Environment.Exit(1);
            }
        }*/

        /**
         * Handles writing in chunks of 8 KB
         * to ensure it works with large sizes
         */
        private void FWrite(byte[] buffer, long size)
        {
            wavSize += size;
            try
            {
                long offset = 0;
                const int chunkSize = 8192; // 8 KB chunks

                while (offset < size)
                {
                    int bytesToWrite = (int)Math.Min(chunkSize, size - offset);
                    fileStream.Write(buffer, (int)offset, bytesToWrite);
                    offset += bytesToWrite;
                }
            }
            catch (Exception ex)
            {
                Console.Error.WriteLine($"Write failed: {fileStream.Name}");
                Console.Error.WriteLine(ex.Message);
                Environment.Exit(1);
            }
        }

        /**
         *  RIFF Wave Fmt Chunk Struct
         */
        private struct Wave
        {
            public ushort wFormatTag; // format type
            public ushort nChannels; // number of channels (i.e. mono, stereo...)
            public uint nSamplesPerSec; // sample rate
            public uint nAvgBytesPerSec; // for buffer estimation
            public ushort nBlockAlign; // block size of data
            public ushort wBitsPerSample; // number of bits per sample of mono data
            public ushort cbSize; // size, in bytes, of extra format information
        }

        /**
        * Write wav file
        *
        * @param path
        * @param data
        * @param count
        */
        void WavWrite(string path, PCM16_mono_s[] bmpcm, PCM16_stereo_s[] bspcm, long count)
        {
            long data_size, wave_size, riff_size;
            int fmt_size = 16;
            try
            {
                Wave wave = new Wave();
                wave.wFormatTag = 0x1;
                wave.nChannels = MONO_STEREO; // 1 or 2 ~ mono or stereo
                wave.wBitsPerSample = 16; // 8 or 16
                wave.nBlockAlign = (ushort)((wave.wBitsPerSample * wave.nChannels) / 8);
                wave.nSamplesPerSec = (uint)Sps;
                wave.nAvgBytesPerSec = wave.nSamplesPerSec * wave.nBlockAlign;
                wave.cbSize = 0;
                wave_size = Marshal.SizeOf(wave);
                data_size = (count * wave.wBitsPerSample * wave.nChannels) / 8;
                riff_size = fmt_size + wave_size + data_size;

                if (MONO_STEREO == 1 && bmpcm != null)
                {
                    try
                    {
                        fileStream = new FileStream(path, FileMode.Create, FileAccess.Write);
                    }
                    catch (Exception ex)
                    {
                        Console.Error.WriteLine($"Open failed: {path}");
                        Console.Error.WriteLine(ex.Message);
                        Environment.Exit(1);
                    }
                    FWrite(Encoding.ASCII.GetBytes("RIFF"), 4);
                    FWrite(BitConverter.GetBytes(riff_size), 4);
                    FWrite(Encoding.ASCII.GetBytes("WAVE"), 4);
                    FWrite(Encoding.ASCII.GetBytes("fmt "), 4);
                    FWrite(BitConverter.GetBytes(wave_size), 4);
                    FWrite(StructToBytes(wave), wave_size);
                    FWrite(Encoding.ASCII.GetBytes("data"), 4);
                    FWrite(BitConverter.GetBytes(data_size), 4);

                    FWrite(MonoStructArrayToByteArray(bmpcm), data_size);

                    fileStream.Flush();
                    fileStream.Close();
                }
                else if (MONO_STEREO == 2 && bspcm != null) 
                {
                    try
                    {
                        fileStream = new FileStream(path, FileMode.Create, FileAccess.Write);
                    }
                    catch (Exception ex)
                    {
                        Console.Error.WriteLine($"Open failed: {path}");
                        Console.Error.WriteLine(ex.Message);
                        Environment.Exit(1);
                    }
                    FWrite(Encoding.ASCII.GetBytes("RIFF"), 4);
                    FWrite(BitConverter.GetBytes(riff_size), 4);
                    FWrite(Encoding.ASCII.GetBytes("WAVE"), 4);
                    FWrite(Encoding.ASCII.GetBytes("fmt "), 4);
                    FWrite(BitConverter.GetBytes(wave_size), 4);
                    FWrite(StructToBytes(wave), wave_size);
                    FWrite(Encoding.ASCII.GetBytes("data"), 4);
                    FWrite(BitConverter.GetBytes(data_size), 4);

                    FWrite(StereoStructArrayToByteArray(bspcm), data_size);

                    fileStream.Flush();
                    fileStream.Close();
                }
            }
            catch
            {
                Console.WriteLine("Failed to create or write a file.");
            }
        }

        /**
        * Converts the array of PCM16_mono_s struct to a byte array
        *
        * @param buffer
        * @return byte[]
        */
        public static byte[] MonoStructArrayToByteArray(PCM16_mono_s[] buffer)
        {
            int size = Marshal.SizeOf(typeof(PCM16_mono_s));
            byte[] byteArray = new byte[buffer.Length * size];
            // allocates unmanaged memory
            IntPtr ptr = Marshal.AllocHGlobal(size);

            for (int i = 0; i < buffer.Length; i++)
            {
                // copies the struct to the unmanaged memory
                Marshal.StructureToPtr(buffer[i], ptr, true);
                // copies the unmanaged memory to the byte array
                Marshal.Copy(ptr, byteArray, i * size, size);
            }
            // free unmanaged memory
            Marshal.FreeHGlobal(ptr);
            return byteArray;
        }

        /**
        * Converts the array of PCM16_stereo_s struct to a byte array
        *
        * @param buffer
        * @return byte[]
        */
        public static byte[] StereoStructArrayToByteArray(PCM16_stereo_s[] buffer)
        {
            int size = Marshal.SizeOf(typeof(PCM16_stereo_s));
            byte[] byteArray = new byte[buffer.Length * size];
            // allocates unmanaged memory
            IntPtr ptr = Marshal.AllocHGlobal(size);

            for (int i = 0; i < buffer.Length; i++)
            {
                // copies the struct to the unmanaged memory
                Marshal.StructureToPtr(buffer[i], ptr, true);
                // copies the unmanaged memory to the byte array
                Marshal.Copy(ptr, byteArray, i * size, size);
            }
            // free unmanaged memory
            Marshal.FreeHGlobal(ptr);
            return byteArray;
        }
    }
}

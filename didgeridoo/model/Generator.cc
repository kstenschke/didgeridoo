/*
  Copyright (c) Kay Stenschke
  All rights reserved.
  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are met:
   * Redistributions of source code must retain the above copyright notice,
     this list of conditions and the following disclaimer.
   * Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in the
     documentation and/or other materials provided with the distribution.
   * Neither the name of  nor the names of its contributors may be used to
     endorse or promote products derived from this software without specific
     prior written permission.
  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
  POSSIBILITY OF SUCH DAMAGE.
*/

#include <model/Generator.h>

Generator::Generator(double hz) {
  hz_ = hz;
}

void Generator::WriteWord(std::ostream &outs, uint64_t value, uint16_t size) {
  if (size == 0) size = sizeof(value);

  for (; size; --size, value >>= 8)
    outs.put(static_cast <char> (value & 0xFF));
}

Generator* Generator::GenerateTone(
    uint8_t tone, double seconds, uint8_t cut_off) {
  std::string filename = "tmp_" + std::to_string(index_tone_) + ".wav";

  GenerateFreq(GetFrequencyByTone(tone), seconds, filename, cut_off);

  ++index_tone_;

  return this;
}

Generator* Generator::GenerateSilence(double seconds) {
  std::string filename = "tmp_" + std::to_string(index_tone_) + ".wav";

  GenerateFreq(0, seconds, filename, 0);

  ++index_tone_;

  return this;
}

void Generator::ConcatTones(const std::string& filename_result,
                            bool rem_tmp_files) {
  if (index_tone_ == 0) return;

  std::string filename_tone;
  std::string cmd_concat = "sox -q -V0";

  for (auto index = 0; index < index_tone_; ++index)
    cmd_concat += " tmp_" + std::to_string(index) + ".wav";

  cmd_concat += " " + filename_result;

  helper::System::RunShellCommand(cmd_concat.c_str());

  if (rem_tmp_files) helper::System::RunShellCommand("rm tmp_*.wav");
}

void Generator::GenerateFreq(double frequency,
                             double seconds,
                             const std::string& filename,
                             uint8_t cut_off = 0) {
  std::ofstream f(filename, std::ios::binary);

  // Write file headers
  f << "RIFF----WAVEfmt ";  // (chunk size to be filled in later)

  WriteWord(f, 16, 4);   // no extension data
  WriteWord(f, 1, 2);    // PCM - integer samples
  WriteWord(f, 2, 2);    // two channels (stereo file)
  WriteWord(f, hz_, 4);  // samples per second (Hz)
  WriteWord(f, hz_ * 4, 4);  // (Sample Rate * BitsPerSample * Channels) / 8

  WriteWord(f, 4, 2);  // data block size (size of two integer samples,
                       // one for each channel, in bytes)

  WriteWord(f, 16, 2);  // number of bits per sample (use a multiple of 8)

  // Write the data chunk header
  size_t data_chunk_pos = f.tellp();
  f << "data----";  // (chunk size to be filled in later)

  // Write the audio samples
  // (We'll generate a single C4 note with a sine wave,
  // fading from left to right)
  constexpr double two_pi = 6.283185307179586476925286766559;
  constexpr double max_amplitude = 32760;  // "volume"

  int N = hz_ * seconds;  // total number of samples

  uint8_t o = 0;

  for (int n = 0; n < N; n++) {
    double amplitude = (double)n / N * max_amplitude;
    double value     = sin( (two_pi * n * frequency) / hz_ );

    if (0 < cut_off) {
      ++o;
      if (o > cut_off) {
        value = value/2;
        o = 0;
      }
    }

    //value /= sin(n) * 11.0;

    WriteWord(f,
              (int) (amplitude * value),
              2);

    WriteWord(f,
              (int) ((max_amplitude - amplitude) * value),
              2);
  }

  // (We'll need the final file size to fix the chunk sizes above)
  size_t file_length = f.tellp();

  // Fix the data chunk header to contain the data size
  f.seekp( data_chunk_pos + 4 );
  WriteWord(f, file_length - data_chunk_pos + 8);

  // Fix the file header to contain the proper RIFF chunk size,
  // which is (file size - 8) bytes
  f.seekp(0 + 4);
  WriteWord(f, file_length - 8, 4);
}

double Generator::GetFrequencyByTone(uint8_t tone) {
  switch (tone) {
    case 0: return Pitch::C_4;
    case 1: return Pitch::CS4;
    case 2: return Pitch::D_4;
    case 3: return Pitch::DS4;
    case 4: return Pitch::E_4;
    case 5: return Pitch::F_4;
    case 6: return Pitch::FS4;
    case 7: return Pitch::G_4;
    case 8: return Pitch::GS4;
    case 9: return Pitch::A_4;
    case 10: return Pitch::AS4;
    case 11: return Pitch::B_4;

    case 12: return Pitch::C_5;
    case 13: return Pitch::CS5;
    case 14: return Pitch::D_5;
    case 15: return Pitch::DS5;
    case 16: return Pitch::E_5;
    case 17: return Pitch::F_5;
    case 18: return Pitch::FS5;
    case 19: return Pitch::G_5;
    case 20: return Pitch::GS5;
    case 21: return Pitch::A_5;
    case 22: return Pitch::AS5;
    case 23: return Pitch::B_5;

    case 24: return Pitch::C_6;
    case 25: return Pitch::CS6;
    case 26: return Pitch::D_6;
    case 27: return Pitch::DS6;
    case 28: return Pitch::E_6;
    case 29: return Pitch::F_6;
    case 30: return Pitch::FS6;
    case 31: return Pitch::G_6;
    case 32: return Pitch::GS6;
    case 33: return Pitch::A_6;
    case 34: return Pitch::AS6;
    case 35: return Pitch::B_6;

    case 36: return Pitch::C_7;
    case 37: return Pitch::CS7;
    case 38: return Pitch::D_7;
    case 39: return Pitch::DS7;
    case 40: return Pitch::E_7;
    case 41: return Pitch::F_7;
    case 42: return Pitch::FS7;
    case 43: return Pitch::G_7;
    case 44: return Pitch::GS7;
    case 45: return Pitch::A_7;
    case 46: return Pitch::AS7;
    case 47: return Pitch::B_7;

    case 48: return Pitch::C_8;
    case 49: return Pitch::CS8;
    case 50: return Pitch::D_8;
    case 51: return Pitch::DS8;
    case 52: return Pitch::E_8;
    case 53: return Pitch::F_8;
    case 54: return Pitch::FS8;
    case 55: return Pitch::G_8;
    case 56: return Pitch::GS8;
    case 57: return Pitch::A_8;
    case 58: return Pitch::AS8;
    case 59: return Pitch::B_8;

    case 60: return Pitch::C_9;
    case 61: return Pitch::CS9;
    case 62: return Pitch::D_9;
    case 63: return Pitch::DS9;
    case 64: return Pitch::E_9;
    case 65: return Pitch::F_9;
    case 66: return Pitch::FS9;
    case 67: return Pitch::G_9;
    case 68: default: return Pitch::GS9;
  }
}
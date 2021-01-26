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

#include <main.h>
#include <struct/pitch.h>
#include <model/Generator.h>
#include <helper/helper_system.h>

void generateBlare(Generator *generator, uint8_t length,
                   uint8_t multiplier  // multiply tone and speed, max: 6
);

int main() {
  auto generator = new Generator();

  generateBlare(generator, 80, 1);
  generator->ConcatTones("result1.wav");
  helper::System::RunShellCommand("play result1.wav");

  helper::System::RunShellCommand("sleep 0.1");

  generateBlare(generator, 200, 3);
  generator->ConcatTones("result2.wav");
  helper::System::RunShellCommand("play result2.wav");
  helper::System::RunShellCommand("sleep 0.1");
  helper::System::RunShellCommand("play result2.wav");

  helper::System::RunShellCommand("sleep 0.1");
  generateBlare(generator, 120, 1);
  generator->ConcatTones("result3.wav");
  helper::System::RunShellCommand("play result3.wav");

  helper::System::RunShellCommand("play result1.wav");

  helper::System::RunShellCommand("rm *.wav");

  delete generator;
}

// Generate "blare" of concatenated tones
void generateBlare(Generator *generator, uint8_t len_blare, uint8_t multiplier) {
  double len_per_tone = 0.0125;
  auto tone = (rand() % 12) * multiplier;
  bool odd = false;
  uint8_t cut_off = 20;

  uint8_t j = 0;
  for (uint8_t i = 0; i < len_blare; i+= multiplier) {
    if (odd) {
      tone += ( (rand() % 10) > 4)
              ? rand() % 4
              : 1;
    } else {
      tone -= ( (rand() % 10) > 4)
              ? rand() % 8
              : 2;
    }

    if (tone <= 0) {
      tone = (rand() % 12) * multiplier;
    }

    if (j > 10) {
      ++cut_off;
      j = 0;
    }

    generator->GenerateTone(tone, len_per_tone, cut_off);

    odd = !odd;
    ++j;
  }
}

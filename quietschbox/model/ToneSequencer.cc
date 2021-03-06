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

#include <model/ToneSequencer.h>

void ToneSequencer::generate(WaveGenerator *generator,
                             uint8_t len_total,
                             uint8_t length_factor,
                             double step_size,
                             double multiplier,
                             double sub_tone_len,
                             uint8_t sub_tone_len_factor,
                             double toggle_1_freq,
                             uint8_t inc_tone_rnd_factor,
                             double inc_tone_rnd_if_gt,
                             uint8_t inc_tone_rnd_max,
                             double inc_tone_static,
                             uint8_t dec_tone_rnd_factor,
                             double dec_tone_rnd_if_gt,
                             uint8_t dec_tone_rnd_max,
                             double dec_tone_static,
                             double tone_lower_limit,
                             uint8_t tone_reset_when_zero_rnd_factor,
                             double cut_off_base,
                             double saw_tooth_divider,
                             uint32_t saw_tooth_length) {
  auto tone = (rand() % 12) * multiplier;
  uint8_t cut_off = cut_off_base;

  bool toggle_1 = false;

  uint8_t counter_1 = 0;

  uint64_t kI = len_total * length_factor;

  for (uint64_t i = 0; i < kI; i += step_size) {
    if (toggle_1) {
      tone += ((rand() % inc_tone_rnd_factor) > inc_tone_rnd_if_gt)
              ? rand() % inc_tone_rnd_max
              : inc_tone_static;
    } else {
      tone -= ((rand() % dec_tone_rnd_factor) > dec_tone_rnd_if_gt)
              ? rand() % dec_tone_rnd_max
              : dec_tone_static;
    }

    if (tone > 68) {
      tone = 0;
    }

    if (tone <= tone_lower_limit) {
      tone = (rand() % tone_reset_when_zero_rnd_factor) * multiplier;
    }

    if (counter_1 > toggle_1_freq) {
      ++cut_off;
      counter_1 = 0;
    }

    generator->GenerateTone(tone,
                            sub_tone_len_factor * sub_tone_len,
                            cut_off,
                            2.0,
                            1.0,
                            saw_tooth_divider, saw_tooth_length);

    toggle_1 = !toggle_1;
    ++counter_1;
  }
}
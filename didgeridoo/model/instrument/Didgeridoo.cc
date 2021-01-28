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

#include <didgeridoo/model/instrument/Didgeridoo.h>

void Didgeridoo::generate(Generator *generator,
                          uint8_t len_total,
                          double multiplier,
                          double sub_tone_len,
                          uint8_t toggle_1_freq,
                          uint8_t inc_tone_rnd_factor,
                          uint8_t inc_tone_rnd_if_gt,
                          uint8_t inc_tone_rnd_max,
                          uint8_t inc_tone_static,
                          uint8_t dec_tone_rnd_factor,
                          uint8_t dec_tone_rnd_if_gt,
                          uint8_t dec_tone_rnd_max,
                          uint8_t dec_tone_static,
                          uint8_t tone_reset_lower_limit,
                          uint8_t tone_reset_when_zero_rnd_factor) {
  auto tone = (rand() % 12) * multiplier;
  uint8_t cut_off = 20;

  bool toggle_1 = false;

  uint8_t counter_1 = 0;
  uint8_t k, l, m, n = 0;

  for (uint8_t i = 0; i < len_total; i += multiplier) {
    if (toggle_1) {
      tone += ((rand() % inc_tone_rnd_factor) > inc_tone_rnd_if_gt)
              ? rand() % inc_tone_rnd_max
              : inc_tone_static;
    } else {
      tone -= ((rand() % dec_tone_rnd_factor) > dec_tone_rnd_if_gt)
              ? rand() % dec_tone_rnd_max
              : dec_tone_static;
    }

    if (tone <= tone_reset_lower_limit) {
      tone = (rand() % tone_reset_when_zero_rnd_factor) * multiplier;
    }

    if (counter_1 > toggle_1_freq) {
      ++cut_off;
      counter_1 = 0;
    }

    generator->GenerateTone(tone,
                            sub_tone_len,
                            cut_off,
                            2.0,
                            1.0);

    toggle_1 = !toggle_1;
    ++counter_1;
  }
}
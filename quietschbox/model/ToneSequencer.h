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

#ifndef QUIETSCHBOX_QUIETSCHBOX_MODEL_TONESEQUENCER_H_
#define QUIETSCHBOX_QUIETSCHBOX_MODEL_TONESEQUENCER_H_

#include <cstdint>
#include <cstdlib>
#include <model/WaveGenerator.h>

class ToneSequencer {
 public:
  static void generate(WaveGenerator *generator, uint8_t len_total,
                       double iteration_addendum,
                       double multiplier,
                       double sub_tone_len = 0.0125,
                       double toggle_1_freq = 10.0,
                       uint8_t inc_tone_rnd_factor = 10,
                       double inc_tone_rnd_if_gt = 4.0,
                       uint8_t inc_tone_rnd_max = 4,
                       double inc_tone_static = 1.0,
                       uint8_t dec_tone_rnd_factor = 10,
                       double dec_tone_rnd_if_gt = 4.0,
                       uint8_t dec_tone_rnd_max = 8,
                       double dec_tone_static = 2.0,
                       double tone_lower_limit = 0.0,
                       uint8_t tone_reset_when_zero_rnd_factor = 40,
                       double cut_off_base = 20.0);
};

#endif //QUIETSCHBOX_QUIETSCHBOX_MODEL_TONESEQUENCER_H_

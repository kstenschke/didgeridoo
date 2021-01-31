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

#include <helper/helper_gtk.h>
#include <helper/helper_system.h>
#include <model/WaveGenerator.h>
#include <model/ToneSequencer.h>
#include <gtk/gtk.h>

class optionsContainer {
 public:
  // sequence parameters
  GtkAdjustment *seq_len_;
  GtkAdjustment *seq_len_factor_;
  GtkAdjustment *seq_step_size_;

  // tone parameters
  GtkAdjustment *tone_base_len_;
  GtkAdjustment *tone_len_factor_;
  GtkAdjustment *tone_inc_rnd_max_;
  GtkAdjustment *tone_cut_off_base_;
  GtkAdjustment *tone_dec_;
  GtkAdjustment *tone_dec_rnd_factor_;
  GtkAdjustment *tone_saw_tooth_divider_;
  GtkAdjustment *tone_saw_tooth_length_;

  // effect parameters
  GtkAdjustment *fx_band_;
  GtkAdjustment *fx_contrast_;
  GtkAdjustment *fx_fade_in_;
};

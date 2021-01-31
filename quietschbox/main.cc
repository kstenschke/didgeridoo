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

optionsContainer* adjustments;  // global (ugly) accessible slider adjustments

void InitSliderAdjustments();

void AddUiElementsForEffects(const GtkWidget *box_main);
void AddUiElementsBottomButtons(const GtkWidget *box_main);
void AddUiElementsForTone(const GtkWidget *box_main);
void AddUiElementsForSequence(const GtkWidget *box_main);

void Randomize();
void InitForSingleTone();

static void IncTotalLen100(GtkWidget *widget, gpointer data);
static void DecTotalLen100(GtkWidget *widget, gpointer data);
static void DoubleLengthFactor(GtkWidget *widget, gpointer data);
static void DoubleSubToneLengthFactor(GtkWidget *widget, gpointer data);
static void IncCutOffBase10(GtkWidget *widget, gpointer data);
static void DecCutOffBase10(GtkWidget *widget, gpointer data);

static void PlaySample(GtkWidget *widget, gpointer data);

static void Activate(GtkApplication* app, gpointer user_data) {
  GtkWidget *window;
  window = gtk_application_window_new(app);

  gtk_window_set_title(GTK_WINDOW(window), "quietschBox");
  gtk_window_set_default_size(GTK_WINDOW(window), 1020, 540);
  gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
  gtk_window_set_keep_above(GTK_WINDOW(window), TRUE);

  InitSliderAdjustments();

  GtkWidget *box_outer = helper::Gtk::AddBox(window, true, true);
  GtkWidget *box_main = helper::Gtk::AddBox(box_outer, false);

  AddUiElementsForSequence(box_main);
  AddUiElementsForTone(box_main);
  AddUiElementsForEffects(box_main);
  AddUiElementsBottomButtons(box_main);

  gtk_widget_show_all(window);
}

void AddUiElementsForSequence(const GtkWidget *box_main) {
  GtkWidget *box0 = helper::Gtk::AddBox(box_main);
  helper::Gtk::AddLabel(box0, "Sequence:");

  // add sliders
  GtkWidget *box1 = helper::Gtk::AddBox(box_main);
  helper::Gtk::AddLabel(box1, "⇥ Sequence length:  ");
  helper::Gtk::AddScale(box1, adjustments->seq_len_);

  GtkWidget *button_total_len_dec = helper::Gtk::AddButton(box1, "-100");
  g_signal_connect(button_total_len_dec, "clicked",
                   G_CALLBACK(DecTotalLen100), NULL);

  GtkWidget *button_total_len_inc = helper::Gtk::AddButton(box1, "+100");
  g_signal_connect(button_total_len_inc, "clicked",
                   G_CALLBACK(IncTotalLen100), NULL);

  helper::Gtk::AddLabel(box1, "  ✕ Seq. length factor:  ");
  helper::Gtk::AddScale(box1, adjustments->seq_len_factor_);

  GtkWidget *button_double_len_fact = helper::Gtk::AddButton(box1, "x2");
  g_signal_connect(button_double_len_fact, "clicked",
                   G_CALLBACK(DoubleLengthFactor), NULL);

  // add slider
  GtkWidget *box2 = helper::Gtk::AddBox(box_main);
  helper::Gtk::AddLabel(box2, "↷ Seq. step size:  ");
  helper::Gtk::AddScale(box2, adjustments->seq_step_size_);
}

void AddUiElementsForTone(const GtkWidget *box_main) {
  helper::Gtk::AddBox(box_main);  // spacing between sequence and tone
  auto box_tone = helper::Gtk::AddBox(box_main);
  helper::Gtk::AddLabel(box_tone, "Tone:");

  GtkWidget *button_single_tone =
      helper::Gtk::AddButton(box_tone, "Preset: Single Tone");
  g_signal_connect(button_single_tone,
                   "clicked",
                   G_CALLBACK(InitForSingleTone),
                   NULL);

  // add slider
  GtkWidget *box3 = helper::Gtk::AddBox(box_main);
  helper::Gtk::AddLabel(box3, "⇢ Tone base length:  ");
  helper::Gtk::AddScale(box3, adjustments->tone_base_len_);

  helper::Gtk::AddLabel(box3, "  ✕ Tone Length factor:  ");
  helper::Gtk::AddScale(box3, adjustments->tone_len_factor_);

  GtkWidget *button_double_sub_tone_len_fact = helper::Gtk::AddButton(box3, "x2");
  g_signal_connect(button_double_sub_tone_len_fact, "clicked",
                   G_CALLBACK(DoubleSubToneLengthFactor), NULL);

  // add slider
  GtkWidget *box3b = helper::Gtk::AddBox(box_main);
  helper::Gtk::AddLabel(box3b, "Saw-tooth length:  ");
  helper::Gtk::AddScale(box3b, adjustments->tone_saw_tooth_length_);

  helper::Gtk::AddLabel(box3b, "  Saw-tooth divider:  ");
  helper::Gtk::AddScale(box3b, adjustments->tone_saw_tooth_divider_);

  // add slider
  GtkWidget *box4 = helper::Gtk::AddBox(box_main);
  helper::Gtk::AddLabel(box4, "✂ Tone Cut-off base:  ");
  helper::Gtk::AddScale(box4, adjustments->tone_cut_off_base_);

  GtkWidget *button_cut_off_base_dec = helper::Gtk::AddButton(box4, "-10");
  g_signal_connect(button_cut_off_base_dec, "clicked",
                   G_CALLBACK(DecCutOffBase10), NULL);

  GtkWidget *button_cut_off_base_inc = helper::Gtk::AddButton(box4, "+10");
  g_signal_connect(button_cut_off_base_inc, "clicked",
                   G_CALLBACK(IncCutOffBase10), NULL);

  // add sliders: sub-tone randomization
  GtkWidget *box5 = helper::Gtk::AddBox(box_main);
  helper::Gtk::AddLabel(box5, "⊖ Tone RND factor:  ");
  helper::Gtk::AddScale(box5, adjustments->tone_dec_rnd_factor_);

  helper::Gtk::AddLabel(box5, "  ⊖ Tone RND max.:  ");
  helper::Gtk::AddScale(box5, adjustments->tone_inc_rnd_max_);

  // add slider
  GtkWidget *box6 = helper::Gtk::AddBox(box_main);
  helper::Gtk::AddLabel(box6, "↘ Tone decline:  ");
  helper::Gtk::AddScale(box6, adjustments->tone_dec_);
}

void AddUiElementsBottomButtons(const GtkWidget *box_main) {
  helper::Gtk::AddBox(box_main);  // spacing between sliders and options

  GtkWidget *box_bottom = helper::Gtk::AddBox(box_main);
  GtkWidget *button_play = helper::Gtk::AddButton(box_bottom, "▶");
  g_signal_connect(button_play, "clicked", G_CALLBACK(PlaySample), NULL);

  GtkWidget *button_randomize = helper::Gtk::AddButton(box_bottom, "⚄ Random");
  g_signal_connect(button_randomize, "clicked", G_CALLBACK(Randomize), NULL);
}

void AddUiElementsForEffects(const GtkWidget *box_main) {
  helper::Gtk::AddBox(box_main);  // spacing between generator and fx sliders

  GtkWidget *boxfx0 = helper::Gtk::AddBox(box_main);
  helper::Gtk::AddLabel(boxfx0, "Effects:");

  GtkWidget *boxFx1 = helper::Gtk::AddBox(box_main);
  helper::Gtk::AddLabel(boxFx1, "⊿ Fade-in:  ");
  helper::Gtk::AddScale(boxFx1, adjustments->fx_fade_in_);

  GtkWidget *boxFx2 = helper::Gtk::AddBox(box_main);
  helper::Gtk::AddLabel(boxFx2, "– Band:  ");
  helper::Gtk::AddScale(boxFx2, adjustments->fx_band_);

  helper::Gtk::AddLabel(boxFx2, "  ✾ Contrast:  ");
  helper::Gtk::AddScale(boxFx2, adjustments->fx_contrast_);
}

int main(int argc, char **argv) {
  GtkApplication *app;

  adjustments = new optionsContainer();

  app = gtk_application_new(
      "org.kstenschke.quietschbox", G_APPLICATION_FLAGS_NONE);

  g_signal_connect(app, "activate", G_CALLBACK(Activate), NULL);
  int status = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);

  return status;
}

void InitSliderAdjustments() {
  // sequence
  adjustments->seq_len_ =
      gtk_adjustment_new(100.0, 1.0, 1500.0, 1.0, 1.0, 0.0);

  adjustments->seq_len_factor_ =
      gtk_adjustment_new(1.0, 1.0, 100.0, 1.0, 1.0, 0.0);

  adjustments->seq_step_size_ =
      gtk_adjustment_new(1.0, 1.0, 50.0, 1.0, 1.0, 0.0);

  // tone
  adjustments->tone_base_len_ =
      gtk_adjustment_new(50.0, 10.0, 300.0, 1.0, 1.0, 0.0);

  adjustments->tone_cut_off_base_ =
      gtk_adjustment_new(0.0, 0.0, 300.0, 1.0, 1.0, 0.0);

  adjustments->tone_len_factor_ =
      gtk_adjustment_new(1.0, 1.0, 100.0, 1.0, 1.0, 0.0);

  adjustments->tone_saw_tooth_length_ =
      gtk_adjustment_new(0.0, 0.0, 15000.0, 1.0, 1.0, 0.0);

  adjustments->tone_saw_tooth_divider_ =
      gtk_adjustment_new(1.0, 1.0, 300.0, 1.0, 1.0, 0.0);

  adjustments->tone_dec_rnd_factor_ =
      gtk_adjustment_new(10.0, 1.0, 68.0, 1.0, 1.0, 0.0);

  adjustments->tone_dec_ =
      gtk_adjustment_new(2.0, 1.0, 68.0, 1.0, 1.0, 0.0);

  adjustments->tone_inc_rnd_max_ =
      gtk_adjustment_new(4.0, 0.0, 100.0, 1.0, 1.0, 0.0);

  // effects
  adjustments->fx_band_ =
      gtk_adjustment_new(0.0, 0.0, 970.0, 1.0, 1.0, 0.0);

  adjustments->fx_contrast_ =
      gtk_adjustment_new(0.0, 0.0, 100.0, 1.0, 1.0, 0.0);

  adjustments->fx_fade_in_ =
      gtk_adjustment_new(0.0, 0.0, 100.0, 1.0, 1.0, 0.0);
}

void Randomize() {
  gtk_adjustment_set_value(adjustments->seq_step_size_,
                           1 + (rand() % 49));  // min: 1, max: 50

  gtk_adjustment_set_value(adjustments->tone_base_len_,
                           10 + (rand() % 290));  // min: 10, max: 300

  gtk_adjustment_set_value(adjustments->tone_cut_off_base_,
                           (rand() % 300));  // min: 0, max: 300

  gtk_adjustment_set_value(adjustments->tone_dec_rnd_factor_,
                           1 + (rand() % 67));  // min: 1, max: 68

  gtk_adjustment_set_value(adjustments->tone_dec_,
                           1 + (rand() % 67));  // min: 1, max: 68

  gtk_adjustment_set_value(adjustments->tone_dec_,
                           (rand() % 100));  // min: 0, max: 100

  // effects
  gtk_adjustment_set_value(adjustments->fx_band_,
                           (rand() % 970));  // min: 0, max: 970

  gtk_adjustment_set_value(adjustments->fx_contrast_,
                           (rand() % 100));  // min: 0, max: 100
}

void InitForSingleTone() {
  gtk_adjustment_set_value(adjustments->seq_len_, 1);
  gtk_adjustment_set_value(adjustments->tone_base_len_, 300);
  gtk_adjustment_set_value(adjustments->tone_len_factor_, 4);
}

static void IncTotalLen100(GtkWidget *widget, gpointer data) {
  auto value = gtk_adjustment_get_value(adjustments->seq_len_);

  gtk_adjustment_set_value(adjustments->seq_len_, value + 100.0);
}

static void DecTotalLen100(GtkWidget *widget, gpointer data) {
  auto value = gtk_adjustment_get_value(adjustments->seq_len_);

  gtk_adjustment_set_value(adjustments->seq_len_, value - 100.0);
}

static void IncCutOffBase10(GtkWidget *widget, gpointer data) {
  auto value = gtk_adjustment_get_value(adjustments->tone_cut_off_base_);

  gtk_adjustment_set_value(adjustments->tone_cut_off_base_, value + 10.0);
}

static void DecCutOffBase10(GtkWidget *widget, gpointer data) {
  auto value = gtk_adjustment_get_value(adjustments->tone_cut_off_base_);

  gtk_adjustment_set_value(adjustments->tone_cut_off_base_, value - 10.0);
}

static void DoubleLengthFactor(GtkWidget *widget, gpointer data) {
  auto value = gtk_adjustment_get_value(adjustments->seq_len_factor_);

  gtk_adjustment_set_value(adjustments->seq_len_factor_, value * 2.0);
}

static void DoubleSubToneLengthFactor(GtkWidget *widget, gpointer data) {
  auto value = gtk_adjustment_get_value(adjustments->tone_len_factor_);

  gtk_adjustment_set_value(adjustments->tone_len_factor_, value * 2.0);
}

static void PlaySample(GtkWidget *widget, gpointer data) {
  helper::System::RunShellCommand("rm *.wav");

  auto generator = new WaveGenerator();

  ToneSequencer::generate(
      generator,
      gtk_adjustment_get_value(adjustments->seq_len_),
      gtk_adjustment_get_value(adjustments->seq_len_factor_),
      gtk_adjustment_get_value(adjustments->seq_step_size_),
      1.0,
      gtk_adjustment_get_value(adjustments->tone_base_len_) / 5000.0,
      gtk_adjustment_get_value(adjustments->tone_len_factor_),
      10,
      10,
      4,
      gtk_adjustment_get_value(adjustments->tone_inc_rnd_max_),
      gtk_adjustment_get_value(adjustments->tone_cut_off_base_) / 16.0,
      gtk_adjustment_get_value(adjustments->tone_dec_rnd_factor_),
      4.0,
      8,
      gtk_adjustment_get_value(adjustments->tone_dec_),
      0.0,
      40,
      20.0,
      gtk_adjustment_get_value(adjustments->tone_saw_tooth_divider_),
      gtk_adjustment_get_value(adjustments->tone_saw_tooth_length_));

  generator->ConcatTones("out.wav");

  std::string cmd = "play -q --norm out.wav";

  int band = gtk_adjustment_get_value(adjustments->fx_band_);
  if (band > 0) cmd += " band " + std::to_string(10000 - band * 10);

  int contrast = gtk_adjustment_get_value(adjustments->fx_contrast_);
  if (contrast > 0) cmd += " contrast " + std::to_string(contrast);

  int fade = gtk_adjustment_get_value(adjustments->fx_fade_in_);
  if (fade > 0) cmd += " fade " + std::to_string(fade / 100.0);

//  cmd += " fade 0.5";
//  cmd += " echo 0.8 0.88 60 0.4";
//  cmd += " earwax";

  helper::System::RunShellCommand(cmd.c_str());

  delete generator;
}
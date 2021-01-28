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

static void IncTotalLen100 (GtkWidget *widget, gpointer data);
static void DecTotalLen100 (GtkWidget *widget, gpointer data);
static void IncCutOffBase10 (GtkWidget *widget, gpointer data);
static void DecCutOffBase10 (GtkWidget *widget, gpointer data);
static void PlaySample (GtkWidget *widget, gpointer data);

static void Activate (GtkApplication* app, gpointer user_data) {
  GtkWidget *window;
  window = gtk_application_window_new (app);

  gtk_window_set_title (GTK_WINDOW (window), "quietschBox");
  gtk_window_set_default_size (GTK_WINDOW (window), 800, 500);
  gtk_window_set_resizable(GTK_WINDOW (window), FALSE);
  gtk_window_set_keep_above(GTK_WINDOW (window), TRUE);

  GtkWidget *box_outer = helper::Gtk::AddBox(window, true, true);
  GtkWidget *box_main = helper::Gtk::AddBox(box_outer, false);

  InitSliderAdjustments();

  // add sliders
  GtkWidget *box1 = helper::Gtk::AddBox(box_main);
  helper::Gtk::AddLabel(box1, "Total length:  ");
  helper::Gtk::AddScale(box1, adjustments->total_length_);

  GtkWidget *button_total_len_dec = helper::Gtk::AddButton(box1, "-100");
  g_signal_connect(button_total_len_dec, "clicked",
                   G_CALLBACK(DecTotalLen100), NULL);

  GtkWidget *button_total_len_inc = helper::Gtk::AddButton(box1, "+100");
  g_signal_connect(button_total_len_inc, "clicked",
                   G_CALLBACK(IncTotalLen100), NULL);

  // add slider
  GtkWidget *box2 = helper::Gtk::AddBox(box_main);
  helper::Gtk::AddLabel(box2, "Step size:  ");
  helper::Gtk::AddScale(box2, adjustments->it_inc_by_);

  // add slider
  GtkWidget *box3 = helper::Gtk::AddBox(box_main);
  helper::Gtk::AddLabel(box3, "Sub-tone base length:  ");

  helper::Gtk::AddScale(box3, adjustments->sub_tone_base_len_);

  // add slider
  GtkWidget *box4 = helper::Gtk::AddBox(box_main);
  helper::Gtk::AddLabel(box4, "Cut-off base:  ");

  helper::Gtk::AddScale(box4, adjustments->cut_off_base_);

  GtkWidget *button_cut_off_base_dec = helper::Gtk::AddButton(box4, "-10");
  g_signal_connect(button_cut_off_base_dec, "clicked",
                   G_CALLBACK(DecCutOffBase10), NULL);

  GtkWidget *button_cut_off_base_inc = helper::Gtk::AddButton(box4, "+10");
  g_signal_connect(button_cut_off_base_inc, "clicked",
                   G_CALLBACK(IncCutOffBase10), NULL);

  // add slider
  GtkWidget *box5 = helper::Gtk::AddBox(box_main);
  helper::Gtk::AddLabel(box5, "Sub-tone[-] RND factor:  ");
  helper::Gtk::AddScale(box5, adjustments->dec_tone_);

  // add slider
  GtkWidget *box6 = helper::Gtk::AddBox(box_main);
  helper::Gtk::AddLabel(box6, "Sub-tone decline:  ");
  helper::Gtk::AddScale(box6, adjustments->dec_tone_);

  // add slider
  GtkWidget *box7 = helper::Gtk::AddBox(box_main);
  helper::Gtk::AddLabel(box7, "Sub-tone[++] RND max.:  ");
  helper::Gtk::AddScale(box7, adjustments->inc_tone_rnd_max_);

  helper::Gtk::AddBox(box_main);  // spacing between sliders and options

  GtkWidget *box_bottom = helper::Gtk::AddBox(box_main);
  GtkWidget *button_play = helper::Gtk::AddButton(box_bottom, "▶");
  g_signal_connect (button_play, "clicked", G_CALLBACK(PlaySample), NULL);

  gtk_widget_show_all (window);
}

int main(int argc, char **argv) {
  GtkApplication *app;

  adjustments = new optionsContainer();

  app = gtk_application_new(
      "org.kstenschke.quietschbox", G_APPLICATION_FLAGS_NONE);

  g_signal_connect(app, "activate", G_CALLBACK(Activate), NULL);
  int status = g_application_run(G_APPLICATION (app), argc, argv);
  g_object_unref(app);

  return status;
}

void InitSliderAdjustments() {
  adjustments->total_length_ =
      gtk_adjustment_new (100.0, 0.0, 1500.0, 1.0, 1.0, 0.0);

  adjustments->it_inc_by_ =
      gtk_adjustment_new (1.0, 1.0, 50.0, 1.0, 1.0, 0.0);

  adjustments->sub_tone_base_len_ =
      gtk_adjustment_new(50.0, 10.0, 300.0, 1.0, 1.0, 0.0);

  adjustments->cut_off_base_ =
      gtk_adjustment_new(0.0, 0.0, 300.0, 1.0, 1.0, 0.0);

  adjustments->dec_tone_rnd_factor_ =
      gtk_adjustment_new(10.0, 1.0, 68.0, 1.0, 1.0, 0.0);

  adjustments->dec_tone_ =
      gtk_adjustment_new(2.0, 1.0, 68.0, 1.0, 1.0, 0.0);

  adjustments->inc_tone_rnd_max_ =
      gtk_adjustment_new(4.0, 0.0, 100.0, 1.0, 1.0, 0.0);
}

static void IncTotalLen100 (GtkWidget *widget, gpointer data) {
  auto value = gtk_adjustment_get_value(adjustments->total_length_);

  gtk_adjustment_set_value(adjustments->total_length_, value + 100.0);
}

static void DecTotalLen100 (GtkWidget *widget, gpointer data) {
  auto value = gtk_adjustment_get_value(adjustments->total_length_);

  gtk_adjustment_set_value(adjustments->total_length_, value - 100.0);
}

static void IncCutOffBase10 (GtkWidget *widget, gpointer data) {
  auto value = gtk_adjustment_get_value(adjustments->cut_off_base_);

  gtk_adjustment_set_value(adjustments->cut_off_base_, value + 10.0);
}

static void DecCutOffBase10 (GtkWidget *widget, gpointer data) {
  auto value = gtk_adjustment_get_value(adjustments->cut_off_base_);

  gtk_adjustment_set_value(adjustments->cut_off_base_, value - 10.0);
}

static void PlaySample (GtkWidget *widget, gpointer data) {
  helper::System::RunShellCommand("rm *.wav");

  auto generator = new WaveGenerator();

  ToneSequencer::generate(
      generator,
      gtk_adjustment_get_value(adjustments->total_length_),
      gtk_adjustment_get_value(adjustments->it_inc_by_),
      1.0,
      gtk_adjustment_get_value(adjustments->sub_tone_base_len_) / 5000.0,
      10,
      10,
      4,
      gtk_adjustment_get_value(adjustments->inc_tone_rnd_max_),
      gtk_adjustment_get_value(adjustments->cut_off_base_) / 16.0,
      gtk_adjustment_get_value(adjustments->dec_tone_rnd_factor_),
      4.0,
      8,
      gtk_adjustment_get_value(adjustments->dec_tone_));

  generator->ConcatTones("out.wav");

  helper::System::RunShellCommand("play -q --norm out.wav");

  delete generator;
}
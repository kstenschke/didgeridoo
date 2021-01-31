/*
  Copyright (c) Kay Stenschke. All rights reserved.
  Redistribution and use in source and binary forms,
  is NOT permitted without prior written consent.
*/

#ifndef QUIETSCHBOX_HELPER_GTK_H
#define QUIETSCHBOX_HELPER_GTK_H

#include <string>
#include <gtk/gtk.h>

namespace helper {
namespace Gtk {

GtkWidget *AddLabel(const GtkWidget *parent_box, const std::string& text);

GtkWidget *AddBox(const GtkWidget *parent, bool horizontal = true,
                  bool parent_is_window = false);

GtkWidget *AddButton(const GtkWidget *parent, const std::string& text);

void AddScale(const GtkWidget *parent_box, GtkAdjustment *adjustment);
}  // namespace Gtk
}  // namespace helper

#endif

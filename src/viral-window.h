/* viral-window.h
 *
 * Copyright 2022 Joshua Murphy
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include <gtk/gtk.h>
#include <adwaita.h>

#define VIRAL_TYPE_WINDOW (viral_window_get_type())

G_DECLARE_FINAL_TYPE(ViralWindow, viral_window, VIRAL, WINDOW, AdwApplicationWindow)

gboolean viral_window_open_file(GFile *file, gpointer data, gchar *title);
void viral_window_close_file(gpointer data, gpointer user_data);
void viral_window_show_toast(ViralWindow *window, gchar *text);
void viral_window_open_files(ViralWindow *window, GList *file_list);
gboolean viral_window_exit(ViralWindow *window, gpointer data);
void viral_window_set_show_notification(ViralWindow* window, gboolean show);


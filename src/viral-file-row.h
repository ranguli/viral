/* viral-file-row.h
 *
 * Copyright 2022 Joshua Murphy
 *
 * viral is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * viral is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once
#include <gtk/gtk.h>
#include <adwaita.h>
#define VIRAL_TYPE_FILE_ROW (viral_file_row_get_type())

G_DECLARE_FINAL_TYPE(ViralFileRow, viral_file_row, VIRAL, FILE_ROW, AdwActionRow)

ViralFileRow *viral_file_row_new(GFile *file);

gchar *viral_file_row_get_filename(ViralFileRow *row);
void viral_file_row_launch_shredding(gpointer data);
void viral_file_row_shredding_abort(gpointer data);
gboolean viral_file_row_set_progress(gpointer data);
void viral_file_row_set_progress_num(ViralFileRow* row, double progress);


/* viral-progress-icon.h
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
#define VIRAL_TYPE_PROGRESS_ICON (viral_progress_icon_get_type())

G_DECLARE_FINAL_TYPE(ViralProgressIcon, viral_progress_icon, VIRAL, PROGRESS_ICON, GtkDrawingArea)

gdouble viral_progress_icon_get_progress(ViralProgressIcon *self);
void viral_progress_icon_set_progress(ViralProgressIcon *self, gdouble progress);

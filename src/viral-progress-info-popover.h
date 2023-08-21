/* viral-progress-info-popover.h
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

#define VIRAL_PROGRESS_INFO_POPOVER_TYPE (viral_progress_info_popover_get_type())

G_DECLARE_FINAL_TYPE(ViralProgressInfoPopover, viral_progress_info_popover, VIRAL, PROGRESS_INFO_POPOVER, GtkPopover)

ViralProgressInfoPopover *viral_progress_info_popover_new();
void viral_progress_info_popover_set_progress(ViralProgressInfoPopover *popover, gdouble fraction);
void viral_progress_info_popover_pulse(ViralProgressInfoPopover *popover);

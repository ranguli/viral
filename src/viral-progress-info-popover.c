/* viral-progress-info-popover.c
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

#include <gtk/gtk.h>
#include <glib/gi18n.h>
#include "viral-progress-info-popover.h"

struct _ViralProgressInfoPopover
{
    GtkPopover parent;
    GtkWidget *progress_bar;
};

G_DEFINE_TYPE(ViralProgressInfoPopover, viral_progress_info_popover, GTK_TYPE_POPOVER)

static void viral_progress_info_popover_init(ViralProgressInfoPopover *popover)
{
    gtk_widget_init_template(GTK_WIDGET(popover));
    gtk_progress_bar_set_pulse_step(GTK_PROGRESS_BAR(popover->progress_bar), .02);
}

static void viral_progress_info_popover_class_init(ViralProgressInfoPopoverClass *klass)
{
    gtk_widget_class_set_template_from_resource(GTK_WIDGET_CLASS(klass), "/com/github/ranguli/Viral/viral-progress-info-popover.ui");
    gtk_widget_class_bind_template_child(GTK_WIDGET_CLASS(klass), ViralProgressInfoPopover, progress_bar);
}

ViralProgressInfoPopover *viral_progress_info_popover_new()
{
    return g_object_new(viral_progress_info_popover_get_type(), NULL);
}

/* This sets both the progress bar progress and its text. */
void viral_progress_info_popover_set_progress(ViralProgressInfoPopover *popover, gdouble fraction)
{
    double percentage = fraction * 100; // Move the decimal.

    if (percentage < 100)
    {
        gchar *display = g_strdup_printf("%d%%", (int)percentage);
        gtk_progress_bar_set_text(GTK_PROGRESS_BAR(popover->progress_bar), display);
        gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(popover->progress_bar), fraction);
        g_free(display);
    }
    else
    {
        gtk_progress_bar_set_text(GTK_PROGRESS_BAR(popover->progress_bar), _("Finishing up..."));
        gtk_progress_bar_pulse(GTK_PROGRESS_BAR(popover->progress_bar));
    }
}

/* This is used when the spinner is shown instead of the progress icon. */
void viral_progress_info_popover_pulse(ViralProgressInfoPopover *popover)
{
    gtk_progress_bar_set_text(GTK_PROGRESS_BAR(popover->progress_bar), _("Estimating..."));
    gtk_progress_bar_pulse(GTK_PROGRESS_BAR(popover->progress_bar));
}

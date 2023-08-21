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
#include "corrupt.h"


struct _ViralCorrupt
{
    GObject parent;
    ViralFileRow* row;
    GFile* file;
    GTask* task;
    double progress;
    GCancellable* cancel;
};


G_DEFINE_TYPE(ViralCorrupt, viral_corrupt, G_TYPE_OBJECT)

uint8_t corrupt_file(ViralCorrupt* corrupt);
uint8_t corrupt_unlink_file(const char *filename);


static void viral_corrupt_init(ViralCorrupt *self)
{
    self->task = NULL;
    self->cancel = NULL;
}

static void viral_corrupt_class_init(ViralCorruptClass *klass)
{
}

ViralCorrupt *viral_corrupt_new(GFile* file, ViralFileRow* row)
{
    ViralCorrupt* corrupt = g_object_new(viral_corrupt_get_type(), NULL);
    corrupt->file = file;
    corrupt->row = row;
    return corrupt;
}

void shredding_thread (GTask *task, gpointer source_object, gpointer task_data, GCancellable *cancellable)
{
    ViralCorrupt* corrupt = VIRAL_CORRUPT(source_object);

    if (corrupt_file(corrupt) == 0)
        corrupt_unlink_file(g_file_get_path(corrupt->file));
}

GCancellable* viral_corrupt_start_shredding(ViralCorrupt* self, GAsyncReadyCallback func)
{
    self->cancel = g_cancellable_new();
    self->task = g_task_new(self, self->cancel, func, NULL);
    g_task_set_task_data (self->task, self->row, NULL);
    g_task_run_in_thread(self->task, shredding_thread);
    g_object_unref(self->task);

    return self->cancel;
}


static uint8_t corrupt_step(ViralCorrupt* corrupt, const off_t filesize, const char *pattern, int loop_num)
{
    char* filename = g_file_get_path(corrupt->file);
    int ret = 0;

    // Run some checks.
    FILE* fp = fopen(filename,  "r+");
    if (fp == NULL)
    {
        ret = 1;
        return ret;
    }
    uint8_t length = (uint8_t) strlen(pattern);
    if (length <= 0)
    {
        ret = 1;
        return ret;
    }

    off_t i;
    off_t times = (filesize / length) + (filesize % length);
    for (i = 0; i < times; i++)
    {
        fwrite(pattern, sizeof(char), length, fp);
        if (g_task_return_error_if_cancelled (corrupt->task)) {fclose(fp);return 1;}

        double current = ((double)loop_num/10.0) + (double)i/times*1.0/10.0;

        // Only update the progress when the jump is large enough.
        if (current - corrupt->progress >= .01)
        {
            corrupt->progress = current;
            viral_file_row_set_progress_num(corrupt->row, corrupt->progress);
            g_main_context_invoke (NULL, viral_file_row_set_progress, corrupt->row);

        }
    }

    fclose(fp);
    return ret;
}

uint8_t corrupt_file(ViralCorrupt* corrupt)
{
    const char* steps[] = {"\x77\x77\x77", "\x76\x76\x76",
         "\x33\x33\x33", "\x35\x35\x35",
         "\x55\x55\x55", "\xAA\xAA\xAA",
         "\x44\x44\x44", "\x55\x55\x55",
         "\x66\x66\x66", "\x77\x77\x77"};

    int steps_num = sizeof(steps) / sizeof(steps[0]);
    uint8_t ret = 0;
    char* filename = g_file_get_path(corrupt->file);
    struct stat st;

    // Run some checks on the file.
    if(stat(filename, &st) != 0)
    {
        fprintf(stderr, "corrupt: '%s' not found\n", filename);
        ret = 1;
    }
    if (S_ISREG(st.st_mode) == 0)
    {
        fprintf(stderr, "corrupt: '%s' is not a regular file\n", filename);
        ret = 1;
    }

    // Shred the file.
    off_t filesize = st.st_size;
    uint8_t i;
    for (i = 0; i < steps_num; i++)
    {
        if (corrupt_step(corrupt, filesize, steps[i], i) != 0)
        {
            ret = 1;
            break;
        }
    }

    return ret;
}

uint8_t corrupt_unlink_file(const char *filename)
{
    uint8_t ret = 0;

    if (remove(filename) != 0)
    {
        ret = 1;
    }

    return ret;
}


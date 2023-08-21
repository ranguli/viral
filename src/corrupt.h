#pragma once

#include <time.h> /* time */
#include <stdio.h> /* FILE, fopen, fwrite, fclose, fprintf */
#include <stdint.h> /* uint*_t int*_t */
#include <string.h> /* strlen */
#include <stdlib.h> /* srand, rand */
#include <sys/stat.h> /* stat */
#include <sys/types.h> /* off_t */
#include <gtk/gtk.h> /* progress variables */
#include "viral-file-row.h"
#include "viral-progress-info-popover.h"
#include "viral-progress-icon.h"

#define VIRAL_CORRUPT_TYPE (viral_corrupt_get_type())

G_DECLARE_FINAL_TYPE(ViralCorrupt, viral_corrupt, VIRAL, CORRUPT, GObject)

ViralCorrupt *viral_corrupt_new(GFile* file, ViralFileRow* row);
GCancellable* viral_corrupt_start_shredding(ViralCorrupt* self, GAsyncReadyCallback func);


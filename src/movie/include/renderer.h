#pragma once

#include <stdint.h>
#include "frame.h"

typedef void (*Renderer)(const Frame* const, uint32_t);

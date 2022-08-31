// Copyright (c) 2022-2023 Klementiev Dmitry
// SPDX-License-Identifier: GPL-3.0

#pragma once

#include "gnumakegen.h"
#include <string.h>

GNUMakeRule initGNUMakeRule(const char *name) {
    GNUMakeRule retVal;

    retVal.preview = nullptr;
    strcpy(retVal.name, name);
    
    return retVal;
} 

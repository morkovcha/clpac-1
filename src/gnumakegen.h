// Copyright (c) 2022-2023 Klementiev Dmitry
// SPDX-License-Identifier: GPL-3.0

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#define MAX_STR_SIZE 256

#ifndef nullptr
#ifdef NULL
#define nullptr NULL
#else
#define nullptr ((void*)0)
#endif
#endif

typedef struct GNUMakeRule {
    char name[MAX_STR_SIZE];
    char* dep[MAX_STR_SIZE];

    /// Preview rule
    struct GNUMakeRule* preview;

    /// Next rule
    struct GNUMakeRule* next;
} GNUMakeRule;

GNUMakeRule initGNUMakeRule(const char* name);

GNUMakeRule* getGNUMakeRuleWithName(const char* name);

#ifdef __cplusplus
}
#endif

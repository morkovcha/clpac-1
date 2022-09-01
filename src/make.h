// Copyright (c) 2022-2023 Klementiev Dmitry
// SPDX-License-Identifier: GPL-3.0

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>

#define MAX_STR_SIZE 256

typedef enum mkResult {
    MK_SUCCESS,
    MK_FAILURE,

    MK_DESTROY_UNALLOCATED,
    MK_USE_UNALLOCATED,


    MK_UNEXPECTEDLY_ALLOCATED_MEMORY,
} mkResult;

typedef enum mkObject {
    MKOBJ_RULE,
    MKOBJ_CMD,
} mkObject;

typedef struct mkCmd {
    char* command;

    /// Preview make cmd
    struct mkCmd* preview;

    /// Next make cmd
    struct mkCmd* next;
} mkCmd;

typedef struct mkRule {
    char name[MAX_STR_SIZE];
    char* comment;

    mkCmd* cmd;
    
    /// Preview make rule
    struct mkRule* preview;

    /// Next make rule
    struct mkRule* next;
} mkRule;

void* mkCreateObject(mkObject);
mkResult mkDestroyObject(mkObject, void*);

mkResult mkAddCmd(mkCmd* cmds, const char* cmd);

mkResult mkAddRule(const char* name, mkRule* rules);
mkRule* mkFindRule(mkRule* rules, const char* name);
mkResult mkAddRuleCmd(mkRule* rule, const char* cmd);
mkResult mkAddRuleComment(mkRule* rule, const char* comment);



#ifdef __cplusplus
}
#endif
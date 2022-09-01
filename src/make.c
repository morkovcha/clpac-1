// Copyright (c) 2022-2023 Klementiev Dmitry
// SPDX-License-Identifier: GPL-3.0

#include "make.h"
#include <string.h>

//===============----------------------===============//
//==========---------- Make rules ----------==========//

static mkRule* mkCreateRule() {
    mkRule* rule;
    rule = malloc(sizeof(mkRule));
    
    rule->preview = NULL;
    rule->next = NULL;
    
    return rule;
}

static mkResult mkDestroyRule(mkRule* rule) {
    if(rule == NULL) {
        return MK_DESTROY_UNALLOCATED;
    }
    if(rule->next == NULL) {
        mkRule* preview = rule->preview;
        mkDestroyObject(MKOBJ_CMD, rule->cmd);
        free(rule->comment);
        free(rule);
        if(preview != NULL) {
            mkDestroyRule(preview);
        }
    } else {
        mkDestroyRule(rule->next);
    }
    return MK_SUCCESS;
}

mkResult mkAddRule(const char* name, mkRule *rules) {
    if(rules == NULL) {
        return MK_USE_UNALLOCATED;
    }
    if(!rules->name[0]) {
        strcpy(rules->name, name);
    } else {
        if(rules->next == NULL) {
            rules->next = malloc(sizeof(mkRule));
        } else {
            return MK_UNEXPECTEDLY_ALLOCATED_MEMORY;
        }
        rules->next->preview = rules;
        mkAddRule(name, rules->next);
    }
    return MK_SUCCESS;
}

mkRule* mkFindRule(mkRule* rules, const char *name) {
    if(rules == NULL) {
        return NULL;
    } else if(!strcmp(rules->name, name)) {
        return rules;
    } else {
        return mkFindRule(rules->next, name);
    }
}

mkResult mkAddRuleComment(mkRule *rule, const char *comment) {
    if(rule == NULL) {
        return MK_USE_UNALLOCATED;
    }
    unsigned int len = strlen(comment);
    rule->comment = malloc(len);
    strcpy(rule->comment, comment);
    return MK_SUCCESS;
}

mkResult mkAddRuleCmd(mkRule *rule, const char *cmd) {
    if(rule == NULL) {
        return MK_USE_UNALLOCATED;
    }
    if(rule->cmd == NULL) rule->cmd = mkCreateObject(MKOBJ_CMD);
    mkAddCmd(rule->cmd, cmd);
    return MK_SUCCESS;
}

//==========---------- Make rules ----------==========//
//===============----------------------===============//

//===============--------------------===============//
//==========---------- Make cmd ----------==========//

mkCmd* mkCreateCmd() {
    mkCmd* cmd;
    cmd = malloc(sizeof(mkCmd));

    cmd->preview = NULL;
    cmd->next = NULL;
    
    return cmd;
}

mkResult mkDestroyCmd(mkCmd *cmd) {
    if(cmd == NULL) {
        return MK_DESTROY_UNALLOCATED;
    }
    if(cmd->next == NULL) {
        mkCmd* preview = cmd->preview;
        free(cmd->command);
        free(cmd);
        if(preview != NULL) {
            mkDestroyCmd(preview);
        }
    } else {
        mkDestroyCmd(cmd->next);
    }
    return MK_SUCCESS;
}

mkResult mkAddCmd(mkCmd* cmds, const char *cmd) {
    if(cmds == NULL) {
        return MK_USE_UNALLOCATED;
    }
    if(!cmds->command[0]) {
        cmds->command = malloc(strlen(cmd));
        strcpy(cmds->command, cmd);
    } else {
        if(cmds->next == NULL) {
            cmds->next = malloc(sizeof(mkRule));
        } else {
            return MK_UNEXPECTEDLY_ALLOCATED_MEMORY;
        }
        cmds->next->preview = cmds;
        mkAddCmd(cmds->next, cmd);
    }
    return MK_SUCCESS;
}

//==========---------- Make cmd ----------==========//
//===============--------------------===============//


//===============----------------------===============//
//==========---------- Make other ----------==========//

void* mkCreateObject(mkObject object) {
    switch (object) {
    case MKOBJ_RULE:
        return mkCreateRule();
    case MKOBJ_CMD:
        return mkCreateCmd();
    }
}

mkResult mkDestroyObject(mkObject type, void *object) {
    switch(type) {
    case MKOBJ_RULE:
        return mkDestroyRule(object);
    case MKOBJ_CMD:
        return mkDestroyCmd(object);
    }
}

//==========---------- Make other ----------==========//
//===============----------------------===============//

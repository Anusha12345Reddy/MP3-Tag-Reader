#ifndef TYPES_H
#define TYPES_H


typedef unsigned int uint;


typedef enum
{
    p_success,
    p_failure
} Status;

typedef enum
{
    p_view,
    p_edit,
    p_help,
    p_unsupported
} OperationType;

#endif
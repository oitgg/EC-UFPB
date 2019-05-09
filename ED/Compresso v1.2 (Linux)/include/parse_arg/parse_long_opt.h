#ifndef PARSE_LONG_OPT_H_
# define PARSE_LONG_OPT_H_

/*
 * opção : ARG_REQUIRIDO
 *
 * --opção argumento
 * --opção=argumento
 *
 * "'"argumento" tem que ser passado para 'opção'
 */

#include "parse_arg.h"

int parse_long_opt(const char *long_opt, const char *next_opt[], const opts options[], opt_error *error);

#endif 

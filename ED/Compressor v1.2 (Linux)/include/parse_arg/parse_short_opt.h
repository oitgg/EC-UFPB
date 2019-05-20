#ifndef PARSE_SHORT_OPT_H_
# define PARSE_SHORT_OPT_H_

/*
 * h : SEM_ARGUMENTO
 * a : ARG_OPCIONAL
 * l : SEM_ARGUMENTO
 *
 * -hal argument
 *
 * 'argumento' tem que ser passado para a opção 'a'
 *
 * h : SEM_ARGUMENTO
 * a : ARG_OPCIONAL
 * l : ARG_OBRIGATÓRIO
 *
 * -lah argument
 *
 * 'argumento' tem que ser passado para a opção 'l'
 *
 * h : SEM_ARGUMENTO
 * a : ARG_OPCIONAL
 * l : ARG_OPCIONAL
 *
 * -lah argument
 *
 * 'argumento' tem que ser passado para a opção 'a'
 *
 * h : SEM_ARGUMENTO
 * l : ARG_OPCIONAL
 *
 * -l -- -h
 *
 * '-h' tem que ser passado para a opção 'a'
 *
 * h : SEM_ARGUMENTO
 * l : SEM_ARGUMENTO
 *
 * -l -- -h
 *
 * '-h' não é uma opção nesse caso
 */

#include "parse_arg.h"

struct opts_arg
{
    const opts  *opt;
    const char  *arg;
};

int parse_short_opt(const char *short_opt, const char **next_opt, const opts options[], opt_error *error);

#endif 
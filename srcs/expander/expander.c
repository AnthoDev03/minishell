#include "../../include/minishell.h"

char *expand_env_variables(char *input) {
  if (!input) {
    return NULL;
  }

  t_expander exp;
  init_expander(&exp, input);

  while (*(exp.current)) {
    if (*(exp.current) == '\'' && !exp.in_double_quotes) {
      handle_single_quote(&exp);
    } else if (*(exp.current) == '"' && !exp.in_single_quotes) {
      handle_double_quote(&exp);
    } else if (*(exp.current) == '$' &&
               (exp.in_double_quotes ||
                (!exp.in_single_quotes && !exp.in_double_quotes))) {
      expand_env_var(&exp);
    } else {
      *(exp.write_pos)++ = *(exp.current)++;
    }
  }

  *(exp.write_pos) = '\0';

  return exp.expanded_str;
}

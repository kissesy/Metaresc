
#include <stdio.h>
#include <stdlib.h>

#include "suffixes_comments_userdata.h"

int main ()
{
  char type[] = "example_t";
  rl_td_t * td = rl_get_td_by_name (type);
  if (NULL == td)
    printf ("error: can't obtain type information for type '%s'\n", type);
  else
    {
      char * td_serialized = RL_SAVE_CINIT (rl_td_t, td);
      if (NULL == td_serialized)
	printf ("error: can't serialize desciptor for type '%s'\n", type);
      else
	{
	  printf ("Type desciptor for type '%s' is\n%s\n", type, td_serialized);
	  RL_FREE (td_serialized);
	}
    }
  return (EXIT_SUCCESS);
}

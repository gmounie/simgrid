/* Latency tests                                                            */

/* Copyright (c) 2007, 2009-2011, 2013-2015. The SimGrid Team.
 * All rights reserved.                                                     */

/* This program is free software; you can redistribute it and/or modify it
 * under the terms of the license (GNU LGPL) which comes with this package. */

#include <stdio.h>
#include "simgrid/simdag.h"

/*
 * intra communication test
 * independent communication
 * 
 * 0 -> 1 
 * 2 -> 3
 * shared is only switch which is fat pipe
 * should be 1 + 2 latency = 3
 */

int main(int argc, char **argv)
{
  double communication_amount[] = { 0.0, 1.0, 0.0, 0.0,
                                    0.0, 0.0, 0.0, 0.0,
                                    0.0, 0.0, 0.0, 1.0,
                                    0.0, 0.0, 0.0, 0.0 };

  double no_cost[] = { 0.0, 0.0, 0.0, 0.0 };

  SD_init(&argc, argv);
  SD_create_environment(argv[1]);

  SD_task_t task = SD_task_create("Comm 1", NULL, 1.0);

  SD_task_schedule(task, 4, sg_host_list(), no_cost, communication_amount, -1.0);

  SD_simulate(-1.0);

  printf("%g\n", SD_get_clock());
  fflush(stdout);

  SD_task_destroy(task);

  SD_exit();
  return 0;
}
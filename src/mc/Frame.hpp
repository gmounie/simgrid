/* Copyright (c) 2007-2015. The SimGrid Team.
 * All rights reserved.                                                     */

/* This program is free software; you can redistribute it and/or modify it
 * under the terms of the license (GNU LGPL) which comes with this package. */

#ifndef SIMGRID_MC_FRAME_HPP
#define SIMGRID_MC_FRAME_HPP

#include <string>

#include "mc_forward.h"
#include "mc_location.h"

namespace simgrid {
namespace mc {

class Frame {
public:
  Frame();

  int tag;
  std::string name;
  void *low_pc;
  void *high_pc;
  simgrid::mc::LocationList frame_base;
  std::vector<Variable> variables;
  unsigned long int id; /* DWARF offset of the subprogram */
  std::vector<Frame> scopes;
  unsigned long int abstract_origin_id;
  simgrid::mc::ObjectInformation* object_info;
};

}
}

#endif
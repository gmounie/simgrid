/* Copyright (c) 2015. The SimGrid Team.
 * All rights reserved.                                                     */

/* This program is free software; you can redistribute it and/or modify it
 * under the terms of the license (GNU LGPL) which comes with this package. */

#ifndef SIMGRID_HOST_HPP
#define SIMGRID_HOST_HPP

#include <memory>
#include <string>
#include <vector>

#include <xbt/base.h>
#include <xbt/Lib.hpp>

namespace simgrid {

XBT_PUBLIC_CLASS Host : public simgrid::xbt::Lib<Host> {
private:
  std::string id_;
public:
  Host(std::string id);
  ~Host();
  std::string const& id() const { return id_; }
  static Host* find_host(const char* name);
  static Host* get_host(const char* name);
};

}

#endif
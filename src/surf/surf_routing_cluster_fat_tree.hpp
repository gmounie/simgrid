/* Copyright (c) 2014. The SimGrid Team.
 * All rights reserved.                                                     */

/* This program is free software; you can redistribute it and/or modify it
 * under the terms of the license (GNU LGPL) which comes with this package. */

#include "surf_routing_cluster.hpp"

#ifndef SURF_ROUTING_CLUSTER_FAT_TREE_HPP_
#define SURF_ROUTING_CLUSTER_FAT_TREE_HPP_


/* The class AsClusterFatTree describes PGFT, as introduced by Eitan Zahavi
 * in "D-Mod-K Routing Providing Non-Blocking Traffic for Shift Permutations
 * on Real Life Fat Trees" (2010). RLFT are PGFT with some restrictions to 
 * address real world constraints, which are not currently enforced (but it 
 * should certainly be checked for)
 */

/* TODO : limiter link ? Loopback?
 *
 */
class FatTreeNode;
class FatTreeLink;

/* \class FatTreeNode
 * \brief A node in a fat tree
 */
class FatTreeNode {
public:
  /* \brief Unique ID which identifies every node
   */
  int id;
  /* \brief Level into the tree, with 0 being the leafs
   */
  unsigned int level; 
  /* \brief Position into the level, starting from 0
   */
  unsigned int position; 
  /* In order to link nodes between them, each one must be assigned a label,
   * consisting of l integers, l being the levels number of the tree. Each label
   * is unique in the level, and the way it is generated allows the construction
   * of a fat tree which fits the desired topology
   */
  std::vector<unsigned int> label;

  /* Links to the lower level, where the position in the vector corresponds to
   * a port number. 
   */
  std::vector<FatTreeLink*> children;
  /* Links to the upper level, where the position in the vector corresponds to
   * a port number. 
   */ 
  std::vector<FatTreeLink*> parents;

  NetworkLink* limiterLink;
  NetworkLink* loopback;
  FatTreeNode(sg_platf_cluster_cbarg_t cluster, int id, int level,
              int position);
};

class FatTreeLink {
public:
  FatTreeLink(sg_platf_cluster_cbarg_t cluster, FatTreeNode *source,
              FatTreeNode *destination);
  /* Links are dependant of the chosen network model, but must implement 
   * NetworkLink
   */
  NetworkLink *upLink; 
  NetworkLink *downLink;
  FatTreeNode *upNode;
  FatTreeNode *downNode;
};

class AsClusterFatTree : public AsCluster {
public:
  AsClusterFatTree();
  ~AsClusterFatTree();
  virtual void getRouteAndLatency(RoutingEdgePtr src, RoutingEdgePtr dst,
                                  sg_platf_route_cbarg_t into,
                                  double *latency);
  // virtual void getRouteAndLatency(const int src, const int dst,
  //                                 std::vector<NetworkLink> *route,
  //                                 double *latency) const;
  virtual void create_links();
  void parse_specific_arguments(sg_platf_cluster_cbarg_t cluster);
  void addProcessingNode(int id);
  void generateDotFile(const string& filename = "fatTree.dot") const;

private:
  
  //description of a PGFT (TODO : better doc)
  unsigned int levels;
  std::vector<unsigned int> lowerLevelNodesNumber; // number of children by node
  std::vector<unsigned int> upperLevelNodesNumber; // number of parents by node
  std::vector<unsigned int> lowerLevelPortsNumber; // ports between each level l and l-1
  
  std::map<int, FatTreeNode*> computeNodes;
  std::vector<FatTreeNode*> nodes;
  std::vector<FatTreeLink*> links;
  std::vector<unsigned int> nodesByLevel;

  sg_platf_cluster_cbarg_t cluster;

  void addLink(FatTreeNode *parent, unsigned int parentPort,
               FatTreeNode *child, unsigned int childPort);
  int getLevelPosition(const unsigned int level);
  void generateLabels();
  void generateSwitches();
  int connectNodeToParents(FatTreeNode *node);
  bool areRelated(FatTreeNode *parent, FatTreeNode *child);
  bool isInSubTree(FatTreeNode *root, FatTreeNode *node);
};
#endif
/*******************************************************************************
 *  Copyright 2012 maidsafe.net limited                                        *
 *                                                                             *
 *  The following source code is property of maidsafe.net limited and is not   *
 *  meant for external use.  The use of this code is governed by the licence   *
 *  file licence.txt found in the root of this directory and also on           *
 *  www.maidsafe.net.                                                          *
 *                                                                             *
 *  You are not free to copy, amend or otherwise use this source code without  *
 *  the explicit written permission of the board of directors of maidsafe.net. *
 ******************************************************************************/

#ifndef MAIDSAFE_ROUTING_NETWORK_STATISTICS_H_
#define MAIDSAFE_ROUTING_NETWORK_STATISTICS_H_

#include <vector>

#include "maidsafe/common/crypto.h"

#include "maidsafe/common/node_id.h"
#include "maidsafe/routing/node_info.h"


namespace maidsafe {

namespace routing {

namespace test {
  class NetworkStatisticsTest_BEH_AverageDistance_Test;
  class NetworkStatisticsTest_BEH_IsIdInGroupRange_Test;
}

class NetworkStatistics {
 public:
  explicit NetworkStatistics(const NodeId& node_id);
  void UpdateLocalAverageDistance(std::vector<NodeInfo>&& unique_nodes);
  void UpdateNetworkAverageDistance(const NodeId& distance);
  bool EstimateInGroup(const NodeId& sender_id, const NodeId& info_id);
  NodeId GetDistance();
  uint64_t NetworkPopulation(const NodeId& node_id) const;
  uint64_t NetworkPopulation() const;
  void SetMaximumHopsTraversed(const uint16_t& hops_to_live);

  friend class test::NetworkStatisticsTest_BEH_AverageDistance_Test;
  friend class test::NetworkStatisticsTest_BEH_IsIdInGroupRange_Test;

 private:
  NetworkStatistics(const NetworkStatistics&);
  NetworkStatistics& operator=(const NetworkStatistics&);
  struct NetworkDistanceData {
    NetworkDistanceData() : contributors_count(), total_distance(), average_distance() {}
    crypto::BigInt contributors_count, total_distance;
    NodeId average_distance;
  };
  std::mutex mutex_;
  const NodeId kNodeId_;
  NodeId distance_;
  NetworkDistanceData network_distance_data_;
  uint16_t max_hops_traversed_;
};

}  // namespace routing

}  // namespace maidsafe

#endif  // MAIDSAFE_ROUTING_NETWORK_STATISTICS_H_


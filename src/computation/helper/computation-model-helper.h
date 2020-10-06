/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
#ifndef COMPUTATION_HELPER_H
#define COMPUTATION_HELPER_H

#include "ns3/computation-model.h"
#include "ns3/node-info.h"

#include "ns3/node-container.h"
#include "ns3/output-stream-wrapper.h"
#include "ns3/object-factory.h"
#include "ns3/attribute.h"


// #include "ns3/"

namespace ns3 {
class ComputationModel;

class ComputationHelper
{
public:
  /**
   * Construct a Computation Helper which is used to make life easier when working
   * with computation models.
   */
  ComputationHelper();
  /**
   * Destroy a Computation Helper
   */
  ~ComputationHelper();
  /**
   * \param name Name of attribute to set.
   * \param v Value of the attribute.
   *
   * Sets one of the attributes of underlying systeminfo.
   */
  // virtual void Set(std::string name, const AttributeValue &v) = 0;
  /**
   * \brief Aggreates the systeminfo to the node.
   *
   * \param node Pointer to the node where systeminfo will be installed.
   */
  void Install (Ptr<Node> node) const;

  /**
   * \brief Aggreates the systeminfo to the node..
   *
   * \param nodeName Name of the node where systeminfo will be installed.
   */
  void Install (std::string nodeName) const;

  /**
   * \brief Aggreates the systeminfo onto the list of nodes.
   *
   * \param container List of nodes where systeminfo will be installed.
   */
  void Install (NodeContainer container) const;

  /**
   * Installs an systeminfo on all nodes in simulation. 
   */
  void InstallAll (void);
  /**
   * \brief Set the Computation Model object
   * Default is ns3::SimpleComputationModel
   * \param type 
   */
  void SetComputationModel(std::string type);
private:
  static void SystemStateInfoChanged(Ptr<OutputStreamWrapper> stream, 
                                     Ptr<const ComputationModel> computation);
  std::vector<Ptr<ComputationModel>> m_computationStack;//!< Internal stack of computation models
  ObjectFactory m_computationFactory;//!< Object factory to create computation objects

  /**
   * \param node Pointer to node where the systeminfo is to be installed.
   * \returns Pointer to the created SysInfo.
   *
   * Child classes of ComputationHelper only have to implement this function,
   * to create and aggregate an SysInfo object onto a single node. Rest of
   * the installation process (eg. installing SysInfo on set of nodes) is
   * implemented in the ComputationHelper base class.
   */
 // virtual Ptr<SysInfo> DoInstall (Ptr<Node> node) const = 0;
};

}

#endif /* COMPUTATION_MODEL_HELPER_H */


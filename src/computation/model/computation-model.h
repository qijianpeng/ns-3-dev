/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
#ifndef COMPUTATION_MODEL_H
#define COMPUTATION_MODEL_H

#include "ns3/node.h"
#include "ns3/object.h"
#include "ns3/traced-callback.h"
#include <mutex>
#include "node-info.h"
namespace ns3 {
/**
 * \ingroup computation
 * @brief 
 * 
 */
class ComputationModel: public Object
{
public:
  static TypeId GetTypeId(void);
  ComputationModel();
  virtual ~ComputationModel() = 0;

  static inline Ptr<ComputationModel>
  GetComputationModel(Ptr<Object> node);

  void SetSystemStateInfo(const SysInfo &sysInfo);

  SysInfo GetSystemStateInfo(void) const;
  /**
   * \brief Sets pointer to node containing this sysinfo.
   *
   * \param node Pointer to node containing this sysinfo.
   */
  void SetNode (Ptr<Node> node);

  /**
   * \returns Pointer to node containing this syinfo.
   *
   * When a subclass needs to get access to the underlying node base class to
   * print the nodeId for example, it can invoke this method.
   */
  Ptr<Node> GetNode (void) const;
  /**
   *  TracedCallback signature.
   *
   * \param [in] model Value of the ComputationModel.
   */
  typedef void (* TracedCallback)(Ptr<const ComputationModel> model);
protected:
  std::mutex mtx;
  void NotifySystemStateInfoChange(void) const;
private:
  /**
   * \brief Set/Update the current state information of system
   * 
   * \param sysinfo 
   */
  virtual void DoSetSystemStateInfo(const SysInfo& sysinfo) = 0;
  /**
   * 
   * \return the current state information of system 
   */
  virtual SysInfo DoGetSystemStateInfo(void) const = 0;

  ns3::TracedCallback<Ptr<const ComputationModel>> m_sysInfoChangeTrace;
    /**
   * Pointer to node containing this systeminfo. Used by helper class to make
   * sure computation models are installed onto the corresponding node.
   */
  Ptr<Node> m_node;
};

Ptr<ComputationModel>
ComputationModel::GetComputationModel(Ptr<Object> node)
{
  return node->GetObject<ComputationModel>();
}


}//namespace ns3


#endif /* COMPUTATION_MODEL_H */


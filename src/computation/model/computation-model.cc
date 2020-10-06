/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */

#include "computation-model.h"
#include "ns3/log.h"

namespace ns3 {
NS_LOG_COMPONENT_DEFINE("ComputationModel");
NS_OBJECT_ENSURE_REGISTERED(ComputationModel);

TypeId
ComputationModel::GetTypeId(void)
{
  static TypeId tid = TypeId("ns3::ComputationModel")
    .SetParent<Object>()
    .SetGroupName("Computation")
    .AddAttribute("SystemStateInfo", "The current state information of system.",
                  TypeId::ATTR_SET | TypeId::ATTR_GET,
                  SysInfoValue(SysInfo()),
                  MakeSysInfoAccessor(&ComputationModel::SetSystemStateInfo,
                                      &ComputationModel::GetSystemStateInfo),
                  MakeSysInfoChecker())
    .AddTraceSource("SystemStateInfoChange",
                    "The value of the system state changed",
                    MakeTraceSourceAccessor(&ComputationModel::m_sysInfoChangeTrace),
                    "ns3::ComputationModel::TraceCallback")
  ;
  return tid;
}

ComputationModel::ComputationModel()
{

}

ComputationModel::~ComputationModel()
{

}

void ComputationModel::SetSystemStateInfo(const SysInfo &sysInfo)
{
  mtx.lock();
  DoSetSystemStateInfo(sysInfo);
  mtx.unlock();
}

SysInfo ComputationModel::GetSystemStateInfo(void) const
{
  return DoGetSystemStateInfo();
}

void ComputationModel::NotifySystemStateInfoChange(void) const
{
  m_sysInfoChangeTrace(this);
}

void ComputationModel::SetNode(Ptr<Node> node)
{
  NS_LOG_FUNCTION(this);
  NS_ASSERT(node != NULL);
  m_node = node;
}

Ptr<Node> ComputationModel::GetNode(void) const
{
  return m_node;
}


}//namespace ns3


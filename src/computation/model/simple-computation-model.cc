/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */

#include "simple-computation-model.h"

namespace ns3 {
NS_OBJECT_ENSURE_REGISTERED(SimpleComputationModel);

TypeId SimpleComputationModel::GetTypeId(void)
{
  static TypeId tid = TypeId("ns3::SimpleComputationModel")
    .SetParent<ComputationModel>()
    .SetGroupName("Computation")
    .AddConstructor<SimpleComputationModel>()
  ;
  return tid;
}

SimpleComputationModel::SimpleComputationModel()
{
}
SimpleComputationModel::~SimpleComputationModel()
{
}
void SimpleComputationModel::DoSetSystemStateInfo(const SysInfo& sysinfo)
{
  m_helper.SetSystemStateInfo(sysinfo);
  NotifySystemStateInfoChange();
}

SysInfo SimpleComputationModel::DoGetSystemStateInfo(void) const
{
  return m_helper.GetSystemStateInfo();
}

}//namespace ns3

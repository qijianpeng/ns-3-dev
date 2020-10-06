/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */


#ifndef SIMPLE_COMPUTATION_MODEL_H
#define SIMPLE_COMPUTATION_MODEL_H

#include "computation-model.h"
#include "system-info-helper.h"
namespace ns3 {

class SimpleComputationModel: public ComputationModel
{
public:
  static TypeId GetTypeId(void);

  SimpleComputationModel();
  virtual ~SimpleComputationModel();

private:
  virtual void DoSetSystemStateInfo(const SysInfo& sysinfo);
  virtual SysInfo DoGetSystemStateInfo(void) const;

  SystemInfoHelper m_helper; //!< helper object for this model
};




}//namespace ns3

#endif /*SIMPLE_COMPUTATION_MODEL*/
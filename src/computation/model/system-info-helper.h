/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
#ifndef SYSTEM_INFO_HELPER_H
#define SYSTEM_INFO_HELPER_H

#include "computation-model.h"
#include "node-info.h"

namespace ns3{

class SystemInfoHelper
{
public:
  SystemInfoHelper();
  /**
   * \brief create object and set system info.
   * 
   * \param sysinfo 
   */
  SystemInfoHelper(const SysInfo &sysinfo);

  void SetSystemStateInfo(const SysInfo &sysinfo);

  SysInfo GetSystemStateInfo(void) const;

private:
  SysInfo m_sysinfo;

};

}//namspace ns3

#endif /*SYSTEM_INFO_HELPER*/
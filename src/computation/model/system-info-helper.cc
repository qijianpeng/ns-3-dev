/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */

#include "system-info-helper.h"
#include "ns3/log.h"


namespace ns3{

NS_LOG_COMPONENT_DEFINE("SystemInfoHelper");

SystemInfoHelper::SystemInfoHelper(){
  NS_LOG_FUNCTION(this);
}

SystemInfoHelper::SystemInfoHelper(const SysInfo &sysinfo)
: m_sysinfo(sysinfo)
{
  NS_LOG_FUNCTION(this << sysinfo);
}

void
SystemInfoHelper::SetSystemStateInfo(const SysInfo &sysinfo)
{
  NS_LOG_FUNCTION(this << sysinfo);
  m_sysinfo = sysinfo;
}

SysInfo
SystemInfoHelper::GetSystemStateInfo(void) const
{
  NS_LOG_FUNCTION(this);
  return m_sysinfo;
}
}//namspace ns3
/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
#include "node-info.h"
#include "ns3/log.h"
#include "id-gen.h"
namespace ns3 {
NS_LOG_COMPONENT_DEFINE ("SysInfo");

ATTRIBUTE_HELPER_CPP(SysInfo);

SysInfo::SysInfo(const uint64_t cpu, const uint64_t mem):_cpu(cpu), _mem(mem)
{
  NS_LOG_FUNCTION(this<< cpu << mem);
  _uuid = ns3::Gen64Uuid();
}

SysInfo::SysInfo(const SysInfo& si):_cpu(si._cpu), _mem(si._mem), _uuid(si._uuid)
{
  NS_LOG_FUNCTION(this<< si._cpu << si._mem << si._uuid);
}

SysInfo::SysInfo():_cpu(SysInfo::DEFAULT_AVALIABLE_CPU), _mem(SysInfo::DEFAULT_AVALIABLE_MEM)
{
  _uuid = ns3::Gen64Uuid();
  NS_LOG_FUNCTION(this<< _cpu << _mem << _uuid);
}

SysInfo SysInfo::operator-(const SysInfo& si){
  SysInfo tmp;
  if(this->_cpu >= si._cpu && this->_mem >= si._mem){
    tmp._cpu = this->_cpu - si._cpu;
    tmp._mem = this->_mem - si._mem;
    tmp._uuid = this->_uuid;
    return tmp;
  } else {
    throw std::invalid_argument( "SysInfo on current node not avaliable");
  }
}

SysInfo SysInfo::operator+(const SysInfo& si){
  SysInfo tmp;
  tmp._cpu = this->_cpu + si._cpu;
  tmp._mem = this->_mem + si._mem;
  tmp._uuid = this->_uuid;
  if(isValidate()){
    return tmp;
  } else {
    throw std::invalid_argument("Your resources putting back are too high!");
  }
}

std::ostream &operator << (std::ostream &os, const SysInfo &sysinfo){
  os << sysinfo._cpu << ":" << sysinfo._mem << ":" << sysinfo._uuid;
  return os;
}

std::istream &operator >> (std::istream &is, SysInfo &sysinfo){
  char c1,c2;
  is >> sysinfo._cpu >> c1 >> sysinfo._mem >> c2;
  if(c1 != ':' || c2 != ':')
  {
    is.setstate(std::ios_base::failbit);
  }
  return is;
}
}//namespace ns3
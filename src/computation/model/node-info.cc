/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
#include "node-info.h"
#include "ns3/log.h"
namespace ns3 {
NS_LOG_COMPONENT_DEFINE ("SysInfo");

ATTRIBUTE_HELPER_CPP(SysInfo);

SysInfo::SysInfo(const uint64_t cpu, const uint64_t mem):_cpu(cpu), _mem(mem)
{
  NS_LOG_FUNCTION(this<< cpu << mem);
}

SysInfo::SysInfo(const SysInfo& si):_cpu(si._cpu), _mem(si._mem)
{
  NS_LOG_FUNCTION(this<< si._cpu << si._mem);
}

SysInfo::SysInfo():_cpu(SysInfo::DEFAULT_AVALIABLE_CPU), _mem(SysInfo::DEFAULT_AVALIABLE_MEM)
{
  NS_LOG_FUNCTION(this<< _cpu << _mem);
}

SysInfo SysInfo::operator-(const SysInfo& si){
  SysInfo tmp;
  if(this->_cpu >= si._cpu && this->_mem >= si._mem){
    tmp._cpu = this->_cpu - si._cpu;
    tmp._mem = this->_mem - si._mem;
    return tmp;
  } else {
    throw std::invalid_argument( "SysInfo on current node not avaliable");
  }
}

SysInfo SysInfo::operator+(const SysInfo& si){
  SysInfo tmp;
  tmp._cpu = this->_cpu + si._cpu;
  tmp._mem = this->_mem + si._mem;
  if(isValidate()){
    return tmp;
  } else {
    throw std::invalid_argument("Your resources putting back are too high!");
  }
}

std::ostream &operator << (std::ostream &os, const SysInfo &sysinfo){
  os << sysinfo._cpu << ":" << sysinfo._mem;
  return os;
}

std::istream &operator >> (std::istream &is, SysInfo &sysinfo){
  char c;
  is >> sysinfo._cpu >> c >> sysinfo._mem;
  if(c != ':')
  {
    is.setstate(std::ios_base::failbit);
  }
  return is;
}
}//namespace ns3
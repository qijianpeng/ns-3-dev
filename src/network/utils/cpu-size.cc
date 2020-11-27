/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
//
// Copyright (c) 2006 Georgia Tech Research Corporation
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License version 2 as
// published by the Free Software Foundation;
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
// Author: QI Jianpeng<jianpengqi@126.com>
//

#include "cpu-size.h"
#include "ns3/fatal-error.h"
#include "ns3/log.h"

namespace ns3 {
  
NS_LOG_COMPONENT_DEFINE ("CPUSize");

ATTRIBUTE_HELPER_CPP (CPUSize);

/* static */
bool
CPUSize::DoParse (const std::string s, uint64_t *v)
{
  NS_LOG_FUNCTION (s << v);
  std::string::size_type n = s.find_first_not_of ("0123456789.");
  if (n != std::string::npos)
    { // Found non-numeric
      std::istringstream iss;
      iss.str (s.substr (0, n));
      double r;
      iss >> r;
      std::string trailer = s.substr (n, std::string::npos);
      if (trailer == "Hz")
        {
          // bit
          *v = (uint64_t)r;
        }
      else if (trailer == "kHz")
        {
          // kilobits
          *v = (uint64_t)(r * 1000);
        }
      else if (trailer == "KHz")
        {
          // kilobits
          *v = (uint64_t)(r * 1000);
        }
      else if (trailer == "KiHz")
        {
          // kibibit
          *v = (uint64_t)(r * 1024);
        }
      else if (trailer == "MHz")
        {
          // MegaBits
          *v = (uint64_t)(r * 1000000);
        }
      else if (trailer == "MiHz")
        {
          // MebiBits
          *v = (uint64_t)(r * 1048576);
        }
      else if (trailer == "GHz")
        {
          // GigaBit
          *v = (uint64_t)(r * 1000000000);
        }
      else if (trailer == "GiHz")
        {
          // GibiBits
          *v = (uint64_t)(r * 1048576 * 1024);
        }
      else
        {
          return false;
        }
      return true;
    }
  std::istringstream iss;
  iss.str (s);
  iss >> *v;
  return true;
}

CPUSize::CPUSize ()
  : m_cpu (0)
{
  NS_LOG_FUNCTION (this);
}

CPUSize::CPUSize(uint64_t cpu)
  : m_cpu (cpu)
{
  NS_LOG_FUNCTION (this << cpu);
}

bool CPUSize::operator < (const CPUSize& rhs) const
{
  return m_cpu<rhs.m_cpu;
}

bool CPUSize::operator <= (const CPUSize& rhs) const
{
  return m_cpu<=rhs.m_cpu;
}

bool CPUSize::operator >  (const CPUSize& rhs) const
{
  return m_cpu>rhs.m_cpu;
}

bool CPUSize::operator >= (const CPUSize& rhs) const
{
  return m_cpu>=rhs.m_cpu;
}

bool CPUSize::operator == (const CPUSize& rhs) const
{
  return m_cpu==rhs.m_cpu;
}

bool CPUSize::operator != (const CPUSize& rhs) const
{
  return m_cpu!=rhs.m_cpu;
}

uint64_t CPUSize::GetCPUSize () const
{
  NS_LOG_FUNCTION (this);
  return m_cpu;
}

CPUSize::CPUSize (std::string size)
{
  NS_LOG_FUNCTION (this << size);
  bool ok = DoParse (size, &m_cpu);
  if (!ok)
    {
      NS_FATAL_ERROR ("Could not parse size: "<<size);
    }
}

/* For printing of CPU size */
std::ostream &operator << (std::ostream &os, const CPUSize &size)
{
  os << size.GetCPUSize () << "Hz";
  return os;
}
/* Initialize a CPU size from an input stream */
std::istream &operator >> (std::istream &is, CPUSize &size)
{
  std::string value;
  is >> value;
  uint64_t v;
  bool ok = CPUSize::DoParse (value, &v);
  if (!ok)
    {
      is.setstate (std::ios_base::failbit);
    }
  size = CPUSize (v);
  return is;
}


} // namespace ns3

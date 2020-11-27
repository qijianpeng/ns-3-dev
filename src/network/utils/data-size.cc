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

#include "data-size.h"
#include "ns3/fatal-error.h"
#include "ns3/log.h"

namespace ns3 {
  
NS_LOG_COMPONENT_DEFINE ("DataSize");

ATTRIBUTE_HELPER_CPP (DataSize);

/* static */
bool
DataSize::DoParse (const std::string s, uint64_t *v)
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
      if (trailer == "b")
        {
          // bit
          *v = (uint64_t)r;
        }
      else if (trailer == "B")
        {
          // byte
          *v = (uint64_t)(r * 8);
        }
      else if (trailer == "kb")
        {
          // kilobits
          *v = (uint64_t)(r * 1000);
        }
      else if (trailer == "Kb")
        {
          // kilobits
          *v = (uint64_t)(r * 1000);
        }
      else if (trailer == "kB")
        {
          // kiloByte
          *v = (uint64_t)(r * 8000);
        }
      else if (trailer == "KB")
        {
          // kiloByte
          *v = (uint64_t)(r * 8000);
        }
      else if (trailer == "Kib")
        {
          // kibibit
          *v = (uint64_t)(r * 1024);
        }
      else if (trailer == "KiB")
        {
          // kibibyte
          *v = (uint64_t)(r * 8192);
        }
      else if (trailer == "Mb")
        {
          // MegaBits
          *v = (uint64_t)(r * 1000000);
        }
      else if (trailer == "MB")
        {
          // MegaBytes
          *v = (uint64_t)(r * 8000000);
        }
      else if (trailer == "Mib")
        {
          // MebiBits
          *v = (uint64_t)(r * 1048576);
        }
      else if (trailer == "MiB")
        {
          // MebiByte
          *v = (uint64_t)(r * 1048576 * 8);
        }
      else if (trailer == "Gb")
        {
          // GigaBit
          *v = (uint64_t)(r * 1000000000);
        }
      else if (trailer == "GB")
        {
          // GigaByte
          *v = (uint64_t)(r * 8*1000000000);
        }
      else if (trailer == "Gib")
        {
          // GibiBits
          *v = (uint64_t)(r * 1048576 * 1024);
        }
      else if (trailer == "GiB")
        {
          // GibiByte
          *v = (uint64_t)(r * 1048576 * 1024 * 8);
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

DataSize::DataSize ()
  : m_b (0)
{
  NS_LOG_FUNCTION (this);
}

DataSize::DataSize(uint64_t b)
  : m_b (b)
{
  NS_LOG_FUNCTION (this << b);
}

bool DataSize::operator < (const DataSize& rhs) const
{
  return m_b<rhs.m_b;
}

bool DataSize::operator <= (const DataSize& rhs) const
{
  return m_b<=rhs.m_b;
}

bool DataSize::operator >  (const DataSize& rhs) const
{
  return m_b>rhs.m_b;
}

bool DataSize::operator >= (const DataSize& rhs) const
{
  return m_b>=rhs.m_b;
}

bool DataSize::operator == (const DataSize& rhs) const
{
  return m_b==rhs.m_b;
}

bool DataSize::operator != (const DataSize& rhs) const
{
  return m_b!=rhs.m_b;
}

uint64_t DataSize::GetBitSize () const
{
  NS_LOG_FUNCTION (this);
  return m_b;
}

DataSize::DataSize (std::string size)
{
  NS_LOG_FUNCTION (this << size);
  bool ok = DoParse (size, &m_b);
  if (!ok)
    {
      NS_FATAL_ERROR ("Could not parse size: "<<size);
    }
}

/* For printing of data size */
std::ostream &operator << (std::ostream &os, const DataSize &size)
{
  os << size.GetBitSize () << "b";
  return os;
}
/* Initialize a data size from an input stream */
std::istream &operator >> (std::istream &is, DataSize &size)
{
  std::string value;
  is >> value;
  uint64_t v;
  bool ok = DataSize::DoParse (value, &v);
  if (!ok)
    {
      is.setstate (std::ios_base::failbit);
    }
  size = DataSize (v);
  return is;
}


} // namespace ns3

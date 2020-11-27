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

#ifndef DATA_SIZE_H
#define DATA_SIZE_H

#include <string>
#include <iostream>
#include <stdint.h>
#include "ns3/attribute.h"
#include "ns3/attribute-helper.h"
#include "ns3/deprecated.h"

namespace ns3 {

/**
 * \ingroup network
 * \defgroup datasize Data Size
 */
/**
 * \ingroup datasize
 * \brief Class for representing data size
 *
 * Allows for natural and familiar use of data size.  Allows construction
 * from strings, natural multiplication e.g.:
 * \code
 *   DataSize x("56kb");
 * \endcode
 * This class also supports the regular comparison operators \c <, \c >,
 * \c <=, \c >=, \c ==, and \c !=
 *
 * Data size specifiers consist of
 * * A numeric value,
 * * An optional multiplier prefix and
 * * A unit.
 *
 * Whitespace is allowed but not required between the numeric value and
 * multipler or unit.
 *
 * Supported multiplier prefixes:
 *
 * | Prefix   | Value       |
 * | :------- | ----------: |
 * | "k", "K" | 1000        |
 * | "Ki"     | 1024        |
 * | "M"      | 1000000     |
 * | "Mi"     | 1024 Ki     |
 * | "G"      | 10^9        |
 * | "Gi "    | 1024 Mi     |
 *
 * Supported unit strings:
 *
 * | Symbol   | Meaning     |
 * | :------- | :---------- |
 * | "b"      | bits        |
 * | "B"      | 8-bit bytes |
 *
 * Examples:
 * * "56kb" = 56,000 bits
 * * "128 kb" = 128,000 bits
 * * "8Kib" = 1 KiB = 8192 bits
 * * "1kB" = 8000 bits
 *
 * \see attribute_DataSize
 */
class DataSize
{
public:
  DataSize ();
  /**
   * \brief Integer constructor
   *
   * Construct a data size from an integer.  This class only supports positive
   * integer data size in units of bits, meaning 1bit is the smallest 
   * non-trivial bitsize available.
   * \param b bit value
   */
  DataSize (uint64_t b);
  /**
   * \brief String constructor
   *
   * Construct a data size from a string.  Many different unit strings are supported
   * Supported unit strings:
   * b, B, \n
   * kb, Kb, kB, KB, Kib, KiB \n
   * Mb, MB, Mib, MiB \n
   * Gb, GB, Gib, GiB \n
   * 
   * Examples:
   * "56kbps" = 56,000 bits/s \n
   * "128 kb/s" = 128,000 bits/s \n
   * "8Kib/s" = 1 KiB/s = 8192 bits/s \n
   * "1kB/s" = 8000 bits/s 
   *
   * \param size string representing the desired size
   */
  DataSize (std::string size);

  /**
   * \return true if this size is less than rhs
   *
   * \param rhs the datasize to compare to this datasize
   */  
  bool operator <  (const DataSize& rhs) const;

  /**
   * \return true if this size is less than or equal to rhs
   *
   * \param rhs the datasize to compare to this datasize
   */ 
  bool operator <= (const DataSize& rhs) const;
  
  /**
   * \return true if this size is greater than rhs
   *
   * \param rhs the datasize to compare to this datasize
   */   
  bool operator >  (const DataSize& rhs) const;
  
  /**
   * \return true if this size is greater than or equal to rhs
   *
   * \param rhs the datasize to compare to this datasize
   */   
  bool operator >= (const DataSize& rhs) const;
  
  /**
   * \return true if this size is equal to rhs
   *
   * \param rhs the datasize to compare to this datasize
   */   
  bool operator == (const DataSize& rhs) const;
  
  /**
   * \return true if this size is not equal to rhs
   *
   * \param rhs the datasize to compare to this datasize
   */   
  bool operator != (const DataSize& rhs) const;

  /**
   * Get the underlying bitsize
   * \return The underlying bitsize in bits
   */
  uint64_t GetBitSize () const;

private:

  /**
   * \brief Parse a string representing a DataSize into an uint64_t
   *
   * Allowed unit representations include all combinations of
   *
   * * An SI prefix: k, K, M, G
   * * Decimal or kibibit (as in "Kib", meaning 1024 bits)
   * * Bits or bytes (8 bits)
   *
   * \param [in] s The string representation, including unit
   * \param [in,out] v The location to put the value, in bits/sec.
   * \return true if parsing was successful.
   */
  static bool DoParse (const std::string s, uint64_t *v);

  // Uses DoParse
  friend std::istream &operator >> (std::istream &is, DataSize &size);
  
  uint64_t m_b; //!< data size [bits]
};

/**
 * \brief Stream insertion operator.
 *
 * \param os the stream
 * \param size the data size
 * \returns a reference to the stream
 */
std::ostream &operator << (std::ostream &os, const DataSize &size);

/**
 * \brief Stream extraction operator.
 *
 * \param is the stream
 * \param size the data size
 * \returns a reference to the stream
 */
std::istream &operator >> (std::istream &is, DataSize &size);

ATTRIBUTE_HELPER_HEADER (DataSize);


} // namespace ns3

#endif /* DATA_SIZE_H */

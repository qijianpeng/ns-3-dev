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

#ifndef CPU_SIZE_H
#define CPU_SIZE_H

#include <string>
#include <iostream>
#include <stdint.h>
#include "ns3/attribute.h"
#include "ns3/attribute-helper.h"
#include "ns3/deprecated.h"

namespace ns3 {

/**
 * \ingroup network
 * \defgroup CPUSize CPU Size
 */
/**
 * \ingroup CPUSize
 * \brief Class for representing CPU size
 *
 * Allows for natural and familiar use of CPU size.  Allows construction
 * from strings, natural multiplication e.g.:
 * \code
 *   CPUSize x("56kb");
 * \endcode
 * This class also supports the regular comparison operators \c <, \c >,
 * \c <=, \c >=, \c ==, and \c !=
 *
 * CPU size specifiers consist of
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
 * | "Hz"     | hertz       |
 *
 * Examples:
 * * "56kHz" = 56,000 Hz
 * * "128 kHz" = 128,000 Hz
 *
 * \see attribute_CPUSize
 */
class CPUSize
{
public:
  CPUSize ();
  /**
   * \brief Integer constructor
   *
   * Construct a CPU size from an integer.  This class only supports positive
   * integer CPU size in units of bits, meaning 1bit is the smallest 
   * non-trivial bitsize available.
   * \param b bit value
   */
  CPUSize (uint64_t b);
  /**
   * \brief String constructor
   *
   * Construct a CPU size from a string.  Many different unit strings are supported
   * Supported unit strings:
   * kHz, KiHz \n
   * MHz, MiHz \n
   * GHz, GiHz\n
   * 
   * Examples:
   * "56kHz" = 56,000 Hz \n
   * "128 kHz" = 128,000 Hz \n
   * "8KiHz" = 1 KiHz = 8192 Hz \n
   *
   * \param size string representing the desired size
   */
  CPUSize (std::string size);

  /**
   * \return true if this size is less than rhs
   *
   * \param rhs the CPUSize to compare to this CPUSize
   */  
  bool operator <  (const CPUSize& rhs) const;

  /**
   * \return true if this size is less than or equal to rhs
   *
   * \param rhs the CPUSize to compare to this CPUSize
   */ 
  bool operator <= (const CPUSize& rhs) const;
  
  /**
   * \return true if this size is greater than rhs
   *
   * \param rhs the CPUSize to compare to this CPUSize
   */   
  bool operator >  (const CPUSize& rhs) const;
  
  /**
   * \return true if this size is greater than or equal to rhs
   *
   * \param rhs the CPUSize to compare to this CPUSize
   */   
  bool operator >= (const CPUSize& rhs) const;
  
  /**
   * \return true if this size is equal to rhs
   *
   * \param rhs the CPUSize to compare to this CPUSize
   */   
  bool operator == (const CPUSize& rhs) const;
  
  /**
   * \return true if this size is not equal to rhs
   *
   * \param rhs the CPUSize to compare to this CPUSize
   */   
  bool operator != (const CPUSize& rhs) const;

  /**
   * Get the underlying CPUsize
   * \return The underlying CPUsize in Hz
   */
  uint64_t GetCPUSize () const;

private:

  /**
   * \brief Parse a string representing a CPUSize into an uint64_t
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
  friend std::istream &operator >> (std::istream &is, CPUSize &size);
  
  uint64_t m_cpu; //!< CPU size [bits]
};

/**
 * \brief Stream insertion operator.
 *
 * \param os the stream
 * \param size the CPU size
 * \returns a reference to the stream
 */
std::ostream &operator << (std::ostream &os, const CPUSize &size);

/**
 * \brief Stream extraction operator.
 *
 * \param is the stream
 * \param size the CPU size
 * \returns a reference to the stream
 */
std::istream &operator >> (std::istream &is, CPUSize &size);

ATTRIBUTE_HELPER_HEADER (CPUSize);


} // namespace ns3

#endif /* CPU_SIZE_H */

/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/**
 * @file node-resources.hpp
 * @author QI-Jianpeng
 * @brief Node resource
 * @version 0.1
 * @date 2020-09-08
 * 
 * @copyright Copyright (c) 2020
 * 
 * Requirement: Install the RapidJSON(https://github.com/Tencent/rapidjson) into your `include` lib.
 * Steps:
 * \code{.sh}
     git clone https://github.com/Tencent/rapidjson.git 
     cd rapidjson/
     git submodule update --init
     mkdir build
     cd build
     cmake ..
     make
     make install
 * \endcode
 * Usage:
 * \code{.cpp}
     SysInfo si(100,200);
     std::string str = si.Serialize();
     SysInfo der;
     der.DeSerialize(str);
 * \endcode
 */
#ifndef SYSINFO_H
#define SYSINFO_H

#include "ns3/attribute.h"
#include "ns3/attribute-helper.h"

#include <rapidjson/rapidjson.h>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/prettywriter.h" // for stringify JSON
#include "rapidjson/stringbuffer.h"
#include <iostream>
#include <stdexcept>

namespace ns3{
using namespace rapidjson;
//TODO(qjp): Add a static method to get the 
//           current system avaliable resources.
class SysInfo{
  public:
    static const uint64_t DEFAULT_AVALIABLE_CPU = 1000l;
    static const uint64_t DEFAULT_AVALIABLE_MEM = 1000l;

    SysInfo(const uint64_t cpu, const uint64_t mem);
    SysInfo(const SysInfo& si);
    SysInfo();

    ~SysInfo(){}
    /**
     * @brief Get resources from the current node.
     * 
     * @param si 
     * @return SysInfo 
     */
    SysInfo operator-(const SysInfo& si);
    /**
     * @brief Restore the resources
     * 
     * @param si 
     * @return SysInfo& 
     */
    SysInfo operator+(const SysInfo& si);
    bool isCPUAvaliable(){
      return _cpu >=0;
    }
    bool isMemAvaliable(){
      return _mem >= 0;
    }
    bool isValidate(){
      return _cpu <= DEFAULT_AVALIABLE_CPU && _mem <= DEFAULT_AVALIABLE_MEM;
    }

 
    template <typename Writer>
    void Serialize(Writer& writer) const {
        writer.StartObject();
        writer.String("cpu");
        writer.Uint64(_cpu);
        writer.String("mem");
        writer.Uint64(_mem);
        writer.String("uuid");
        writer.Uint64(_uuid);
        writer.EndObject();
    }
    std::string Serialize(){
      StringBuffer sb;
      PrettyWriter<StringBuffer> writer(sb);
      this->Serialize(writer);
      return sb.GetString();
    }
    void DeSerialize(const rapidjson::Value & obj){
      this->_cpu = obj["cpu"].GetUint64();
      this->_mem = obj["mem"].GetUint64();
      this->_uuid = obj["uuid"].GetUint64();
    }
    void DeSerialize(const std::string &str){
      rapidjson::Document doc;
       doc.Parse(str.c_str());
       this->DeSerialize(doc);
    }

    uint64_t getCPU(){
      return _cpu;
    }
    uint64_t getMem(){
      return _mem;
    }
    uint64_t getUuid()
    {
      return _uuid;
    }
  /**
   * Output streamer.
   * SysInfo are written as "cpu:mem".
   *
   * \param [in,out] os The stream.
   * \param [in] sysinfo The sysinfo to stream
   * \return The stream.
   */
  friend std::ostream &operator << (std::ostream &os, const SysInfo &sysinfo);

  /**
   * Input streamer.
   *
   * SysInfo are expected to be in the form "cpu:mem".
   *
   * \param [in,out] is The stream.
   * \param [in] sysinfo The sysinfo.
   * \returns The stream.
   */
  friend std::istream &operator >> (std::istream &is, SysInfo &sysinfo);

  private:
    uint64_t _cpu;
    uint64_t _mem;
    uint64_t _uuid; //uuid of this node. Different from `Node::GetId()`.
};
 std::ostream &operator << (std::ostream &os, const SysInfo &sysinfo);
 std::istream &operator >> (std::istream &is, SysInfo &sysinfo);

 ATTRIBUTE_HELPER_HEADER(SysInfo);

 Ptr<const AttributeChecker> MakeSysInfoChecker(void);
}//namespace ns3

#endif /*NODEINFO_H*/
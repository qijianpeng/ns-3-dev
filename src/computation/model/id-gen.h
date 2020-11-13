#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/lexical_cast.hpp>

#ifndef ID_GEN_H
#define ID_GEN_H
namespace ns3
{
std::string Genuuid(const int startPos, const int lengthHex)
{
  boost::uuids::random_generator gen;
  boost::uuids::uuid uuidId = gen();
  std::string randomUUID = boost::lexical_cast<std::string>(uuidId);
  std::remove( randomUUID.begin(), randomUUID.end(), '-');
  randomUUID = "0x" + randomUUID.substr(startPos, lengthHex);
  return randomUUID;
}
uint64_t Gen64Uuid()
{
  uint64_t ui64 = 0;
  const int startPosition = 18;//can vary - we can use rand() too
  const int lengthHex = 14;//can vary - we can use rand() too
  std::string randomUUID = Genuuid(startPosition, lengthHex);
  ui64 = std::stoull(randomUUID, 0, 16); //random out of UUID
  return ui64;
}
}//namespace ns3

#endif /*ID_GEN_H*/
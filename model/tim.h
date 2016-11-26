#ifndef TIM_H
#define TIM_H

#include "ns3/wifi-information-element.h"
#include "ns3/mac48-address.h"
#include <set>

using namespace std;
namespace ns3 {
  class Tim : public WifiInformationElement
  {
  public:
    Tim();
    ~Tim();
    void AddNodeIp(Mac48Address a);
    void DeleteNodeIp(Mac48Address a);
    bool ExistNodeIp(Mac48Address a);
    WifiInformationElementId ElementId () const;
    uint8_t GetInformationFieldSize () const;
    void SerializeInformationField (Buffer::Iterator start) const;
    uint8_t DeserializeInformationField (Buffer::Iterator start,
                                       uint8_t length);
    set<Mac48Address> addressList;
  private:
    int size;
  };
}

#endif

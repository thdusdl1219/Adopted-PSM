#include "tim.h"
#include "ns3/assert.h"
#include <cstring>

namespace ns3 {
  Tim::Tim ()
  {
    size = 0;
    addressList = set<Mac48Address> ();
  }
  Tim::~Tim()
  {
    addressList.clear();
  }
  void Tim::AddNodeIp(Mac48Address a)
  {
    addressList.insert(a);
  }
  void Tim::DeleteNodeIp(Mac48Address a)
  {
    for(set<Mac48Address>::iterator i = addressList.begin(); i != addressList.end(); i++)
    {
      if(*i == a)
        addressList.erase(i);
    }
  }
  WifiInformationElementId
  Tim::ElementId () const
  {
    return IE_TIM;
  }

  uint8_t
  Tim::GetInformationFieldSize () const
  {
    return (4 + size * 6);
  }

  void
  Tim::SerializeInformationField (Buffer::Iterator start) const
  {
    uint8_t buf[4 + size * 6];
    memcpy(buf, &size, 4);
    int index = 0;
    for(set<Mac48Address>::const_iterator i = addressList.begin(); i != addressList.end(); i++)
    {
      memcpy(buf + 4 + index * 6, &*i, 6); 
      index++;
    }

    start.Write (buf, 4 + size * 6);
  }

  uint8_t
  Tim::DeserializeInformationField (Buffer::Iterator start,
                                   uint8_t length)
  {
    start.Read ((uint8_t *)&size, 4);
    uint8_t buf[size * 6];

    NS_ASSERT(length - 4 == size * 6);
    start.Read(buf, length - 4);
    
    addressList.clear();
    for(int i = 0; i < size; i++) {

      Mac48Address a;
      a.CopyFrom(&buf[i * 6]);
      addressList.insert(a);
    }
    return length;
  }
}

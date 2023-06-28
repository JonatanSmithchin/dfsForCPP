//
// Created by 刘骁 on 2023/4/10.
//

#ifndef DFSFORCPP_DATANODEINFO_H
#define DFSFORCPP_DATANODEINFO_H
#include "DatanodeID.h"
#include "ctime"

class datanodeInfo :public datanodeID{
private:
    long capacity;
    long used;
    long remained;
    time_t lastUpdated;
    int XceiverNum;
    string location;
    string version;
    enum State{
        OK,DECOMMISSIONED,INDECOMMISSION
    };
    State nodeState;
public:
    long getCapacity() const;

    void setCapacity(long capacity);

    long getUsed() const;

    void setUsed(long used);

    long getRemained() const;

    void setRemained(long remained);

    time_t getLastUpdated() const;

    void setLastUpdated(time_t lastUpdated);

    int getXceiverNum() const;

    void setXceiverNum(int xceiverNum);

    const string &getLocation() const;

    void setLocation(const string &location);

    const string &getVersion() const;

    void setVersion(const string &version);

    State getNodeState() const;

    void setNodeState(State nodeState);
};


#endif //DFSFORCPP_DATANODEINFO_H

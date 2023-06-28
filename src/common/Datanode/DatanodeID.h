//
// Created by 刘骁 on 2023/4/10.
//

#ifndef DFSFORCPP_DATANODEID_H
#define DFSFORCPP_DATANODEID_H
#include "string"
using std::string;
class datanodeID {
private:
    string ipAddr;
    string hostName;
    string ID;
    int TransPort;
    int infoPort;
    int RPCPort;
public:
    const string &getIpAddr() const;

    void setIpAddr(const string &ipAddr);

    const string &getHostName() const;

    void setHostName(const string &hostName);

    const string &getId() const;

    void setId(const string &id);

    int getTransPort() const;

    void setTransPort(int transPort);

    int getInfoPort() const;

    void setInfoPort(int infoPort);

    int getRpcPort() const;

    void setRpcPort(int rpcPort);
};


#endif //DFSFORCPP_DATANODEID_H

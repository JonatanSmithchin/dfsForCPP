//
// Created by 刘骁 on 2023/4/10.
//

#include "DatanodeID.h"


const string &datanodeID::getIpAddr() const {
    return ipAddr;
}

void datanodeID::setIpAddr(const string &ipAddr) {
    datanodeID::ipAddr = ipAddr;
}

const string &datanodeID::getHostName() const {
    return hostName;
}

void datanodeID::setHostName(const string &hostName) {
    datanodeID::hostName = hostName;
}

const string &datanodeID::getId() const {
    return ID;
}

void datanodeID::setId(const string &id) {
    ID = id;
}

int datanodeID::getTransPort() const {
    return TransPort;
}

void datanodeID::setTransPort(int transPort) {
    TransPort = transPort;
}

int datanodeID::getInfoPort() const {
    return infoPort;
}

void datanodeID::setInfoPort(int infoPort) {
    datanodeID::infoPort = infoPort;
}

int datanodeID::getRpcPort() const {
    return RPCPort;
}

void datanodeID::setRpcPort(int rpcPort) {
    RPCPort = rpcPort;
}

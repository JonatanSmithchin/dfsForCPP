//
// Created by 刘骁 on 2023/4/10.
//

#include "DatanodeInfo.h"

long datanodeInfo::getCapacity() const {
    return capacity;
}

void datanodeInfo::setCapacity(long capacity) {
    datanodeInfo::capacity = capacity;
}

long datanodeInfo::getUsed() const {
    return used;
}

void datanodeInfo::setUsed(long used) {
    datanodeInfo::used = used;
}

long datanodeInfo::getRemained() const {
    return remained;
}

void datanodeInfo::setRemained(long remained) {
    datanodeInfo::remained = remained;
}

time_t datanodeInfo::getLastUpdated() const {
    return lastUpdated;
}

void datanodeInfo::setLastUpdated(time_t lastUpdated) {
    datanodeInfo::lastUpdated = lastUpdated;
}

int datanodeInfo::getXceiverNum() const {
    return XceiverNum;
}

void datanodeInfo::setXceiverNum(int xceiverNum) {
    XceiverNum = xceiverNum;
}

const string &datanodeInfo::getLocation() const {
    return location;
}

void datanodeInfo::setLocation(const string &location) {
    datanodeInfo::location = location;
}

const string &datanodeInfo::getVersion() const {
    return version;
}

void datanodeInfo::setVersion(const string &version) {
    datanodeInfo::version = version;
}

datanodeInfo::State datanodeInfo::getNodeState() const {
    return nodeState;
}

void datanodeInfo::setNodeState(datanodeInfo::State nodeState) {
    datanodeInfo::nodeState = nodeState;
}

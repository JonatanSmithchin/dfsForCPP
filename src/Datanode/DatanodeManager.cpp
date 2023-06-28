//
// Created by 刘晓 on 2023/6/27.
//

#include "DatanodeManager.h"

void datanode::DatanodeManager::DecomissionMonitor::run() {

}

void datanode::DatanodeManager::DecomissionMonitor::check() {

}

void datanode::DatanodeManager::HeartBeatMonitor::run() {

}

bool datanode::DatanodeManager::HeartBeatMonitor::heartBeatCheck() {
    return false;
}

void datanode::DatanodeManager::addDatanode(DatanodeDescriptor* d) {
    datanodeMap.insert(pair<string,DatanodeDescriptor*>(d->getId(),d));
}

void datanode::DatanodeManager::removeDatanode(DatanodeDescriptor* d) {
    datanodeMap.erase((d->getId()));
}

DatanodeDescriptor *datanode::DatanodeManager::getDatanode(const string& id) {
    auto it = datanodeMap.find(id);
    return it->second;
}

void datanode::DatanodeManager::refreshDatanodes() {

}

std::vector<DatanodeNamenode::DatanodeCommand> datanode::DatanodeManager::handleHeartBeat() {
    return std::vector<DatanodeNamenode::DatanodeCommand>();
}

void datanode::DatanodeManager::updateHeartBeat() {

}

bool datanode::DatanodeManager::checkDecommisionState() {
    return false;
}

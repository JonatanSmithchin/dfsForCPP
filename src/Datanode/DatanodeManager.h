//
// Created by 刘晓 on 2023/6/27.
//

#ifndef NAMENODE_DATANODEMANAGER_H
#define NAMENODE_DATANODEMANAGER_H

#include<map>
#include<vector>
#include<string>
#include "DatanodeDescriptor.h"
#include "../../proto/DatanodeNamenode.pb.h"

namespace datanode{
    class DatanodeManager {
    private:
        std::map<std::string,DatanodeDescriptor*> datanodeMap;
        std::map<std::string,DatanodeDescriptor*> bck4DatanodeMap;
        class DecomissionMonitor{
        public:
            void run();
        private:
            void check();
        };
        class HeartBeatMonitor{
        public:
            void run();
        private:
            bool heartBeatCheck();
        };
    public:
        void addDatanode(DatanodeDescriptor* d);
        void removeDatanode(DatanodeDescriptor* d);
        DatanodeDescriptor* getDatanode(const string& id);
        void refreshDatanodes();
        std::vector<DatanodeNamenode::DatanodeCommand> handleHeartBeat();
        void updateHeartBeat();
        bool checkDecommisionState();
    };
}

#endif //NAMENODE_DATANODEMANAGER_H

#pragma once
#ifndef RPCSERVER_H
#define RPCSERVER_H
#include<iostream>
#include<string>
#include<grpcpp/grpcpp.h>
#include<string>
#include"ClientServiceImpl.h"
#include"DatanodeServiceImpl.h"
#include"../../proto/dfs.pb.h"
#include"../NameSystem/NameSystem.h"
#include"../Datanode/DatanodeManager.h"


class RPCServer {
private:
    namesystem::NameSystem* m_nameSystem;
    ClientNamenodeServiceImpl* m_client_service;
    DatanodeServiceImpl* m_datanode_service;
public:
    RPCServer(namesystem::NameSystem *nameSystem,ClientNamenodeServiceImpl* ClientNamenodeService,DatanodeServiceImpl* DatanodeService);
	void RunServer();
};
#endif
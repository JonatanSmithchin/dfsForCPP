cmake_minimum_required( VERSION 3.1 )

project( namenode )

find_package(gRPC CONFIG REQUIRED)

find_package( Protobuf REQUIRED )

aux_source_directory(src/Datanode DATANODE)

aux_source_directory(src/INode INODE)

aux_source_directory(src/common/Datanode COMMENDATANODE)

add_executable( namenode src/Server/RPCServer.cpp proto/DatanodeNamenode.grpc.pb.cc proto/DatanodeNamenode.pb.cc proto/ClientNamenode.grpc.pb.cc proto/ClientNamenode.pb.cc proto/dfs.grpc.pb.cc proto/dfs.pb.cc ${INODE} src/NameSystem/FsPermission.cpp src/NameSystem/NameSystem.cpp  src/Server/ClientServiceImpl.h src/Server/ClientServiceImpl.cpp src/Server/DatanodeServiceImpl.cpp src/Server/DatanodeServiceImpl.h ${DATANODE} ${COMMENDATANODE})

add_executable( client  src/Client/RPCClient.cpp proto/ClientNamenode.grpc.pb.cc proto/ClientNamenode.pb.cc proto/dfs.grpc.pb.cc proto/dfs.pb.cc)

add_executable( datanodeClient src/Client/DatanodeClient.cpp proto/DatanodeNamenode.grpc.pb.cc proto/DatanodeNamenode.pb.cc proto/dfs.grpc.pb.cc proto/dfs.pb.cc)

target_link_libraries( namenode PRIVATE gRPC::grpc++ gRPC::grpc++_reflection gRPC::gpr gRPC::grpc gRPC::grpc++ protobuf::libprotoc protobuf::libprotobuf protobuf::libprotobuf-lite )

target_link_libraries( client PRIVATE gRPC::grpc++ gRPC::grpc++_reflection gRPC::gpr gRPC::grpc gRPC::grpc++ protobuf::libprotoc protobuf::libprotobuf protobuf::libprotobuf-lite )

target_link_libraries( datanodeClient PRIVATE gRPC::grpc++ gRPC::grpc++_reflection gRPC::gpr gRPC::grpc gRPC::grpc++ protobuf::libprotoc protobuf::libprotobuf protobuf::libprotobuf-lite )

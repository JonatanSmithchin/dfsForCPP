//
// Created by 刘晓 on 2023/6/15.
//

#ifndef GRPC_EXAMPLE_NAMESYSTEM_H
#define GRPC_EXAMPLE_NAMESYSTEM_H

#include "../INode/INodeDir.h"
#include "../INode/INodeFile.h"
#include "../../proto/ClientNamenode.pb.h"

namespace namesystem {

    class NameSystem {
    private:
        INodeDir* m_root;
        INodeDir* working_dir;//当前工作目录
        static INodeFile* constructFile(const string& src);
        static vector<string>resolvePath(const string& path);
        INode* find(const string& path);
        INodeDir* findParent(const string& path);
        static string getFileName(const string& path);
    public:
        NameSystem(INodeDir *root);
        INode* addFile(const ClientNamenode::CreateRequest* request);
        bool deleteNode(const ClientNamenode::DeleteRequest* request);
        bool rename(const ClientNamenode::RenameRequest* request);
        INodeDir *getRoot() const;
        INode* addDir(const ClientNamenode::mkdirRequest* request);
        vector<INode*> list(const ClientNamenode::GetListingRequest* request);
    };

} // namesystem


#endif //GRPC_EXAMPLE_NAMESYSTEM_H

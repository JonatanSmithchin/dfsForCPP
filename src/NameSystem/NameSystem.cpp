//
// Created by 刘晓 on 2023/6/15.
//

#include "NameSystem.h"
#include "sstream"
using namespace std;
namespace namesystem {
    INodeFile* NameSystem::constructFile(const string &src) {
        auto* newFile =new INodeFile();
        newFile->setFullPathName(src);
        newFile->setName(getFileName(src));
        return newFile;
    }

   vector<string> NameSystem::resolvePath(const string &path) {
        stringstream ss(path);
        char c = '/';
        vector<string> results;
        if(path[0] == '/'){
            results.emplace_back("/");//如果路径是绝对路径
        }
        string s;
        while (getline(ss, s, c)) {
            if(s.empty()){
                continue;
            }
            results.push_back(s);
        }
        return results;
    }

    string NameSystem::getFileName(const string& path){
        unsigned long index = path.find_last_of('/');
        string fileName=path.substr(index,-1);
        return fileName;
    }

    INode* NameSystem::find(const string& path){
        vector<string> results = resolvePath(path);
        INode* node;

        if(results[0] == "/"){
            node = static_cast<INode *>(m_root);//从根目录开始查找
        }else{
            node = static_cast<INode *>(working_dir);//从当前目录开始查找
        }

        for (int i = 0; i < results.size()-1; i++) {
            if (node->isDir()) {
                auto *dir = dynamic_cast<INodeDir *>(node);
                INode *child = dir->getChild(results[i+1]);
                if(child == nullptr){
                    return nullptr;
                }
                node = child;
            } else {
                return nullptr;
            }
        }
        return node;
    }

    //TODO:修改函数，与find()一致
    INodeDir *NameSystem::findParent(const string& path) {
        //分割处理文件路径
        vector<string> results = resolvePath(path);

        //判断是否为Inode child
        INode* node;

        if(results[0] == "/"){
            node = static_cast<INode *>(m_root);//从根目录开始查找
        }else{
            node = static_cast<INode *>(working_dir);//从当前目录开始查找
        }

        for (int i = 0; i < results.size()-1; i++) {
            if (node->isDir()) {
                auto *dir = dynamic_cast<INodeDir *>(node);
                INode *child = dir->getChild(results[i+1]);
                if ( i+1 == results.size()-1 ) {//如果已经遍历到最后一级目录
                    printf("found");
                    return dynamic_cast<INodeDir *>(node);
                }
                if(child == nullptr){
                    cout<<"not found";
                    return nullptr;
                }
                node = child;
            } else {
                return nullptr;
            }
        }
        return dynamic_cast<INodeDir *>(node);
    }

    NameSystem::NameSystem(INodeDir* root):m_root(root) {
        root->setFullPathName("/");
        root->setName("/");
        auto* etc = new INodeDir();
        etc->setFullPathName("/etc");
        etc->setName("etc");
        root->addChild(etc);
    }

    INode *NameSystem::addFile(const ClientNamenode::CreateRequest* request) {

        INodeDir* p = findParent(request->src());
        if(p == nullptr){
            return nullptr;
        }
        INode* newFile = constructFile(request->src());
        p->addChild(newFile);
        return newFile;
    }

    bool NameSystem::rename(const ClientNamenode::RenameRequest* request) {
        INode* node = find(request->src());

        if (node == nullptr){
            return false;
        }

        if (dynamic_cast<INodeDir*>(node->getParent())->getChild(request->dst()) != nullptr){
            return false;
        }

        node->setName(request->dst());
        return true;
    }

    INodeDir *NameSystem::getRoot() const {
        return m_root;
    }

    INode *NameSystem::addDir(const ClientNamenode::mkdirRequest* request) {
        INodeDir* p = findParent(request->src());
        if(p == nullptr){
            return nullptr;
        }
        int index = request->src().find_last_of("/");
        string name = request->src().substr(index+1,-1);
        if(p->getChild(name) != nullptr){
            return nullptr;
        }else{
            INodeDir* newDir = new INodeDir();
            newDir->setFullPathName(request->src());
            newDir->setName(name);
            p->addChild(newDir);
            return newDir;
        }
    }

    vector<INode *> NameSystem::list(const ClientNamenode::GetListingRequest *request) {
        INode* node = find(request->src());
        if (node == nullptr || !node->isDir()){
            return {};
        }else{
            auto* dir = dynamic_cast<INodeDir*>(node);
            return dir->getChildren();
        }
    }

    bool NameSystem::deleteNode(const ClientNamenode::DeleteRequest *request) {
        INodeDir* p = findParent(request->src());
        if(p == nullptr){
            return false;
        }

        return p->removeChild(getFileName(request->src()));
    }


} // namesystem
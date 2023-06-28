//
// Created by 刘骁 on 2023/4/10.
//

#ifndef DFSFORCPP_INODEDIR_H
#define DFSFORCPP_INODEDIR_H

#include "INode.h"
#include "vector"

using std::vector;

class INodeDir : public INode {
private:
    vector<INode*> children;
public:
    bool addChild(INode* child);

    bool removeChild(const string &childName);

    bool replaceChild(INode* child);

    INode* getChild(const string &childName);

    vector<INode*> getChildren();

    bool clearChildren();

private:
    bool isFile() override;

    bool isDir() override;

    bool isRoot() override;

    bool isSymlink() override;
};


#endif //DFSFORCPP_INODEDIR_H

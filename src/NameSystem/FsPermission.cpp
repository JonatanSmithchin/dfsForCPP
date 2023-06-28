#include "FsPermission.h"

FsAction FsPermission::groupAction()
{
	return groupaction;
}

FsAction FsPermission::userAction()
{
	return useraction;
}

FsAction FsPermission::otherAction()
{
	return otheraction;
}

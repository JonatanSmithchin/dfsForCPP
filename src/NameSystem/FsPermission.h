#pragma once
#ifndef FSPERMISSION_H
#define FSPERMISSION_H
enum class FsAction {
	NONE,
	EXECUTE,
	WRITE,
	WRITE_EXECUTE,
	READ,
	READ_EXECUTE,
	READ_WRITE,
	ALL,
};

class FsPermission {
private:
	FsAction useraction;
	FsAction groupaction;
	FsAction otheraction;

public:
	FsAction userAction();
	FsAction groupAction();
	FsAction otherAction();
};
#endif // !FSPERMISSION_H

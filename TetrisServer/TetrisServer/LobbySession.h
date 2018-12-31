#pragma once
#include "Protocol.h"
#include <vector>

using namespace google;
class ClientSocket;


class RoomInfo
{
public:
	int	nRoomId = -1;
	std::string strRoomName;
};

class CLobbySession : public PacketHandler
{
public:
	enum
	{
		kShowRoomCnt = 6,
		kMaxRoomCnt = 600,
	};

public:
	CLobbySession();
	virtual ~CLobbySession();

	virtual void Handle(int nMessageType, protobuf::io::CodedInputStream* codedStream, ClientSocket* pSocket);

private:
	void __OnReqRoomList(protobuf::io::CodedInputStream* codedStream, ClientSocket* pSocket);
	void __OnReqCreateRoom(protobuf::io::CodedInputStream* codedStream, ClientSocket* pSocket);
	void __OnReqEnterRoom(protobuf::io::CodedInputStream* codedStream, ClientSocket* pSocket);
	

	unsigned int __GetRoomId();

private:
	unsigned int m_nRoomId;
	std::vector<RoomInfo> m_rooms;
};


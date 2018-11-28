#pragma once
#include "Protocol.h"
#include <vector>

using namespace google;
class ClientSocket;


class RoomInfo
{
public:
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
	void __OnReqRoomList(ServerMessage::MessageBase::ReqRoomList& onPacket, ClientSocket* pSocket);

private:
	std::vector<RoomInfo> m_rooms;
};


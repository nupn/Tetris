#pragma once
#include "Protocol.h"

using namespace google;
class ClientSocket;

class CLoginSession : public PacketHandler
{
public:
	CLoginSession();
	virtual ~CLoginSession();

	virtual void Handle(int nMessageType, protobuf::io::CodedInputStream* codedStream, ClientSocket* pSocket);


private:
	void __OnReqLogin(ServerMessage::MessageBase::ReqLogin& onPacket, ClientSocket* pSocket);
};


#pragma once

#include <google/protobuf/io/zero_copy_stream_impl_lite.h>
#include "ServerMessage.pb.h"
class ClientSocket;

using namespace google;

struct MessageHeader
{
	google::protobuf::uint32 size;
	ServerMessage::MessageType type;
};
const int MessageHeaderSize = sizeof(MessageHeader);

class PacketHandler
{
public:
	PacketHandler() = default;
	virtual ~PacketHandler() = default;
	virtual void Handle(int nMessageType, protobuf::io::CodedInputStream* codedStream, ClientSocket* pSocket)
	{
	}

	void SendChatMsg(std::string& chatMsg);
};

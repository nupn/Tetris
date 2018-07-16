#pragma once

#include <google/protobuf/io/zero_copy_stream_impl_lite.h>
#include "protocol\ServerMessage.pb.h"
class ClientSocket;

struct MessageHeader
{
	google::protobuf::uint32 size;
	ServerMessage::MessageType type;
};

class PacketHandler
{
public:
	virtual void Handle(const ServerMessage::Login& message, ClientSocket* pSocket)
	{
	}
	virtual void Handle(const ServerMessage::Chat& message, ClientSocket* pSocket)
	{
	}
	virtual void Handle(const ServerMessage::Move& message, ClientSocket* pSocket)
	{
	}
};

const int MessageHeaderSize = sizeof(MessageHeader);
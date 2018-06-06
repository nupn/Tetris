#pragma once



struct MessageHeader
{
	protobuf::uint32 size;
	ServerMessage::MessageType type;
};

class PacketHandler
{
public:
	void Handle(const ServerMessage::Login& message) const
	{
	}
	void Handle(const ServerMessage::Chat& message) const
	{
	}
	void Handle(const ServerMessage::Move& message) const
	{
	}
};

const int MessageHeaderSize = sizeof(MessageHeader);
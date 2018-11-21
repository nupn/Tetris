#pragma once

#include <google/protobuf/io/zero_copy_stream_impl_lite.h>
#include "ServerMessage.pb.h"
class ClientSocket;

using namespace google;

struct MessageHeader
{
	google::protobuf::uint32 size;
	int type;
};

class PacketHandler
{
public:
	virtual void Handle(int nMessageType, protobuf::io::CodedInputStream* codedStream, ClientSocket* pSocket)
	{
	}
};

const int MessageHeaderSize = sizeof(MessageHeader);
#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <process.h>
#include <vector>
#include <winsock2.h>
#include <thread>
#include <algorithm>
#include <google/protobuf/io/zero_copy_stream_impl_lite.h>
#include "protocol\ServerMessage.pb.h"

#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "NPCMemoryPool.lib")


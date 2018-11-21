set DST_DIR=C:\workspace\Tetris\protocol
set SRC_DIR=C:\workspace\Tetris\protocol
C:\workspace\protobuf-3.5.1\VC\Debug\protoc -I=%SRC_DIR% --cpp_out=%DST_DIR% %SRC_DIR%/ServerMessage.proto
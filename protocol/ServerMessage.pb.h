// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: ServerMessage.proto

#ifndef PROTOBUF_ServerMessage_2eproto__INCLUDED
#define PROTOBUF_ServerMessage_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 3005000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 3005001 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/generated_enum_reflection.h>
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)

namespace protobuf_ServerMessage_2eproto {
// Internal implementation detail -- do not use these members.
struct TableStruct {
  static const ::google::protobuf::internal::ParseTableField entries[];
  static const ::google::protobuf::internal::AuxillaryParseTableField aux[];
  static const ::google::protobuf::internal::ParseTable schema[3];
  static const ::google::protobuf::internal::FieldMetadata field_metadata[];
  static const ::google::protobuf::internal::SerializationTable serialization_table[];
  static const ::google::protobuf::uint32 offsets[];
};
void AddDescriptors();
void InitDefaultsMessageBase_ReqLoginImpl();
void InitDefaultsMessageBase_ReqLogin();
void InitDefaultsMessageBase_ResLoginImpl();
void InitDefaultsMessageBase_ResLogin();
void InitDefaultsMessageBaseImpl();
void InitDefaultsMessageBase();
inline void InitDefaults() {
  InitDefaultsMessageBase_ReqLogin();
  InitDefaultsMessageBase_ResLogin();
  InitDefaultsMessageBase();
}
}  // namespace protobuf_ServerMessage_2eproto
namespace ServerMessage {
class MessageBase;
class MessageBaseDefaultTypeInternal;
extern MessageBaseDefaultTypeInternal _MessageBase_default_instance_;
class MessageBase_ReqLogin;
class MessageBase_ReqLoginDefaultTypeInternal;
extern MessageBase_ReqLoginDefaultTypeInternal _MessageBase_ReqLogin_default_instance_;
class MessageBase_ResLogin;
class MessageBase_ResLoginDefaultTypeInternal;
extern MessageBase_ResLoginDefaultTypeInternal _MessageBase_ResLogin_default_instance_;
}  // namespace ServerMessage
namespace ServerMessage {

enum MessageType {
  kReqLogin = 0,
  kResLogin = 1,
  MessageType_INT_MIN_SENTINEL_DO_NOT_USE_ = ::google::protobuf::kint32min,
  MessageType_INT_MAX_SENTINEL_DO_NOT_USE_ = ::google::protobuf::kint32max
};
bool MessageType_IsValid(int value);
const MessageType MessageType_MIN = kReqLogin;
const MessageType MessageType_MAX = kResLogin;
const int MessageType_ARRAYSIZE = MessageType_MAX + 1;

const ::google::protobuf::EnumDescriptor* MessageType_descriptor();
inline const ::std::string& MessageType_Name(MessageType value) {
  return ::google::protobuf::internal::NameOfEnum(
    MessageType_descriptor(), value);
}
inline bool MessageType_Parse(
    const ::std::string& name, MessageType* value) {
  return ::google::protobuf::internal::ParseNamedEnum<MessageType>(
    MessageType_descriptor(), name, value);
}
// ===================================================================

class MessageBase_ReqLogin : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:ServerMessage.MessageBase.ReqLogin) */ {
 public:
  MessageBase_ReqLogin();
  virtual ~MessageBase_ReqLogin();

  MessageBase_ReqLogin(const MessageBase_ReqLogin& from);

  inline MessageBase_ReqLogin& operator=(const MessageBase_ReqLogin& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  MessageBase_ReqLogin(MessageBase_ReqLogin&& from) noexcept
    : MessageBase_ReqLogin() {
    *this = ::std::move(from);
  }

  inline MessageBase_ReqLogin& operator=(MessageBase_ReqLogin&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const ::google::protobuf::Descriptor* descriptor();
  static const MessageBase_ReqLogin& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const MessageBase_ReqLogin* internal_default_instance() {
    return reinterpret_cast<const MessageBase_ReqLogin*>(
               &_MessageBase_ReqLogin_default_instance_);
  }
  static PROTOBUF_CONSTEXPR int const kIndexInFileMessages =
    0;

  void Swap(MessageBase_ReqLogin* other);
  friend void swap(MessageBase_ReqLogin& a, MessageBase_ReqLogin& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline MessageBase_ReqLogin* New() const PROTOBUF_FINAL { return New(NULL); }

  MessageBase_ReqLogin* New(::google::protobuf::Arena* arena) const PROTOBUF_FINAL;
  void CopyFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void MergeFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void CopyFrom(const MessageBase_ReqLogin& from);
  void MergeFrom(const MessageBase_ReqLogin& from);
  void Clear() PROTOBUF_FINAL;
  bool IsInitialized() const PROTOBUF_FINAL;

  size_t ByteSizeLong() const PROTOBUF_FINAL;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) PROTOBUF_FINAL;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const PROTOBUF_FINAL;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* target) const PROTOBUF_FINAL;
  int GetCachedSize() const PROTOBUF_FINAL { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const PROTOBUF_FINAL;
  void InternalSwap(MessageBase_ReqLogin* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return NULL;
  }
  inline void* MaybeArenaPtr() const {
    return NULL;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const PROTOBUF_FINAL;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // string name = 2;
  void clear_name();
  static const int kNameFieldNumber = 2;
  const ::std::string& name() const;
  void set_name(const ::std::string& value);
  #if LANG_CXX11
  void set_name(::std::string&& value);
  #endif
  void set_name(const char* value);
  void set_name(const char* value, size_t size);
  ::std::string* mutable_name();
  ::std::string* release_name();
  void set_allocated_name(::std::string* name);

  // int32 id = 1;
  void clear_id();
  static const int kIdFieldNumber = 1;
  ::google::protobuf::int32 id() const;
  void set_id(::google::protobuf::int32 value);

  // @@protoc_insertion_point(class_scope:ServerMessage.MessageBase.ReqLogin)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::ArenaStringPtr name_;
  ::google::protobuf::int32 id_;
  mutable int _cached_size_;
  friend struct ::protobuf_ServerMessage_2eproto::TableStruct;
  friend void ::protobuf_ServerMessage_2eproto::InitDefaultsMessageBase_ReqLoginImpl();
};
// -------------------------------------------------------------------

class MessageBase_ResLogin : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:ServerMessage.MessageBase.ResLogin) */ {
 public:
  MessageBase_ResLogin();
  virtual ~MessageBase_ResLogin();

  MessageBase_ResLogin(const MessageBase_ResLogin& from);

  inline MessageBase_ResLogin& operator=(const MessageBase_ResLogin& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  MessageBase_ResLogin(MessageBase_ResLogin&& from) noexcept
    : MessageBase_ResLogin() {
    *this = ::std::move(from);
  }

  inline MessageBase_ResLogin& operator=(MessageBase_ResLogin&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const ::google::protobuf::Descriptor* descriptor();
  static const MessageBase_ResLogin& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const MessageBase_ResLogin* internal_default_instance() {
    return reinterpret_cast<const MessageBase_ResLogin*>(
               &_MessageBase_ResLogin_default_instance_);
  }
  static PROTOBUF_CONSTEXPR int const kIndexInFileMessages =
    1;

  void Swap(MessageBase_ResLogin* other);
  friend void swap(MessageBase_ResLogin& a, MessageBase_ResLogin& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline MessageBase_ResLogin* New() const PROTOBUF_FINAL { return New(NULL); }

  MessageBase_ResLogin* New(::google::protobuf::Arena* arena) const PROTOBUF_FINAL;
  void CopyFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void MergeFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void CopyFrom(const MessageBase_ResLogin& from);
  void MergeFrom(const MessageBase_ResLogin& from);
  void Clear() PROTOBUF_FINAL;
  bool IsInitialized() const PROTOBUF_FINAL;

  size_t ByteSizeLong() const PROTOBUF_FINAL;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) PROTOBUF_FINAL;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const PROTOBUF_FINAL;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* target) const PROTOBUF_FINAL;
  int GetCachedSize() const PROTOBUF_FINAL { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const PROTOBUF_FINAL;
  void InternalSwap(MessageBase_ResLogin* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return NULL;
  }
  inline void* MaybeArenaPtr() const {
    return NULL;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const PROTOBUF_FINAL;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // int32 res = 1;
  void clear_res();
  static const int kResFieldNumber = 1;
  ::google::protobuf::int32 res() const;
  void set_res(::google::protobuf::int32 value);

  // @@protoc_insertion_point(class_scope:ServerMessage.MessageBase.ResLogin)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::int32 res_;
  mutable int _cached_size_;
  friend struct ::protobuf_ServerMessage_2eproto::TableStruct;
  friend void ::protobuf_ServerMessage_2eproto::InitDefaultsMessageBase_ResLoginImpl();
};
// -------------------------------------------------------------------

class MessageBase : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:ServerMessage.MessageBase) */ {
 public:
  MessageBase();
  virtual ~MessageBase();

  MessageBase(const MessageBase& from);

  inline MessageBase& operator=(const MessageBase& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  MessageBase(MessageBase&& from) noexcept
    : MessageBase() {
    *this = ::std::move(from);
  }

  inline MessageBase& operator=(MessageBase&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const ::google::protobuf::Descriptor* descriptor();
  static const MessageBase& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const MessageBase* internal_default_instance() {
    return reinterpret_cast<const MessageBase*>(
               &_MessageBase_default_instance_);
  }
  static PROTOBUF_CONSTEXPR int const kIndexInFileMessages =
    2;

  void Swap(MessageBase* other);
  friend void swap(MessageBase& a, MessageBase& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline MessageBase* New() const PROTOBUF_FINAL { return New(NULL); }

  MessageBase* New(::google::protobuf::Arena* arena) const PROTOBUF_FINAL;
  void CopyFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void MergeFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void CopyFrom(const MessageBase& from);
  void MergeFrom(const MessageBase& from);
  void Clear() PROTOBUF_FINAL;
  bool IsInitialized() const PROTOBUF_FINAL;

  size_t ByteSizeLong() const PROTOBUF_FINAL;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) PROTOBUF_FINAL;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const PROTOBUF_FINAL;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* target) const PROTOBUF_FINAL;
  int GetCachedSize() const PROTOBUF_FINAL { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const PROTOBUF_FINAL;
  void InternalSwap(MessageBase* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return NULL;
  }
  inline void* MaybeArenaPtr() const {
    return NULL;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const PROTOBUF_FINAL;

  // nested types ----------------------------------------------------

  typedef MessageBase_ReqLogin ReqLogin;
  typedef MessageBase_ResLogin ResLogin;

  // accessors -------------------------------------------------------

  // @@protoc_insertion_point(class_scope:ServerMessage.MessageBase)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  mutable int _cached_size_;
  friend struct ::protobuf_ServerMessage_2eproto::TableStruct;
  friend void ::protobuf_ServerMessage_2eproto::InitDefaultsMessageBaseImpl();
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// MessageBase_ReqLogin

// int32 id = 1;
inline void MessageBase_ReqLogin::clear_id() {
  id_ = 0;
}
inline ::google::protobuf::int32 MessageBase_ReqLogin::id() const {
  // @@protoc_insertion_point(field_get:ServerMessage.MessageBase.ReqLogin.id)
  return id_;
}
inline void MessageBase_ReqLogin::set_id(::google::protobuf::int32 value) {
  
  id_ = value;
  // @@protoc_insertion_point(field_set:ServerMessage.MessageBase.ReqLogin.id)
}

// string name = 2;
inline void MessageBase_ReqLogin::clear_name() {
  name_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& MessageBase_ReqLogin::name() const {
  // @@protoc_insertion_point(field_get:ServerMessage.MessageBase.ReqLogin.name)
  return name_.GetNoArena();
}
inline void MessageBase_ReqLogin::set_name(const ::std::string& value) {
  
  name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:ServerMessage.MessageBase.ReqLogin.name)
}
#if LANG_CXX11
inline void MessageBase_ReqLogin::set_name(::std::string&& value) {
  
  name_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:ServerMessage.MessageBase.ReqLogin.name)
}
#endif
inline void MessageBase_ReqLogin::set_name(const char* value) {
  GOOGLE_DCHECK(value != NULL);
  
  name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:ServerMessage.MessageBase.ReqLogin.name)
}
inline void MessageBase_ReqLogin::set_name(const char* value, size_t size) {
  
  name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:ServerMessage.MessageBase.ReqLogin.name)
}
inline ::std::string* MessageBase_ReqLogin::mutable_name() {
  
  // @@protoc_insertion_point(field_mutable:ServerMessage.MessageBase.ReqLogin.name)
  return name_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* MessageBase_ReqLogin::release_name() {
  // @@protoc_insertion_point(field_release:ServerMessage.MessageBase.ReqLogin.name)
  
  return name_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void MessageBase_ReqLogin::set_allocated_name(::std::string* name) {
  if (name != NULL) {
    
  } else {
    
  }
  name_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), name);
  // @@protoc_insertion_point(field_set_allocated:ServerMessage.MessageBase.ReqLogin.name)
}

// -------------------------------------------------------------------

// MessageBase_ResLogin

// int32 res = 1;
inline void MessageBase_ResLogin::clear_res() {
  res_ = 0;
}
inline ::google::protobuf::int32 MessageBase_ResLogin::res() const {
  // @@protoc_insertion_point(field_get:ServerMessage.MessageBase.ResLogin.res)
  return res_;
}
inline void MessageBase_ResLogin::set_res(::google::protobuf::int32 value) {
  
  res_ = value;
  // @@protoc_insertion_point(field_set:ServerMessage.MessageBase.ResLogin.res)
}

// -------------------------------------------------------------------

// MessageBase

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__
// -------------------------------------------------------------------

// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)

}  // namespace ServerMessage

namespace google {
namespace protobuf {

template <> struct is_proto_enum< ::ServerMessage::MessageType> : ::google::protobuf::internal::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::ServerMessage::MessageType>() {
  return ::ServerMessage::MessageType_descriptor();
}

}  // namespace protobuf
}  // namespace google

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_ServerMessage_2eproto__INCLUDED

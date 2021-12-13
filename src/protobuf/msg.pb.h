// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: msg.proto

#ifndef PROTOBUF_INCLUDED_msg_2eproto
#define PROTOBUF_INCLUDED_msg_2eproto

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 3006001
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 3006001 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/inlined_string_field.h>
#include <google/protobuf/metadata.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)
#define PROTOBUF_INTERNAL_EXPORT_protobuf_msg_2eproto 

namespace protobuf_msg_2eproto {
// Internal implementation detail -- do not use these members.
struct TableStruct {
  static const ::google::protobuf::internal::ParseTableField entries[];
  static const ::google::protobuf::internal::AuxillaryParseTableField aux[];
  static const ::google::protobuf::internal::ParseTable schema[1];
  static const ::google::protobuf::internal::FieldMetadata field_metadata[];
  static const ::google::protobuf::internal::SerializationTable serialization_table[];
  static const ::google::protobuf::uint32 offsets[];
};
void AddDescriptors();
}  // namespace protobuf_msg_2eproto
namespace Proto {
class TestMsg;
class TestMsgDefaultTypeInternal;
extern TestMsgDefaultTypeInternal _TestMsg_default_instance_;
}  // namespace Proto
namespace google {
namespace protobuf {
template<> ::Proto::TestMsg* Arena::CreateMaybeMessage<::Proto::TestMsg>(Arena*);
}  // namespace protobuf
}  // namespace google
namespace Proto {

// ===================================================================

class TestMsg : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:Proto.TestMsg) */ {
 public:
  TestMsg();
  virtual ~TestMsg();

  TestMsg(const TestMsg& from);

  inline TestMsg& operator=(const TestMsg& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  TestMsg(TestMsg&& from) noexcept
    : TestMsg() {
    *this = ::std::move(from);
  }

  inline TestMsg& operator=(TestMsg&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const ::google::protobuf::Descriptor* descriptor();
  static const TestMsg& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const TestMsg* internal_default_instance() {
    return reinterpret_cast<const TestMsg*>(
               &_TestMsg_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  void Swap(TestMsg* other);
  friend void swap(TestMsg& a, TestMsg& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline TestMsg* New() const final {
    return CreateMaybeMessage<TestMsg>(NULL);
  }

  TestMsg* New(::google::protobuf::Arena* arena) const final {
    return CreateMaybeMessage<TestMsg>(arena);
  }
  void CopyFrom(const ::google::protobuf::Message& from) final;
  void MergeFrom(const ::google::protobuf::Message& from) final;
  void CopyFrom(const TestMsg& from);
  void MergeFrom(const TestMsg& from);
  void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) final;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const final;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* target) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(TestMsg* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return NULL;
  }
  inline void* MaybeArenaPtr() const {
    return NULL;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // string msg = 1;
  void clear_msg();
  static const int kMsgFieldNumber = 1;
  const ::std::string& msg() const;
  void set_msg(const ::std::string& value);
  #if LANG_CXX11
  void set_msg(::std::string&& value);
  #endif
  void set_msg(const char* value);
  void set_msg(const char* value, size_t size);
  ::std::string* mutable_msg();
  ::std::string* release_msg();
  void set_allocated_msg(::std::string* msg);

  // int32 index = 2;
  void clear_index();
  static const int kIndexFieldNumber = 2;
  ::google::protobuf::int32 index() const;
  void set_index(::google::protobuf::int32 value);

  // @@protoc_insertion_point(class_scope:Proto.TestMsg)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::ArenaStringPtr msg_;
  ::google::protobuf::int32 index_;
  mutable ::google::protobuf::internal::CachedSize _cached_size_;
  friend struct ::protobuf_msg_2eproto::TableStruct;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// TestMsg

// string msg = 1;
inline void TestMsg::clear_msg() {
  msg_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& TestMsg::msg() const {
  // @@protoc_insertion_point(field_get:Proto.TestMsg.msg)
  return msg_.GetNoArena();
}
inline void TestMsg::set_msg(const ::std::string& value) {
  
  msg_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:Proto.TestMsg.msg)
}
#if LANG_CXX11
inline void TestMsg::set_msg(::std::string&& value) {
  
  msg_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:Proto.TestMsg.msg)
}
#endif
inline void TestMsg::set_msg(const char* value) {
  GOOGLE_DCHECK(value != NULL);
  
  msg_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:Proto.TestMsg.msg)
}
inline void TestMsg::set_msg(const char* value, size_t size) {
  
  msg_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:Proto.TestMsg.msg)
}
inline ::std::string* TestMsg::mutable_msg() {
  
  // @@protoc_insertion_point(field_mutable:Proto.TestMsg.msg)
  return msg_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* TestMsg::release_msg() {
  // @@protoc_insertion_point(field_release:Proto.TestMsg.msg)
  
  return msg_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void TestMsg::set_allocated_msg(::std::string* msg) {
  if (msg != NULL) {
    
  } else {
    
  }
  msg_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), msg);
  // @@protoc_insertion_point(field_set_allocated:Proto.TestMsg.msg)
}

// int32 index = 2;
inline void TestMsg::clear_index() {
  index_ = 0;
}
inline ::google::protobuf::int32 TestMsg::index() const {
  // @@protoc_insertion_point(field_get:Proto.TestMsg.index)
  return index_;
}
inline void TestMsg::set_index(::google::protobuf::int32 value) {
  
  index_ = value;
  // @@protoc_insertion_point(field_set:Proto.TestMsg.index)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)

}  // namespace Proto

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_INCLUDED_msg_2eproto

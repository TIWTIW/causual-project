// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: test_ToServer.proto

#ifndef PROTOBUF_test_5fToServer_2eproto__INCLUDED
#define PROTOBUF_test_5fToServer_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 3003000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 3003002 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
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
namespace test {
class ToServer;
class ToServerDefaultTypeInternal;
extern ToServerDefaultTypeInternal _ToServer_default_instance_;
}  // namespace test

namespace test {

namespace protobuf_test_5fToServer_2eproto {
// Internal implementation detail -- do not call these.
struct TableStruct {
  static const ::google::protobuf::internal::ParseTableField entries[];
  static const ::google::protobuf::internal::AuxillaryParseTableField aux[];
  static const ::google::protobuf::internal::ParseTable schema[];
  static const ::google::protobuf::uint32 offsets[];
  static void InitDefaultsImpl();
  static void Shutdown();
};
void AddDescriptors();
void InitDefaults();
}  // namespace protobuf_test_5fToServer_2eproto

enum ToServer_Type {
  ToServer_Type_NeedImage = 0,
  ToServer_Type_NoNeedImage = 1
};
bool ToServer_Type_IsValid(int value);
const ToServer_Type ToServer_Type_Type_MIN = ToServer_Type_NeedImage;
const ToServer_Type ToServer_Type_Type_MAX = ToServer_Type_NoNeedImage;
const int ToServer_Type_Type_ARRAYSIZE = ToServer_Type_Type_MAX + 1;

const ::google::protobuf::EnumDescriptor* ToServer_Type_descriptor();
inline const ::std::string& ToServer_Type_Name(ToServer_Type value) {
  return ::google::protobuf::internal::NameOfEnum(
    ToServer_Type_descriptor(), value);
}
inline bool ToServer_Type_Parse(
    const ::std::string& name, ToServer_Type* value) {
  return ::google::protobuf::internal::ParseNamedEnum<ToServer_Type>(
    ToServer_Type_descriptor(), name, value);
}
enum ToServer_Mode {
  ToServer_Mode_ControlMode = 0,
  ToServer_Mode_SelfMode = 1
};
bool ToServer_Mode_IsValid(int value);
const ToServer_Mode ToServer_Mode_Mode_MIN = ToServer_Mode_ControlMode;
const ToServer_Mode ToServer_Mode_Mode_MAX = ToServer_Mode_SelfMode;
const int ToServer_Mode_Mode_ARRAYSIZE = ToServer_Mode_Mode_MAX + 1;

const ::google::protobuf::EnumDescriptor* ToServer_Mode_descriptor();
inline const ::std::string& ToServer_Mode_Name(ToServer_Mode value) {
  return ::google::protobuf::internal::NameOfEnum(
    ToServer_Mode_descriptor(), value);
}
inline bool ToServer_Mode_Parse(
    const ::std::string& name, ToServer_Mode* value) {
  return ::google::protobuf::internal::ParseNamedEnum<ToServer_Mode>(
    ToServer_Mode_descriptor(), name, value);
}
// ===================================================================

class ToServer : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:test.ToServer) */ {
 public:
  ToServer();
  virtual ~ToServer();

  ToServer(const ToServer& from);

  inline ToServer& operator=(const ToServer& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _internal_metadata_.unknown_fields();
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return _internal_metadata_.mutable_unknown_fields();
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const ToServer& default_instance();

  static inline const ToServer* internal_default_instance() {
    return reinterpret_cast<const ToServer*>(
               &_ToServer_default_instance_);
  }
  static PROTOBUF_CONSTEXPR int const kIndexInFileMessages =
    0;

  void Swap(ToServer* other);

  // implements Message ----------------------------------------------

  inline ToServer* New() const PROTOBUF_FINAL { return New(NULL); }

  ToServer* New(::google::protobuf::Arena* arena) const PROTOBUF_FINAL;
  void CopyFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void MergeFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void CopyFrom(const ToServer& from);
  void MergeFrom(const ToServer& from);
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
  void InternalSwap(ToServer* other);
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

  typedef ToServer_Type Type;
  static const Type NeedImage =
    ToServer_Type_NeedImage;
  static const Type NoNeedImage =
    ToServer_Type_NoNeedImage;
  static inline bool Type_IsValid(int value) {
    return ToServer_Type_IsValid(value);
  }
  static const Type Type_MIN =
    ToServer_Type_Type_MIN;
  static const Type Type_MAX =
    ToServer_Type_Type_MAX;
  static const int Type_ARRAYSIZE =
    ToServer_Type_Type_ARRAYSIZE;
  static inline const ::google::protobuf::EnumDescriptor*
  Type_descriptor() {
    return ToServer_Type_descriptor();
  }
  static inline const ::std::string& Type_Name(Type value) {
    return ToServer_Type_Name(value);
  }
  static inline bool Type_Parse(const ::std::string& name,
      Type* value) {
    return ToServer_Type_Parse(name, value);
  }

  typedef ToServer_Mode Mode;
  static const Mode ControlMode =
    ToServer_Mode_ControlMode;
  static const Mode SelfMode =
    ToServer_Mode_SelfMode;
  static inline bool Mode_IsValid(int value) {
    return ToServer_Mode_IsValid(value);
  }
  static const Mode Mode_MIN =
    ToServer_Mode_Mode_MIN;
  static const Mode Mode_MAX =
    ToServer_Mode_Mode_MAX;
  static const int Mode_ARRAYSIZE =
    ToServer_Mode_Mode_ARRAYSIZE;
  static inline const ::google::protobuf::EnumDescriptor*
  Mode_descriptor() {
    return ToServer_Mode_descriptor();
  }
  static inline const ::std::string& Mode_Name(Mode value) {
    return ToServer_Mode_Name(value);
  }
  static inline bool Mode_Parse(const ::std::string& name,
      Mode* value) {
    return ToServer_Mode_Parse(name, value);
  }

  // accessors -------------------------------------------------------

  // optional .test.ToServer.Type DataType = 1;
  bool has_datatype() const;
  void clear_datatype();
  static const int kDataTypeFieldNumber = 1;
  ::test::ToServer_Type datatype() const;
  void set_datatype(::test::ToServer_Type value);

  // optional .test.ToServer.Mode ModeInfo = 2;
  bool has_modeinfo() const;
  void clear_modeinfo();
  static const int kModeInfoFieldNumber = 2;
  ::test::ToServer_Mode modeinfo() const;
  void set_modeinfo(::test::ToServer_Mode value);

  // optional bool left = 3;
  bool has_left() const;
  void clear_left();
  static const int kLeftFieldNumber = 3;
  bool left() const;
  void set_left(bool value);

  // optional bool right = 4;
  bool has_right() const;
  void clear_right();
  static const int kRightFieldNumber = 4;
  bool right() const;
  void set_right(bool value);

  // optional bool forward = 5;
  bool has_forward() const;
  void clear_forward();
  static const int kForwardFieldNumber = 5;
  bool forward() const;
  void set_forward(bool value);

  // optional bool backward = 6;
  bool has_backward() const;
  void clear_backward();
  static const int kBackwardFieldNumber = 6;
  bool backward() const;
  void set_backward(bool value);

  // @@protoc_insertion_point(class_scope:test.ToServer)
 private:
  void set_has_datatype();
  void clear_has_datatype();
  void set_has_modeinfo();
  void clear_has_modeinfo();
  void set_has_left();
  void clear_has_left();
  void set_has_right();
  void clear_has_right();
  void set_has_forward();
  void clear_has_forward();
  void set_has_backward();
  void clear_has_backward();

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::HasBits<1> _has_bits_;
  mutable int _cached_size_;
  int datatype_;
  int modeinfo_;
  bool left_;
  bool right_;
  bool forward_;
  bool backward_;
  friend struct protobuf_test_5fToServer_2eproto::TableStruct;
};
// ===================================================================


// ===================================================================

#if !PROTOBUF_INLINE_NOT_IN_HEADERS
// ToServer

// optional .test.ToServer.Type DataType = 1;
inline bool ToServer::has_datatype() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void ToServer::set_has_datatype() {
  _has_bits_[0] |= 0x00000001u;
}
inline void ToServer::clear_has_datatype() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void ToServer::clear_datatype() {
  datatype_ = 0;
  clear_has_datatype();
}
inline ::test::ToServer_Type ToServer::datatype() const {
  // @@protoc_insertion_point(field_get:test.ToServer.DataType)
  return static_cast< ::test::ToServer_Type >(datatype_);
}
inline void ToServer::set_datatype(::test::ToServer_Type value) {
  assert(::test::ToServer_Type_IsValid(value));
  set_has_datatype();
  datatype_ = value;
  // @@protoc_insertion_point(field_set:test.ToServer.DataType)
}

// optional .test.ToServer.Mode ModeInfo = 2;
inline bool ToServer::has_modeinfo() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void ToServer::set_has_modeinfo() {
  _has_bits_[0] |= 0x00000002u;
}
inline void ToServer::clear_has_modeinfo() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void ToServer::clear_modeinfo() {
  modeinfo_ = 0;
  clear_has_modeinfo();
}
inline ::test::ToServer_Mode ToServer::modeinfo() const {
  // @@protoc_insertion_point(field_get:test.ToServer.ModeInfo)
  return static_cast< ::test::ToServer_Mode >(modeinfo_);
}
inline void ToServer::set_modeinfo(::test::ToServer_Mode value) {
  assert(::test::ToServer_Mode_IsValid(value));
  set_has_modeinfo();
  modeinfo_ = value;
  // @@protoc_insertion_point(field_set:test.ToServer.ModeInfo)
}

// optional bool left = 3;
inline bool ToServer::has_left() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void ToServer::set_has_left() {
  _has_bits_[0] |= 0x00000004u;
}
inline void ToServer::clear_has_left() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void ToServer::clear_left() {
  left_ = false;
  clear_has_left();
}
inline bool ToServer::left() const {
  // @@protoc_insertion_point(field_get:test.ToServer.left)
  return left_;
}
inline void ToServer::set_left(bool value) {
  set_has_left();
  left_ = value;
  // @@protoc_insertion_point(field_set:test.ToServer.left)
}

// optional bool right = 4;
inline bool ToServer::has_right() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void ToServer::set_has_right() {
  _has_bits_[0] |= 0x00000008u;
}
inline void ToServer::clear_has_right() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void ToServer::clear_right() {
  right_ = false;
  clear_has_right();
}
inline bool ToServer::right() const {
  // @@protoc_insertion_point(field_get:test.ToServer.right)
  return right_;
}
inline void ToServer::set_right(bool value) {
  set_has_right();
  right_ = value;
  // @@protoc_insertion_point(field_set:test.ToServer.right)
}

// optional bool forward = 5;
inline bool ToServer::has_forward() const {
  return (_has_bits_[0] & 0x00000010u) != 0;
}
inline void ToServer::set_has_forward() {
  _has_bits_[0] |= 0x00000010u;
}
inline void ToServer::clear_has_forward() {
  _has_bits_[0] &= ~0x00000010u;
}
inline void ToServer::clear_forward() {
  forward_ = false;
  clear_has_forward();
}
inline bool ToServer::forward() const {
  // @@protoc_insertion_point(field_get:test.ToServer.forward)
  return forward_;
}
inline void ToServer::set_forward(bool value) {
  set_has_forward();
  forward_ = value;
  // @@protoc_insertion_point(field_set:test.ToServer.forward)
}

// optional bool backward = 6;
inline bool ToServer::has_backward() const {
  return (_has_bits_[0] & 0x00000020u) != 0;
}
inline void ToServer::set_has_backward() {
  _has_bits_[0] |= 0x00000020u;
}
inline void ToServer::clear_has_backward() {
  _has_bits_[0] &= ~0x00000020u;
}
inline void ToServer::clear_backward() {
  backward_ = false;
  clear_has_backward();
}
inline bool ToServer::backward() const {
  // @@protoc_insertion_point(field_get:test.ToServer.backward)
  return backward_;
}
inline void ToServer::set_backward(bool value) {
  set_has_backward();
  backward_ = value;
  // @@protoc_insertion_point(field_set:test.ToServer.backward)
}

#endif  // !PROTOBUF_INLINE_NOT_IN_HEADERS

// @@protoc_insertion_point(namespace_scope)


}  // namespace test

#ifndef SWIG
namespace google {
namespace protobuf {

template <> struct is_proto_enum< ::test::ToServer_Type> : ::google::protobuf::internal::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::test::ToServer_Type>() {
  return ::test::ToServer_Type_descriptor();
}
template <> struct is_proto_enum< ::test::ToServer_Mode> : ::google::protobuf::internal::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::test::ToServer_Mode>() {
  return ::test::ToServer_Mode_descriptor();
}

}  // namespace protobuf
}  // namespace google
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_test_5fToServer_2eproto__INCLUDED

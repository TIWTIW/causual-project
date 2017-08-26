// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: test_ToClient.proto

#ifndef PROTOBUF_test_5fToClient_2eproto__INCLUDED
#define PROTOBUF_test_5fToClient_2eproto__INCLUDED

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
class ToClient;
class ToClientDefaultTypeInternal;
extern ToClientDefaultTypeInternal _ToClient_default_instance_;
}  // namespace test

namespace test {

namespace protobuf_test_5fToClient_2eproto {
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
}  // namespace protobuf_test_5fToClient_2eproto

enum ToClient_Type {
  ToClient_Type_NoImage = 0,
  ToClient_Type_HasImage = 1
};
bool ToClient_Type_IsValid(int value);
const ToClient_Type ToClient_Type_Type_MIN = ToClient_Type_NoImage;
const ToClient_Type ToClient_Type_Type_MAX = ToClient_Type_HasImage;
const int ToClient_Type_Type_ARRAYSIZE = ToClient_Type_Type_MAX + 1;

const ::google::protobuf::EnumDescriptor* ToClient_Type_descriptor();
inline const ::std::string& ToClient_Type_Name(ToClient_Type value) {
  return ::google::protobuf::internal::NameOfEnum(
    ToClient_Type_descriptor(), value);
}
inline bool ToClient_Type_Parse(
    const ::std::string& name, ToClient_Type* value) {
  return ::google::protobuf::internal::ParseNamedEnum<ToClient_Type>(
    ToClient_Type_descriptor(), name, value);
}
// ===================================================================

class ToClient : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:test.ToClient) */ {
 public:
  ToClient();
  virtual ~ToClient();

  ToClient(const ToClient& from);

  inline ToClient& operator=(const ToClient& from) {
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
  static const ToClient& default_instance();

  static inline const ToClient* internal_default_instance() {
    return reinterpret_cast<const ToClient*>(
               &_ToClient_default_instance_);
  }
  static PROTOBUF_CONSTEXPR int const kIndexInFileMessages =
    0;

  void Swap(ToClient* other);

  // implements Message ----------------------------------------------

  inline ToClient* New() const PROTOBUF_FINAL { return New(NULL); }

  ToClient* New(::google::protobuf::Arena* arena) const PROTOBUF_FINAL;
  void CopyFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void MergeFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void CopyFrom(const ToClient& from);
  void MergeFrom(const ToClient& from);
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
  void InternalSwap(ToClient* other);
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

  typedef ToClient_Type Type;
  static const Type NoImage =
    ToClient_Type_NoImage;
  static const Type HasImage =
    ToClient_Type_HasImage;
  static inline bool Type_IsValid(int value) {
    return ToClient_Type_IsValid(value);
  }
  static const Type Type_MIN =
    ToClient_Type_Type_MIN;
  static const Type Type_MAX =
    ToClient_Type_Type_MAX;
  static const int Type_ARRAYSIZE =
    ToClient_Type_Type_ARRAYSIZE;
  static inline const ::google::protobuf::EnumDescriptor*
  Type_descriptor() {
    return ToClient_Type_descriptor();
  }
  static inline const ::std::string& Type_Name(Type value) {
    return ToClient_Type_Name(value);
  }
  static inline bool Type_Parse(const ::std::string& name,
      Type* value) {
    return ToClient_Type_Parse(name, value);
  }

  // accessors -------------------------------------------------------

  // required .test.ToClient.Type DataType = 1;
  bool has_datatype() const;
  void clear_datatype();
  static const int kDataTypeFieldNumber = 1;
  ::test::ToClient_Type datatype() const;
  void set_datatype(::test::ToClient_Type value);

  // required uint32 Sen_data = 3;
  bool has_sen_data() const;
  void clear_sen_data();
  static const int kSenDataFieldNumber = 3;
  ::google::protobuf::uint32 sen_data() const;
  void set_sen_data(::google::protobuf::uint32 value);

  // required float pose_x = 4;
  bool has_pose_x() const;
  void clear_pose_x();
  static const int kPoseXFieldNumber = 4;
  float pose_x() const;
  void set_pose_x(float value);

  // required float pose_y = 5;
  bool has_pose_y() const;
  void clear_pose_y();
  static const int kPoseYFieldNumber = 5;
  float pose_y() const;
  void set_pose_y(float value);

  // required float pose_theta = 6;
  bool has_pose_theta() const;
  void clear_pose_theta();
  static const int kPoseThetaFieldNumber = 6;
  float pose_theta() const;
  void set_pose_theta(float value);

  // optional uint32 Image_Length = 7;
  bool has_image_length() const;
  void clear_image_length();
  static const int kImageLengthFieldNumber = 7;
  ::google::protobuf::uint32 image_length() const;
  void set_image_length(::google::protobuf::uint32 value);

  // @@protoc_insertion_point(class_scope:test.ToClient)
 private:
  void set_has_datatype();
  void clear_has_datatype();
  void set_has_sen_data();
  void clear_has_sen_data();
  void set_has_pose_x();
  void clear_has_pose_x();
  void set_has_pose_y();
  void clear_has_pose_y();
  void set_has_pose_theta();
  void clear_has_pose_theta();
  void set_has_image_length();
  void clear_has_image_length();

  // helper for ByteSizeLong()
  size_t RequiredFieldsByteSizeFallback() const;

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::HasBits<1> _has_bits_;
  mutable int _cached_size_;
  int datatype_;
  ::google::protobuf::uint32 sen_data_;
  float pose_x_;
  float pose_y_;
  float pose_theta_;
  ::google::protobuf::uint32 image_length_;
  friend struct protobuf_test_5fToClient_2eproto::TableStruct;
};
// ===================================================================


// ===================================================================

#if !PROTOBUF_INLINE_NOT_IN_HEADERS
// ToClient

// required .test.ToClient.Type DataType = 1;
inline bool ToClient::has_datatype() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void ToClient::set_has_datatype() {
  _has_bits_[0] |= 0x00000001u;
}
inline void ToClient::clear_has_datatype() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void ToClient::clear_datatype() {
  datatype_ = 0;
  clear_has_datatype();
}
inline ::test::ToClient_Type ToClient::datatype() const {
  // @@protoc_insertion_point(field_get:test.ToClient.DataType)
  return static_cast< ::test::ToClient_Type >(datatype_);
}
inline void ToClient::set_datatype(::test::ToClient_Type value) {
  assert(::test::ToClient_Type_IsValid(value));
  set_has_datatype();
  datatype_ = value;
  // @@protoc_insertion_point(field_set:test.ToClient.DataType)
}

// required uint32 Sen_data = 3;
inline bool ToClient::has_sen_data() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void ToClient::set_has_sen_data() {
  _has_bits_[0] |= 0x00000002u;
}
inline void ToClient::clear_has_sen_data() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void ToClient::clear_sen_data() {
  sen_data_ = 0u;
  clear_has_sen_data();
}
inline ::google::protobuf::uint32 ToClient::sen_data() const {
  // @@protoc_insertion_point(field_get:test.ToClient.Sen_data)
  return sen_data_;
}
inline void ToClient::set_sen_data(::google::protobuf::uint32 value) {
  set_has_sen_data();
  sen_data_ = value;
  // @@protoc_insertion_point(field_set:test.ToClient.Sen_data)
}

// required float pose_x = 4;
inline bool ToClient::has_pose_x() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void ToClient::set_has_pose_x() {
  _has_bits_[0] |= 0x00000004u;
}
inline void ToClient::clear_has_pose_x() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void ToClient::clear_pose_x() {
  pose_x_ = 0;
  clear_has_pose_x();
}
inline float ToClient::pose_x() const {
  // @@protoc_insertion_point(field_get:test.ToClient.pose_x)
  return pose_x_;
}
inline void ToClient::set_pose_x(float value) {
  set_has_pose_x();
  pose_x_ = value;
  // @@protoc_insertion_point(field_set:test.ToClient.pose_x)
}

// required float pose_y = 5;
inline bool ToClient::has_pose_y() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void ToClient::set_has_pose_y() {
  _has_bits_[0] |= 0x00000008u;
}
inline void ToClient::clear_has_pose_y() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void ToClient::clear_pose_y() {
  pose_y_ = 0;
  clear_has_pose_y();
}
inline float ToClient::pose_y() const {
  // @@protoc_insertion_point(field_get:test.ToClient.pose_y)
  return pose_y_;
}
inline void ToClient::set_pose_y(float value) {
  set_has_pose_y();
  pose_y_ = value;
  // @@protoc_insertion_point(field_set:test.ToClient.pose_y)
}

// required float pose_theta = 6;
inline bool ToClient::has_pose_theta() const {
  return (_has_bits_[0] & 0x00000010u) != 0;
}
inline void ToClient::set_has_pose_theta() {
  _has_bits_[0] |= 0x00000010u;
}
inline void ToClient::clear_has_pose_theta() {
  _has_bits_[0] &= ~0x00000010u;
}
inline void ToClient::clear_pose_theta() {
  pose_theta_ = 0;
  clear_has_pose_theta();
}
inline float ToClient::pose_theta() const {
  // @@protoc_insertion_point(field_get:test.ToClient.pose_theta)
  return pose_theta_;
}
inline void ToClient::set_pose_theta(float value) {
  set_has_pose_theta();
  pose_theta_ = value;
  // @@protoc_insertion_point(field_set:test.ToClient.pose_theta)
}

// optional uint32 Image_Length = 7;
inline bool ToClient::has_image_length() const {
  return (_has_bits_[0] & 0x00000020u) != 0;
}
inline void ToClient::set_has_image_length() {
  _has_bits_[0] |= 0x00000020u;
}
inline void ToClient::clear_has_image_length() {
  _has_bits_[0] &= ~0x00000020u;
}
inline void ToClient::clear_image_length() {
  image_length_ = 0u;
  clear_has_image_length();
}
inline ::google::protobuf::uint32 ToClient::image_length() const {
  // @@protoc_insertion_point(field_get:test.ToClient.Image_Length)
  return image_length_;
}
inline void ToClient::set_image_length(::google::protobuf::uint32 value) {
  set_has_image_length();
  image_length_ = value;
  // @@protoc_insertion_point(field_set:test.ToClient.Image_Length)
}

#endif  // !PROTOBUF_INLINE_NOT_IN_HEADERS

// @@protoc_insertion_point(namespace_scope)


}  // namespace test

#ifndef SWIG
namespace google {
namespace protobuf {

template <> struct is_proto_enum< ::test::ToClient_Type> : ::google::protobuf::internal::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::test::ToClient_Type>() {
  return ::test::ToClient_Type_descriptor();
}

}  // namespace protobuf
}  // namespace google
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_test_5fToClient_2eproto__INCLUDED

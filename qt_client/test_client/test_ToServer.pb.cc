// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: test_ToServer.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "test_ToServer.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/port.h>
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace test {
class ToServerDefaultTypeInternal : public ::google::protobuf::internal::ExplicitlyConstructed<ToServer> {
} _ToServer_default_instance_;

namespace protobuf_test_5fToServer_2eproto {


namespace {

::google::protobuf::Metadata file_level_metadata[1];
const ::google::protobuf::EnumDescriptor* file_level_enum_descriptors[2];

}  // namespace

PROTOBUF_CONSTEXPR_VAR ::google::protobuf::internal::ParseTableField
    const TableStruct::entries[] = {
  {0, 0, 0, ::google::protobuf::internal::kInvalidMask, 0, 0},
};

PROTOBUF_CONSTEXPR_VAR ::google::protobuf::internal::AuxillaryParseTableField
    const TableStruct::aux[] = {
  ::google::protobuf::internal::AuxillaryParseTableField(),
};
PROTOBUF_CONSTEXPR_VAR ::google::protobuf::internal::ParseTable const
    TableStruct::schema[] = {
  { NULL, NULL, 0, -1, -1, false },
};

const ::google::protobuf::uint32 TableStruct::offsets[] = {
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ToServer, _has_bits_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ToServer, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ToServer, datatype_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ToServer, modeinfo_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ToServer, left_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ToServer, right_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ToServer, forward_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ToServer, backward_),
  0,
  1,
  2,
  3,
  4,
  5,
};

static const ::google::protobuf::internal::MigrationSchema schemas[] = {
  { 0, 11, sizeof(ToServer)},
};

static ::google::protobuf::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::google::protobuf::Message*>(&_ToServer_default_instance_),
};

namespace {

void protobuf_AssignDescriptors() {
  AddDescriptors();
  ::google::protobuf::MessageFactory* factory = NULL;
  AssignDescriptors(
      "test_ToServer.proto", schemas, file_default_instances, TableStruct::offsets, factory,
      file_level_metadata, file_level_enum_descriptors, NULL);
}

void protobuf_AssignDescriptorsOnce() {
  static GOOGLE_PROTOBUF_DECLARE_ONCE(once);
  ::google::protobuf::GoogleOnceInit(&once, &protobuf_AssignDescriptors);
}

void protobuf_RegisterTypes(const ::std::string&) GOOGLE_ATTRIBUTE_COLD;
void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::internal::RegisterAllTypes(file_level_metadata, 1);
}

}  // namespace

void TableStruct::Shutdown() {
  _ToServer_default_instance_.Shutdown();
  delete file_level_metadata[0].reflection;
}

void TableStruct::InitDefaultsImpl() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::internal::InitProtobufDefaults();
  _ToServer_default_instance_.DefaultConstruct();
}

void InitDefaults() {
  static GOOGLE_PROTOBUF_DECLARE_ONCE(once);
  ::google::protobuf::GoogleOnceInit(&once, &TableStruct::InitDefaultsImpl);
}
namespace {
void AddDescriptorsImpl() {
  InitDefaults();
  static const char descriptor[] = {
      "\n\023test_ToServer.proto\022\004test\"\347\001\n\010ToServer"
      "\022%\n\010DataType\030\001 \002(\0162\023.test.ToServer.Type\022"
      "%\n\010ModeInfo\030\002 \002(\0162\023.test.ToServer.Mode\022\014"
      "\n\004left\030\003 \001(\010\022\r\n\005right\030\004 \001(\010\022\017\n\007forward\030\005"
      " \001(\010\022\020\n\010backward\030\006 \001(\010\"&\n\004Type\022\r\n\tNeedIm"
      "age\020\000\022\017\n\013NoNeedImage\020\001\"%\n\004Mode\022\017\n\013Contro"
      "lMode\020\000\022\014\n\010SelfMode\020\001"
  };
  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
      descriptor, 261);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "test_ToServer.proto", &protobuf_RegisterTypes);
  ::google::protobuf::internal::OnShutdown(&TableStruct::Shutdown);
}
} // anonymous namespace

void AddDescriptors() {
  static GOOGLE_PROTOBUF_DECLARE_ONCE(once);
  ::google::protobuf::GoogleOnceInit(&once, &AddDescriptorsImpl);
}
// Force AddDescriptors() to be called at dynamic initialization time.
struct StaticDescriptorInitializer {
  StaticDescriptorInitializer() {
    AddDescriptors();
  }
} static_descriptor_initializer;

}  // namespace protobuf_test_5fToServer_2eproto

const ::google::protobuf::EnumDescriptor* ToServer_Type_descriptor() {
  protobuf_test_5fToServer_2eproto::protobuf_AssignDescriptorsOnce();
  return protobuf_test_5fToServer_2eproto::file_level_enum_descriptors[0];
}
bool ToServer_Type_IsValid(int value) {
  switch (value) {
    case 0:
    case 1:
      return true;
    default:
      return false;
  }
}

#if !defined(_MSC_VER) || _MSC_VER >= 1900
const ToServer_Type ToServer::NeedImage;
const ToServer_Type ToServer::NoNeedImage;
const ToServer_Type ToServer::Type_MIN;
const ToServer_Type ToServer::Type_MAX;
const int ToServer::Type_ARRAYSIZE;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900
const ::google::protobuf::EnumDescriptor* ToServer_Mode_descriptor() {
  protobuf_test_5fToServer_2eproto::protobuf_AssignDescriptorsOnce();
  return protobuf_test_5fToServer_2eproto::file_level_enum_descriptors[1];
}
bool ToServer_Mode_IsValid(int value) {
  switch (value) {
    case 0:
    case 1:
      return true;
    default:
      return false;
  }
}

#if !defined(_MSC_VER) || _MSC_VER >= 1900
const ToServer_Mode ToServer::ControlMode;
const ToServer_Mode ToServer::SelfMode;
const ToServer_Mode ToServer::Mode_MIN;
const ToServer_Mode ToServer::Mode_MAX;
const int ToServer::Mode_ARRAYSIZE;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

// ===================================================================

#if !defined(_MSC_VER) || _MSC_VER >= 1900
const int ToServer::kDataTypeFieldNumber;
const int ToServer::kModeInfoFieldNumber;
const int ToServer::kLeftFieldNumber;
const int ToServer::kRightFieldNumber;
const int ToServer::kForwardFieldNumber;
const int ToServer::kBackwardFieldNumber;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

ToServer::ToServer()
  : ::google::protobuf::Message(), _internal_metadata_(NULL) {
  if (GOOGLE_PREDICT_TRUE(this != internal_default_instance())) {
    protobuf_test_5fToServer_2eproto::InitDefaults();
  }
  SharedCtor();
  // @@protoc_insertion_point(constructor:test.ToServer)
}
ToServer::ToServer(const ToServer& from)
  : ::google::protobuf::Message(),
      _internal_metadata_(NULL),
      _has_bits_(from._has_bits_),
      _cached_size_(0) {
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::memcpy(&datatype_, &from.datatype_,
    static_cast<size_t>(reinterpret_cast<char*>(&backward_) -
    reinterpret_cast<char*>(&datatype_)) + sizeof(backward_));
  // @@protoc_insertion_point(copy_constructor:test.ToServer)
}

void ToServer::SharedCtor() {
  _cached_size_ = 0;
  ::memset(&datatype_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&backward_) -
      reinterpret_cast<char*>(&datatype_)) + sizeof(backward_));
}

ToServer::~ToServer() {
  // @@protoc_insertion_point(destructor:test.ToServer)
  SharedDtor();
}

void ToServer::SharedDtor() {
}

void ToServer::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* ToServer::descriptor() {
  protobuf_test_5fToServer_2eproto::protobuf_AssignDescriptorsOnce();
  return protobuf_test_5fToServer_2eproto::file_level_metadata[kIndexInFileMessages].descriptor;
}

const ToServer& ToServer::default_instance() {
  protobuf_test_5fToServer_2eproto::InitDefaults();
  return *internal_default_instance();
}

ToServer* ToServer::New(::google::protobuf::Arena* arena) const {
  ToServer* n = new ToServer;
  if (arena != NULL) {
    arena->Own(n);
  }
  return n;
}

void ToServer::Clear() {
// @@protoc_insertion_point(message_clear_start:test.ToServer)
  if (_has_bits_[0 / 32] & 63u) {
    ::memset(&datatype_, 0, static_cast<size_t>(
        reinterpret_cast<char*>(&backward_) -
        reinterpret_cast<char*>(&datatype_)) + sizeof(backward_));
  }
  _has_bits_.Clear();
  _internal_metadata_.Clear();
}

bool ToServer::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!GOOGLE_PREDICT_TRUE(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:test.ToServer)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoffNoLastTag(127u);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required .test.ToServer.Type DataType = 1;
      case 1: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(8u)) {
          int value;
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   int, ::google::protobuf::internal::WireFormatLite::TYPE_ENUM>(
                 input, &value)));
          if (::test::ToServer_Type_IsValid(value)) {
            set_datatype(static_cast< ::test::ToServer_Type >(value));
          } else {
            mutable_unknown_fields()->AddVarint(
                1, static_cast< ::google::protobuf::uint64>(value));
          }
        } else {
          goto handle_unusual;
        }
        break;
      }

      // required .test.ToServer.Mode ModeInfo = 2;
      case 2: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(16u)) {
          int value;
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   int, ::google::protobuf::internal::WireFormatLite::TYPE_ENUM>(
                 input, &value)));
          if (::test::ToServer_Mode_IsValid(value)) {
            set_modeinfo(static_cast< ::test::ToServer_Mode >(value));
          } else {
            mutable_unknown_fields()->AddVarint(
                2, static_cast< ::google::protobuf::uint64>(value));
          }
        } else {
          goto handle_unusual;
        }
        break;
      }

      // optional bool left = 3;
      case 3: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(24u)) {
          set_has_left();
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   bool, ::google::protobuf::internal::WireFormatLite::TYPE_BOOL>(
                 input, &left_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // optional bool right = 4;
      case 4: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(32u)) {
          set_has_right();
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   bool, ::google::protobuf::internal::WireFormatLite::TYPE_BOOL>(
                 input, &right_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // optional bool forward = 5;
      case 5: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(40u)) {
          set_has_forward();
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   bool, ::google::protobuf::internal::WireFormatLite::TYPE_BOOL>(
                 input, &forward_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // optional bool backward = 6;
      case 6: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(48u)) {
          set_has_backward();
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   bool, ::google::protobuf::internal::WireFormatLite::TYPE_BOOL>(
                 input, &backward_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0 ||
            ::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          goto success;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:test.ToServer)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:test.ToServer)
  return false;
#undef DO_
}

void ToServer::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:test.ToServer)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  cached_has_bits = _has_bits_[0];
  // required .test.ToServer.Type DataType = 1;
  if (cached_has_bits & 0x00000001u) {
    ::google::protobuf::internal::WireFormatLite::WriteEnum(
      1, this->datatype(), output);
  }

  // required .test.ToServer.Mode ModeInfo = 2;
  if (cached_has_bits & 0x00000002u) {
    ::google::protobuf::internal::WireFormatLite::WriteEnum(
      2, this->modeinfo(), output);
  }

  // optional bool left = 3;
  if (cached_has_bits & 0x00000004u) {
    ::google::protobuf::internal::WireFormatLite::WriteBool(3, this->left(), output);
  }

  // optional bool right = 4;
  if (cached_has_bits & 0x00000008u) {
    ::google::protobuf::internal::WireFormatLite::WriteBool(4, this->right(), output);
  }

  // optional bool forward = 5;
  if (cached_has_bits & 0x00000010u) {
    ::google::protobuf::internal::WireFormatLite::WriteBool(5, this->forward(), output);
  }

  // optional bool backward = 6;
  if (cached_has_bits & 0x00000020u) {
    ::google::protobuf::internal::WireFormatLite::WriteBool(6, this->backward(), output);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:test.ToServer)
}

::google::protobuf::uint8* ToServer::InternalSerializeWithCachedSizesToArray(
    bool deterministic, ::google::protobuf::uint8* target) const {
  (void)deterministic; // Unused
  // @@protoc_insertion_point(serialize_to_array_start:test.ToServer)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  cached_has_bits = _has_bits_[0];
  // required .test.ToServer.Type DataType = 1;
  if (cached_has_bits & 0x00000001u) {
    target = ::google::protobuf::internal::WireFormatLite::WriteEnumToArray(
      1, this->datatype(), target);
  }

  // required .test.ToServer.Mode ModeInfo = 2;
  if (cached_has_bits & 0x00000002u) {
    target = ::google::protobuf::internal::WireFormatLite::WriteEnumToArray(
      2, this->modeinfo(), target);
  }

  // optional bool left = 3;
  if (cached_has_bits & 0x00000004u) {
    target = ::google::protobuf::internal::WireFormatLite::WriteBoolToArray(3, this->left(), target);
  }

  // optional bool right = 4;
  if (cached_has_bits & 0x00000008u) {
    target = ::google::protobuf::internal::WireFormatLite::WriteBoolToArray(4, this->right(), target);
  }

  // optional bool forward = 5;
  if (cached_has_bits & 0x00000010u) {
    target = ::google::protobuf::internal::WireFormatLite::WriteBoolToArray(5, this->forward(), target);
  }

  // optional bool backward = 6;
  if (cached_has_bits & 0x00000020u) {
    target = ::google::protobuf::internal::WireFormatLite::WriteBoolToArray(6, this->backward(), target);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:test.ToServer)
  return target;
}

size_t ToServer::RequiredFieldsByteSizeFallback() const {
// @@protoc_insertion_point(required_fields_byte_size_fallback_start:test.ToServer)
  size_t total_size = 0;

  if (has_datatype()) {
    // required .test.ToServer.Type DataType = 1;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::EnumSize(this->datatype());
  }

  if (has_modeinfo()) {
    // required .test.ToServer.Mode ModeInfo = 2;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::EnumSize(this->modeinfo());
  }

  return total_size;
}
size_t ToServer::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:test.ToServer)
  size_t total_size = 0;

  if (_internal_metadata_.have_unknown_fields()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  if (((_has_bits_[0] & 0x00000003) ^ 0x00000003) == 0) {  // All required fields are present.
    // required .test.ToServer.Type DataType = 1;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::EnumSize(this->datatype());

    // required .test.ToServer.Mode ModeInfo = 2;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::EnumSize(this->modeinfo());

  } else {
    total_size += RequiredFieldsByteSizeFallback();
  }
  if (_has_bits_[0 / 32] & 60u) {
    // optional bool left = 3;
    if (has_left()) {
      total_size += 1 + 1;
    }

    // optional bool right = 4;
    if (has_right()) {
      total_size += 1 + 1;
    }

    // optional bool forward = 5;
    if (has_forward()) {
      total_size += 1 + 1;
    }

    // optional bool backward = 6;
    if (has_backward()) {
      total_size += 1 + 1;
    }

  }
  int cached_size = ::google::protobuf::internal::ToCachedSize(total_size);
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = cached_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void ToServer::MergeFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:test.ToServer)
  GOOGLE_DCHECK_NE(&from, this);
  const ToServer* source =
      ::google::protobuf::internal::DynamicCastToGenerated<const ToServer>(
          &from);
  if (source == NULL) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:test.ToServer)
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:test.ToServer)
    MergeFrom(*source);
  }
}

void ToServer::MergeFrom(const ToServer& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:test.ToServer)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  cached_has_bits = from._has_bits_[0];
  if (cached_has_bits & 63u) {
    if (cached_has_bits & 0x00000001u) {
      datatype_ = from.datatype_;
    }
    if (cached_has_bits & 0x00000002u) {
      modeinfo_ = from.modeinfo_;
    }
    if (cached_has_bits & 0x00000004u) {
      left_ = from.left_;
    }
    if (cached_has_bits & 0x00000008u) {
      right_ = from.right_;
    }
    if (cached_has_bits & 0x00000010u) {
      forward_ = from.forward_;
    }
    if (cached_has_bits & 0x00000020u) {
      backward_ = from.backward_;
    }
    _has_bits_[0] |= cached_has_bits;
  }
}

void ToServer::CopyFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:test.ToServer)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void ToServer::CopyFrom(const ToServer& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:test.ToServer)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool ToServer::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000003) != 0x00000003) return false;
  return true;
}

void ToServer::Swap(ToServer* other) {
  if (other == this) return;
  InternalSwap(other);
}
void ToServer::InternalSwap(ToServer* other) {
  std::swap(datatype_, other->datatype_);
  std::swap(modeinfo_, other->modeinfo_);
  std::swap(left_, other->left_);
  std::swap(right_, other->right_);
  std::swap(forward_, other->forward_);
  std::swap(backward_, other->backward_);
  std::swap(_has_bits_[0], other->_has_bits_[0]);
  _internal_metadata_.Swap(&other->_internal_metadata_);
  std::swap(_cached_size_, other->_cached_size_);
}

::google::protobuf::Metadata ToServer::GetMetadata() const {
  protobuf_test_5fToServer_2eproto::protobuf_AssignDescriptorsOnce();
  return protobuf_test_5fToServer_2eproto::file_level_metadata[kIndexInFileMessages];
}

#if PROTOBUF_INLINE_NOT_IN_HEADERS
// ToServer

// required .test.ToServer.Type DataType = 1;
bool ToServer::has_datatype() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
void ToServer::set_has_datatype() {
  _has_bits_[0] |= 0x00000001u;
}
void ToServer::clear_has_datatype() {
  _has_bits_[0] &= ~0x00000001u;
}
void ToServer::clear_datatype() {
  datatype_ = 0;
  clear_has_datatype();
}
::test::ToServer_Type ToServer::datatype() const {
  // @@protoc_insertion_point(field_get:test.ToServer.DataType)
  return static_cast< ::test::ToServer_Type >(datatype_);
}
void ToServer::set_datatype(::test::ToServer_Type value) {
  assert(::test::ToServer_Type_IsValid(value));
  set_has_datatype();
  datatype_ = value;
  // @@protoc_insertion_point(field_set:test.ToServer.DataType)
}

// required .test.ToServer.Mode ModeInfo = 2;
bool ToServer::has_modeinfo() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
void ToServer::set_has_modeinfo() {
  _has_bits_[0] |= 0x00000002u;
}
void ToServer::clear_has_modeinfo() {
  _has_bits_[0] &= ~0x00000002u;
}
void ToServer::clear_modeinfo() {
  modeinfo_ = 0;
  clear_has_modeinfo();
}
::test::ToServer_Mode ToServer::modeinfo() const {
  // @@protoc_insertion_point(field_get:test.ToServer.ModeInfo)
  return static_cast< ::test::ToServer_Mode >(modeinfo_);
}
void ToServer::set_modeinfo(::test::ToServer_Mode value) {
  assert(::test::ToServer_Mode_IsValid(value));
  set_has_modeinfo();
  modeinfo_ = value;
  // @@protoc_insertion_point(field_set:test.ToServer.ModeInfo)
}

// optional bool left = 3;
bool ToServer::has_left() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
void ToServer::set_has_left() {
  _has_bits_[0] |= 0x00000004u;
}
void ToServer::clear_has_left() {
  _has_bits_[0] &= ~0x00000004u;
}
void ToServer::clear_left() {
  left_ = false;
  clear_has_left();
}
bool ToServer::left() const {
  // @@protoc_insertion_point(field_get:test.ToServer.left)
  return left_;
}
void ToServer::set_left(bool value) {
  set_has_left();
  left_ = value;
  // @@protoc_insertion_point(field_set:test.ToServer.left)
}

// optional bool right = 4;
bool ToServer::has_right() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
void ToServer::set_has_right() {
  _has_bits_[0] |= 0x00000008u;
}
void ToServer::clear_has_right() {
  _has_bits_[0] &= ~0x00000008u;
}
void ToServer::clear_right() {
  right_ = false;
  clear_has_right();
}
bool ToServer::right() const {
  // @@protoc_insertion_point(field_get:test.ToServer.right)
  return right_;
}
void ToServer::set_right(bool value) {
  set_has_right();
  right_ = value;
  // @@protoc_insertion_point(field_set:test.ToServer.right)
}

// optional bool forward = 5;
bool ToServer::has_forward() const {
  return (_has_bits_[0] & 0x00000010u) != 0;
}
void ToServer::set_has_forward() {
  _has_bits_[0] |= 0x00000010u;
}
void ToServer::clear_has_forward() {
  _has_bits_[0] &= ~0x00000010u;
}
void ToServer::clear_forward() {
  forward_ = false;
  clear_has_forward();
}
bool ToServer::forward() const {
  // @@protoc_insertion_point(field_get:test.ToServer.forward)
  return forward_;
}
void ToServer::set_forward(bool value) {
  set_has_forward();
  forward_ = value;
  // @@protoc_insertion_point(field_set:test.ToServer.forward)
}

// optional bool backward = 6;
bool ToServer::has_backward() const {
  return (_has_bits_[0] & 0x00000020u) != 0;
}
void ToServer::set_has_backward() {
  _has_bits_[0] |= 0x00000020u;
}
void ToServer::clear_has_backward() {
  _has_bits_[0] &= ~0x00000020u;
}
void ToServer::clear_backward() {
  backward_ = false;
  clear_has_backward();
}
bool ToServer::backward() const {
  // @@protoc_insertion_point(field_get:test.ToServer.backward)
  return backward_;
}
void ToServer::set_backward(bool value) {
  set_has_backward();
  backward_ = value;
  // @@protoc_insertion_point(field_set:test.ToServer.backward)
}

#endif  // PROTOBUF_INLINE_NOT_IN_HEADERS

// @@protoc_insertion_point(namespace_scope)

}  // namespace test

// @@protoc_insertion_point(global_scope)

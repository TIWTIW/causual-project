// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: test_ToServer.proto

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
// This is a temporary google only hack
#ifdef GOOGLE_PROTOBUF_ENFORCE_UNIQUENESS
#include "third_party/protobuf/version.h"
#endif
// @@protoc_insertion_point(includes)
namespace test {
class ToServerDefaultTypeInternal {
 public:
  ::google::protobuf::internal::ExplicitlyConstructed<ToServer>
      _instance;
} _ToServer_default_instance_;
}  // namespace test
namespace protobuf_test_5fToServer_2eproto {
void InitDefaultsToServerImpl() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

#ifdef GOOGLE_PROTOBUF_ENFORCE_UNIQUENESS
  ::google::protobuf::internal::InitProtobufDefaultsForceUnique();
#else
  ::google::protobuf::internal::InitProtobufDefaults();
#endif  // GOOGLE_PROTOBUF_ENFORCE_UNIQUENESS
  {
    void* ptr = &::test::_ToServer_default_instance_;
    new (ptr) ::test::ToServer();
    ::google::protobuf::internal::OnShutdownDestroyMessage(ptr);
  }
  ::test::ToServer::InitAsDefaultInstance();
}

void InitDefaultsToServer() {
  static GOOGLE_PROTOBUF_DECLARE_ONCE(once);
  ::google::protobuf::GoogleOnceInit(&once, &InitDefaultsToServerImpl);
}

::google::protobuf::Metadata file_level_metadata[1];
const ::google::protobuf::EnumDescriptor* file_level_enum_descriptors[2];

const ::google::protobuf::uint32 TableStruct::offsets[] GOOGLE_PROTOBUF_ATTRIBUTE_SECTION_VARIABLE(protodesc_cold) = {
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::test::ToServer, _has_bits_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::test::ToServer, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::test::ToServer, datatype_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::test::ToServer, modeinfo_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::test::ToServer, left_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::test::ToServer, right_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::test::ToServer, forward_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::test::ToServer, backward_),
  0,
  1,
  2,
  3,
  4,
  5,
};
static const ::google::protobuf::internal::MigrationSchema schemas[] GOOGLE_PROTOBUF_ATTRIBUTE_SECTION_VARIABLE(protodesc_cold) = {
  { 0, 11, sizeof(::test::ToServer)},
};

static ::google::protobuf::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::google::protobuf::Message*>(&::test::_ToServer_default_instance_),
};

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

void protobuf_RegisterTypes(const ::std::string&) GOOGLE_PROTOBUF_ATTRIBUTE_COLD;
void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::internal::RegisterAllTypes(file_level_metadata, 1);
}

void AddDescriptorsImpl() {
  InitDefaults();
  static const char descriptor[] GOOGLE_PROTOBUF_ATTRIBUTE_SECTION_VARIABLE(protodesc_cold) = {
      "\n\023test_ToServer.proto\022\004test\"\211\002\n\010ToServer"
      "\022%\n\010DataType\030\001 \001(\0162\023.test.ToServer.Type\022"
      "%\n\010ModeInfo\030\002 \001(\0162\023.test.ToServer.Mode\022\014"
      "\n\004left\030\003 \001(\010\022\r\n\005right\030\004 \001(\010\022\017\n\007forward\030\005"
      " \001(\010\022\020\n\010backward\030\006 \001(\010\"7\n\004Type\022\017\n\013Defaul"
      "tType\020\000\022\r\n\tNeedImage\020\001\022\017\n\013NoNeedImage\020\002\""
      "6\n\004Mode\022\017\n\013DefaultMode\020\000\022\017\n\013ControlMode\020"
      "\001\022\014\n\010SelfMode\020\002"
  };
  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
      descriptor, 295);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "test_ToServer.proto", &protobuf_RegisterTypes);
}

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
namespace test {
const ::google::protobuf::EnumDescriptor* ToServer_Type_descriptor() {
  protobuf_test_5fToServer_2eproto::protobuf_AssignDescriptorsOnce();
  return protobuf_test_5fToServer_2eproto::file_level_enum_descriptors[0];
}
bool ToServer_Type_IsValid(int value) {
  switch (value) {
    case 0:
    case 1:
    case 2:
      return true;
    default:
      return false;
  }
}

#if !defined(_MSC_VER) || _MSC_VER >= 1900
const ToServer_Type ToServer::DefaultType;
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
    case 2:
      return true;
    default:
      return false;
  }
}

#if !defined(_MSC_VER) || _MSC_VER >= 1900
const ToServer_Mode ToServer::DefaultMode;
const ToServer_Mode ToServer::ControlMode;
const ToServer_Mode ToServer::SelfMode;
const ToServer_Mode ToServer::Mode_MIN;
const ToServer_Mode ToServer::Mode_MAX;
const int ToServer::Mode_ARRAYSIZE;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

// ===================================================================

void ToServer::InitAsDefaultInstance() {
}
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
    ::protobuf_test_5fToServer_2eproto::InitDefaultsToServer();
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
  ::protobuf_test_5fToServer_2eproto::protobuf_AssignDescriptorsOnce();
  return ::protobuf_test_5fToServer_2eproto::file_level_metadata[kIndexInFileMessages].descriptor;
}

const ToServer& ToServer::default_instance() {
  ::protobuf_test_5fToServer_2eproto::InitDefaultsToServer();
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
  ::google::protobuf::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  cached_has_bits = _has_bits_[0];
  if (cached_has_bits & 63u) {
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
      // optional .test.ToServer.Type DataType = 1;
      case 1: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(8u /* 8 & 0xFF */)) {
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

      // optional .test.ToServer.Mode ModeInfo = 2;
      case 2: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(16u /* 16 & 0xFF */)) {
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
            static_cast< ::google::protobuf::uint8>(24u /* 24 & 0xFF */)) {
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
            static_cast< ::google::protobuf::uint8>(32u /* 32 & 0xFF */)) {
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
            static_cast< ::google::protobuf::uint8>(40u /* 40 & 0xFF */)) {
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
            static_cast< ::google::protobuf::uint8>(48u /* 48 & 0xFF */)) {
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
        if (tag == 0) {
          goto success;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, _internal_metadata_.mutable_unknown_fields()));
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
  // optional .test.ToServer.Type DataType = 1;
  if (cached_has_bits & 0x00000001u) {
    ::google::protobuf::internal::WireFormatLite::WriteEnum(
      1, this->datatype(), output);
  }

  // optional .test.ToServer.Mode ModeInfo = 2;
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
        _internal_metadata_.unknown_fields(), output);
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
  // optional .test.ToServer.Type DataType = 1;
  if (cached_has_bits & 0x00000001u) {
    target = ::google::protobuf::internal::WireFormatLite::WriteEnumToArray(
      1, this->datatype(), target);
  }

  // optional .test.ToServer.Mode ModeInfo = 2;
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
        _internal_metadata_.unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:test.ToServer)
  return target;
}

size_t ToServer::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:test.ToServer)
  size_t total_size = 0;

  if (_internal_metadata_.have_unknown_fields()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        _internal_metadata_.unknown_fields());
  }
  if (_has_bits_[0 / 32] & 63u) {
    // optional .test.ToServer.Type DataType = 1;
    if (has_datatype()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::EnumSize(this->datatype());
    }

    // optional .test.ToServer.Mode ModeInfo = 2;
    if (has_modeinfo()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::EnumSize(this->modeinfo());
    }

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
  return true;
}

void ToServer::Swap(ToServer* other) {
  if (other == this) return;
  InternalSwap(other);
}
void ToServer::InternalSwap(ToServer* other) {
  using std::swap;
  swap(datatype_, other->datatype_);
  swap(modeinfo_, other->modeinfo_);
  swap(left_, other->left_);
  swap(right_, other->right_);
  swap(forward_, other->forward_);
  swap(backward_, other->backward_);
  swap(_has_bits_[0], other->_has_bits_[0]);
  _internal_metadata_.Swap(&other->_internal_metadata_);
  swap(_cached_size_, other->_cached_size_);
}

::google::protobuf::Metadata ToServer::GetMetadata() const {
  protobuf_test_5fToServer_2eproto::protobuf_AssignDescriptorsOnce();
  return ::protobuf_test_5fToServer_2eproto::file_level_metadata[kIndexInFileMessages];
}


// @@protoc_insertion_point(namespace_scope)
}  // namespace test

// @@protoc_insertion_point(global_scope)

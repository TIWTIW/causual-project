// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: request.proto

#include "request.pb.h"

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
namespace networkLearn {
class RequestDefaultTypeInternal {
 public:
  ::google::protobuf::internal::ExplicitlyConstructed<Request>
      _instance;
} _Request_default_instance_;
}  // namespace networkLearn
namespace protobuf_request_2eproto {
void InitDefaultsRequestImpl() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

#ifdef GOOGLE_PROTOBUF_ENFORCE_UNIQUENESS
  ::google::protobuf::internal::InitProtobufDefaultsForceUnique();
#else
  ::google::protobuf::internal::InitProtobufDefaults();
#endif  // GOOGLE_PROTOBUF_ENFORCE_UNIQUENESS
  protobuf_httpRequest_2eproto::InitDefaultshttpRequest();
  protobuf_google_2fprotobuf_2ftimestamp_2eproto::InitDefaultsTimestamp();
  {
    void* ptr = &::networkLearn::_Request_default_instance_;
    new (ptr) ::networkLearn::Request();
    ::google::protobuf::internal::OnShutdownDestroyMessage(ptr);
  }
  ::networkLearn::Request::InitAsDefaultInstance();
}

void InitDefaultsRequest() {
  static GOOGLE_PROTOBUF_DECLARE_ONCE(once);
  ::google::protobuf::GoogleOnceInit(&once, &InitDefaultsRequestImpl);
}

::google::protobuf::Metadata file_level_metadata[1];

const ::google::protobuf::uint32 TableStruct::offsets[] GOOGLE_PROTOBUF_ATTRIBUTE_SECTION_VARIABLE(protodesc_cold) = {
  ~0u,  // no _has_bits_
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::networkLearn::Request, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::networkLearn::Request, length_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::networkLearn::Request, version_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::networkLearn::Request, content_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::networkLearn::Request, last_updated_),
};
static const ::google::protobuf::internal::MigrationSchema schemas[] GOOGLE_PROTOBUF_ATTRIBUTE_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, sizeof(::networkLearn::Request)},
};

static ::google::protobuf::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::google::protobuf::Message*>(&::networkLearn::_Request_default_instance_),
};

void protobuf_AssignDescriptors() {
  AddDescriptors();
  ::google::protobuf::MessageFactory* factory = NULL;
  AssignDescriptors(
      "request.proto", schemas, file_default_instances, TableStruct::offsets, factory,
      file_level_metadata, NULL, NULL);
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
      "\n\rrequest.proto\022\014networkLearn\032\037google/pr"
      "otobuf/timestamp.proto\032\021httpRequest.prot"
      "o\"\210\001\n\007Request\022\016\n\006length\030\001 \001(\005\022\017\n\007version"
      "\030\002 \001(\t\022*\n\007content\030\003 \001(\0132\031.networkLearn.h"
      "ttpRequest\0220\n\014last_updated\030\004 \001(\0132\032.googl"
      "e.protobuf.Timestampb\006proto3"
  };
  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
      descriptor, 228);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "request.proto", &protobuf_RegisterTypes);
  ::protobuf_google_2fprotobuf_2ftimestamp_2eproto::AddDescriptors();
  ::protobuf_httpRequest_2eproto::AddDescriptors();
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
}  // namespace protobuf_request_2eproto
namespace networkLearn {

// ===================================================================

void Request::InitAsDefaultInstance() {
  ::networkLearn::_Request_default_instance_._instance.get_mutable()->content_ = const_cast< ::networkLearn::httpRequest*>(
      ::networkLearn::httpRequest::internal_default_instance());
  ::networkLearn::_Request_default_instance_._instance.get_mutable()->last_updated_ = const_cast< ::google::protobuf::Timestamp*>(
      ::google::protobuf::Timestamp::internal_default_instance());
}
void Request::clear_content() {
  if (GetArenaNoVirtual() == NULL && content_ != NULL) {
    delete content_;
  }
  content_ = NULL;
}
void Request::clear_last_updated() {
  if (GetArenaNoVirtual() == NULL && last_updated_ != NULL) {
    delete last_updated_;
  }
  last_updated_ = NULL;
}
#if !defined(_MSC_VER) || _MSC_VER >= 1900
const int Request::kLengthFieldNumber;
const int Request::kVersionFieldNumber;
const int Request::kContentFieldNumber;
const int Request::kLastUpdatedFieldNumber;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

Request::Request()
  : ::google::protobuf::Message(), _internal_metadata_(NULL) {
  if (GOOGLE_PREDICT_TRUE(this != internal_default_instance())) {
    ::protobuf_request_2eproto::InitDefaultsRequest();
  }
  SharedCtor();
  // @@protoc_insertion_point(constructor:networkLearn.Request)
}
Request::Request(const Request& from)
  : ::google::protobuf::Message(),
      _internal_metadata_(NULL),
      _cached_size_(0) {
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  version_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  if (from.version().size() > 0) {
    version_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.version_);
  }
  if (from.has_content()) {
    content_ = new ::networkLearn::httpRequest(*from.content_);
  } else {
    content_ = NULL;
  }
  if (from.has_last_updated()) {
    last_updated_ = new ::google::protobuf::Timestamp(*from.last_updated_);
  } else {
    last_updated_ = NULL;
  }
  length_ = from.length_;
  // @@protoc_insertion_point(copy_constructor:networkLearn.Request)
}

void Request::SharedCtor() {
  version_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  ::memset(&content_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&length_) -
      reinterpret_cast<char*>(&content_)) + sizeof(length_));
  _cached_size_ = 0;
}

Request::~Request() {
  // @@protoc_insertion_point(destructor:networkLearn.Request)
  SharedDtor();
}

void Request::SharedDtor() {
  version_.DestroyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  if (this != internal_default_instance()) delete content_;
  if (this != internal_default_instance()) delete last_updated_;
}

void Request::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* Request::descriptor() {
  ::protobuf_request_2eproto::protobuf_AssignDescriptorsOnce();
  return ::protobuf_request_2eproto::file_level_metadata[kIndexInFileMessages].descriptor;
}

const Request& Request::default_instance() {
  ::protobuf_request_2eproto::InitDefaultsRequest();
  return *internal_default_instance();
}

Request* Request::New(::google::protobuf::Arena* arena) const {
  Request* n = new Request;
  if (arena != NULL) {
    arena->Own(n);
  }
  return n;
}

void Request::Clear() {
// @@protoc_insertion_point(message_clear_start:networkLearn.Request)
  ::google::protobuf::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  version_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  if (GetArenaNoVirtual() == NULL && content_ != NULL) {
    delete content_;
  }
  content_ = NULL;
  if (GetArenaNoVirtual() == NULL && last_updated_ != NULL) {
    delete last_updated_;
  }
  last_updated_ = NULL;
  length_ = 0;
  _internal_metadata_.Clear();
}

bool Request::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!GOOGLE_PREDICT_TRUE(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:networkLearn.Request)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoffNoLastTag(127u);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // int32 length = 1;
      case 1: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(8u /* 8 & 0xFF */)) {

          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &length_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // string version = 2;
      case 2: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(18u /* 18 & 0xFF */)) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_version()));
          DO_(::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
            this->version().data(), static_cast<int>(this->version().length()),
            ::google::protobuf::internal::WireFormatLite::PARSE,
            "networkLearn.Request.version"));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // .networkLearn.httpRequest content = 3;
      case 3: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(26u /* 26 & 0xFF */)) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessage(
               input, mutable_content()));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // .google.protobuf.Timestamp last_updated = 4;
      case 4: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(34u /* 34 & 0xFF */)) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessage(
               input, mutable_last_updated()));
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
  // @@protoc_insertion_point(parse_success:networkLearn.Request)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:networkLearn.Request)
  return false;
#undef DO_
}

void Request::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:networkLearn.Request)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // int32 length = 1;
  if (this->length() != 0) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(1, this->length(), output);
  }

  // string version = 2;
  if (this->version().size() > 0) {
    ::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
      this->version().data(), static_cast<int>(this->version().length()),
      ::google::protobuf::internal::WireFormatLite::SERIALIZE,
      "networkLearn.Request.version");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      2, this->version(), output);
  }

  // .networkLearn.httpRequest content = 3;
  if (this->has_content()) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      3, *this->content_, output);
  }

  // .google.protobuf.Timestamp last_updated = 4;
  if (this->has_last_updated()) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      4, *this->last_updated_, output);
  }

  if ((_internal_metadata_.have_unknown_fields() &&  ::google::protobuf::internal::GetProto3PreserveUnknownsDefault())) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        (::google::protobuf::internal::GetProto3PreserveUnknownsDefault()   ? _internal_metadata_.unknown_fields()   : _internal_metadata_.default_instance()), output);
  }
  // @@protoc_insertion_point(serialize_end:networkLearn.Request)
}

::google::protobuf::uint8* Request::InternalSerializeWithCachedSizesToArray(
    bool deterministic, ::google::protobuf::uint8* target) const {
  (void)deterministic; // Unused
  // @@protoc_insertion_point(serialize_to_array_start:networkLearn.Request)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // int32 length = 1;
  if (this->length() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(1, this->length(), target);
  }

  // string version = 2;
  if (this->version().size() > 0) {
    ::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
      this->version().data(), static_cast<int>(this->version().length()),
      ::google::protobuf::internal::WireFormatLite::SERIALIZE,
      "networkLearn.Request.version");
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        2, this->version(), target);
  }

  // .networkLearn.httpRequest content = 3;
  if (this->has_content()) {
    target = ::google::protobuf::internal::WireFormatLite::
      InternalWriteMessageToArray(
        3, *this->content_, deterministic, target);
  }

  // .google.protobuf.Timestamp last_updated = 4;
  if (this->has_last_updated()) {
    target = ::google::protobuf::internal::WireFormatLite::
      InternalWriteMessageToArray(
        4, *this->last_updated_, deterministic, target);
  }

  if ((_internal_metadata_.have_unknown_fields() &&  ::google::protobuf::internal::GetProto3PreserveUnknownsDefault())) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        (::google::protobuf::internal::GetProto3PreserveUnknownsDefault()   ? _internal_metadata_.unknown_fields()   : _internal_metadata_.default_instance()), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:networkLearn.Request)
  return target;
}

size_t Request::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:networkLearn.Request)
  size_t total_size = 0;

  if ((_internal_metadata_.have_unknown_fields() &&  ::google::protobuf::internal::GetProto3PreserveUnknownsDefault())) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        (::google::protobuf::internal::GetProto3PreserveUnknownsDefault()   ? _internal_metadata_.unknown_fields()   : _internal_metadata_.default_instance()));
  }
  // string version = 2;
  if (this->version().size() > 0) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::StringSize(
        this->version());
  }

  // .networkLearn.httpRequest content = 3;
  if (this->has_content()) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::MessageSize(
        *this->content_);
  }

  // .google.protobuf.Timestamp last_updated = 4;
  if (this->has_last_updated()) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::MessageSize(
        *this->last_updated_);
  }

  // int32 length = 1;
  if (this->length() != 0) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::Int32Size(
        this->length());
  }

  int cached_size = ::google::protobuf::internal::ToCachedSize(total_size);
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = cached_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void Request::MergeFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:networkLearn.Request)
  GOOGLE_DCHECK_NE(&from, this);
  const Request* source =
      ::google::protobuf::internal::DynamicCastToGenerated<const Request>(
          &from);
  if (source == NULL) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:networkLearn.Request)
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:networkLearn.Request)
    MergeFrom(*source);
  }
}

void Request::MergeFrom(const Request& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:networkLearn.Request)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  if (from.version().size() > 0) {

    version_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.version_);
  }
  if (from.has_content()) {
    mutable_content()->::networkLearn::httpRequest::MergeFrom(from.content());
  }
  if (from.has_last_updated()) {
    mutable_last_updated()->::google::protobuf::Timestamp::MergeFrom(from.last_updated());
  }
  if (from.length() != 0) {
    set_length(from.length());
  }
}

void Request::CopyFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:networkLearn.Request)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void Request::CopyFrom(const Request& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:networkLearn.Request)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Request::IsInitialized() const {
  return true;
}

void Request::Swap(Request* other) {
  if (other == this) return;
  InternalSwap(other);
}
void Request::InternalSwap(Request* other) {
  using std::swap;
  version_.Swap(&other->version_);
  swap(content_, other->content_);
  swap(last_updated_, other->last_updated_);
  swap(length_, other->length_);
  _internal_metadata_.Swap(&other->_internal_metadata_);
  swap(_cached_size_, other->_cached_size_);
}

::google::protobuf::Metadata Request::GetMetadata() const {
  protobuf_request_2eproto::protobuf_AssignDescriptorsOnce();
  return ::protobuf_request_2eproto::file_level_metadata[kIndexInFileMessages];
}


// @@protoc_insertion_point(namespace_scope)
}  // namespace networkLearn

// @@protoc_insertion_point(global_scope)

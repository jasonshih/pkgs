/**
 * Autogenerated by Thrift Compiler (0.9.0)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#include "StateStoreService_types.h"

#include <algorithm>

namespace impala {

int _kStateStoreServiceVersionValues[] = {
  StateStoreServiceVersion::V1
};
const char* _kStateStoreServiceVersionNames[] = {
  "V1"
};
const std::map<int, const char*> _StateStoreServiceVersion_VALUES_TO_NAMES(::apache::thrift::TEnumIterator(1, _kStateStoreServiceVersionValues, _kStateStoreServiceVersionNames), ::apache::thrift::TEnumIterator(-1, NULL, NULL));

const char* TBackendDescriptor::ascii_fingerprint = "60AD13F4E27EBFD15F3C4A5627C15865";
const uint8_t TBackendDescriptor::binary_fingerprint[16] = {0x60,0xAD,0x13,0xF4,0xE2,0x7E,0xBF,0xD1,0x5F,0x3C,0x4A,0x56,0x27,0xC1,0x58,0x65};

uint32_t TBackendDescriptor::read(::apache::thrift::protocol::TProtocol* iprot) {

  uint32_t xfer = 0;
  std::string fname;
  ::apache::thrift::protocol::TType ftype;
  int16_t fid;

  xfer += iprot->readStructBegin(fname);

  using ::apache::thrift::protocol::TProtocolException;

  bool isset_address = false;
  bool isset_ip_address = false;

  while (true)
  {
    xfer += iprot->readFieldBegin(fname, ftype, fid);
    if (ftype == ::apache::thrift::protocol::T_STOP) {
      break;
    }
    switch (fid)
    {
      case 1:
        if (ftype == ::apache::thrift::protocol::T_STRUCT) {
          xfer += this->address.read(iprot);
          isset_address = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 2:
        if (ftype == ::apache::thrift::protocol::T_STRING) {
          xfer += iprot->readString(this->ip_address);
          isset_ip_address = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 3:
        if (ftype == ::apache::thrift::protocol::T_STRUCT) {
          xfer += this->debug_http_address.read(iprot);
          this->__isset.debug_http_address = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      default:
        xfer += iprot->skip(ftype);
        break;
    }
    xfer += iprot->readFieldEnd();
  }

  xfer += iprot->readStructEnd();

  if (!isset_address)
    throw TProtocolException(TProtocolException::INVALID_DATA);
  if (!isset_ip_address)
    throw TProtocolException(TProtocolException::INVALID_DATA);
  return xfer;
}

uint32_t TBackendDescriptor::write(::apache::thrift::protocol::TProtocol* oprot) const {
  uint32_t xfer = 0;
  uint32_t fcnt = 0;
  xfer += oprot->writeStructBegin("TBackendDescriptor");

  ++fcnt;
  xfer += oprot->writeFieldBegin("address", ::apache::thrift::protocol::T_STRUCT, 1);
  xfer += this->address.write(oprot);
  xfer += oprot->writeFieldEnd();

  ++fcnt;
  xfer += oprot->writeFieldBegin("ip_address", ::apache::thrift::protocol::T_STRING, 2);
  xfer += oprot->writeString(this->ip_address);
  xfer += oprot->writeFieldEnd();

  if (this->__isset.debug_http_address) {
    ++fcnt;
    xfer += oprot->writeFieldBegin("debug_http_address", ::apache::thrift::protocol::T_STRUCT, 3);
    xfer += this->debug_http_address.write(oprot);
    xfer += oprot->writeFieldEnd();
  }
  xfer += oprot->writeFieldStop();
  xfer += oprot->writeStructEnd();
  return xfer;
}

void swap(TBackendDescriptor &a, TBackendDescriptor &b) {
  using ::std::swap;
  swap(a.address, b.address);
  swap(a.ip_address, b.ip_address);
  swap(a.debug_http_address, b.debug_http_address);
  swap(a.__isset, b.__isset);
}

const char* TTopicItem::ascii_fingerprint = "07A9615F837F7D0A952B595DD3020972";
const uint8_t TTopicItem::binary_fingerprint[16] = {0x07,0xA9,0x61,0x5F,0x83,0x7F,0x7D,0x0A,0x95,0x2B,0x59,0x5D,0xD3,0x02,0x09,0x72};

uint32_t TTopicItem::read(::apache::thrift::protocol::TProtocol* iprot) {

  uint32_t xfer = 0;
  std::string fname;
  ::apache::thrift::protocol::TType ftype;
  int16_t fid;

  xfer += iprot->readStructBegin(fname);

  using ::apache::thrift::protocol::TProtocolException;

  bool isset_key = false;
  bool isset_value = false;

  while (true)
  {
    xfer += iprot->readFieldBegin(fname, ftype, fid);
    if (ftype == ::apache::thrift::protocol::T_STOP) {
      break;
    }
    switch (fid)
    {
      case 1:
        if (ftype == ::apache::thrift::protocol::T_STRING) {
          xfer += iprot->readString(this->key);
          isset_key = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 2:
        if (ftype == ::apache::thrift::protocol::T_STRING) {
          xfer += iprot->readString(this->value);
          isset_value = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      default:
        xfer += iprot->skip(ftype);
        break;
    }
    xfer += iprot->readFieldEnd();
  }

  xfer += iprot->readStructEnd();

  if (!isset_key)
    throw TProtocolException(TProtocolException::INVALID_DATA);
  if (!isset_value)
    throw TProtocolException(TProtocolException::INVALID_DATA);
  return xfer;
}

uint32_t TTopicItem::write(::apache::thrift::protocol::TProtocol* oprot) const {
  uint32_t xfer = 0;
  uint32_t fcnt = 0;
  xfer += oprot->writeStructBegin("TTopicItem");

  ++fcnt;
  xfer += oprot->writeFieldBegin("key", ::apache::thrift::protocol::T_STRING, 1);
  xfer += oprot->writeString(this->key);
  xfer += oprot->writeFieldEnd();

  ++fcnt;
  xfer += oprot->writeFieldBegin("value", ::apache::thrift::protocol::T_STRING, 2);
  xfer += oprot->writeString(this->value);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldStop();
  xfer += oprot->writeStructEnd();
  return xfer;
}

void swap(TTopicItem &a, TTopicItem &b) {
  using ::std::swap;
  swap(a.key, b.key);
  swap(a.value, b.value);
}

const char* TTopicUpdate::ascii_fingerprint = "63BEFF99DEA50F978623FCD4A34DFFEB";
const uint8_t TTopicUpdate::binary_fingerprint[16] = {0x63,0xBE,0xFF,0x99,0xDE,0xA5,0x0F,0x97,0x86,0x23,0xFC,0xD4,0xA3,0x4D,0xFF,0xEB};

uint32_t TTopicUpdate::read(::apache::thrift::protocol::TProtocol* iprot) {

  uint32_t xfer = 0;
  std::string fname;
  ::apache::thrift::protocol::TType ftype;
  int16_t fid;

  xfer += iprot->readStructBegin(fname);

  using ::apache::thrift::protocol::TProtocolException;

  bool isset_topic_name = false;
  bool isset_topic_updates = false;
  bool isset_topic_deletions = false;

  while (true)
  {
    xfer += iprot->readFieldBegin(fname, ftype, fid);
    if (ftype == ::apache::thrift::protocol::T_STOP) {
      break;
    }
    switch (fid)
    {
      case 1:
        if (ftype == ::apache::thrift::protocol::T_STRING) {
          xfer += iprot->readString(this->topic_name);
          isset_topic_name = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 2:
        if (ftype == ::apache::thrift::protocol::T_LIST) {
          {
            this->topic_updates.clear();
            uint32_t _size0;
            ::apache::thrift::protocol::TType _etype3;
            xfer += iprot->readListBegin(_etype3, _size0);
            this->topic_updates.resize(_size0);
            uint32_t _i4;
            for (_i4 = 0; _i4 < _size0; ++_i4)
            {
              xfer += this->topic_updates[_i4].read(iprot);
            }
            xfer += iprot->readListEnd();
          }
          isset_topic_updates = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 3:
        if (ftype == ::apache::thrift::protocol::T_LIST) {
          {
            this->topic_deletions.clear();
            uint32_t _size5;
            ::apache::thrift::protocol::TType _etype8;
            xfer += iprot->readListBegin(_etype8, _size5);
            this->topic_deletions.resize(_size5);
            uint32_t _i9;
            for (_i9 = 0; _i9 < _size5; ++_i9)
            {
              xfer += iprot->readString(this->topic_deletions[_i9]);
            }
            xfer += iprot->readListEnd();
          }
          isset_topic_deletions = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      default:
        xfer += iprot->skip(ftype);
        break;
    }
    xfer += iprot->readFieldEnd();
  }

  xfer += iprot->readStructEnd();

  if (!isset_topic_name)
    throw TProtocolException(TProtocolException::INVALID_DATA);
  if (!isset_topic_updates)
    throw TProtocolException(TProtocolException::INVALID_DATA);
  if (!isset_topic_deletions)
    throw TProtocolException(TProtocolException::INVALID_DATA);
  return xfer;
}

uint32_t TTopicUpdate::write(::apache::thrift::protocol::TProtocol* oprot) const {
  uint32_t xfer = 0;
  uint32_t fcnt = 0;
  xfer += oprot->writeStructBegin("TTopicUpdate");

  ++fcnt;
  xfer += oprot->writeFieldBegin("topic_name", ::apache::thrift::protocol::T_STRING, 1);
  xfer += oprot->writeString(this->topic_name);
  xfer += oprot->writeFieldEnd();

  ++fcnt;
  xfer += oprot->writeFieldBegin("topic_updates", ::apache::thrift::protocol::T_LIST, 2);
  {
    xfer += oprot->writeListBegin(::apache::thrift::protocol::T_STRUCT, static_cast<uint32_t>(this->topic_updates.size()));
    std::vector<TTopicItem> ::const_iterator _iter10;
    for (_iter10 = this->topic_updates.begin(); _iter10 != this->topic_updates.end(); ++_iter10)
    {
      xfer += (*_iter10).write(oprot);
    }
    xfer += oprot->writeListEnd();
  }
  xfer += oprot->writeFieldEnd();

  ++fcnt;
  xfer += oprot->writeFieldBegin("topic_deletions", ::apache::thrift::protocol::T_LIST, 3);
  {
    xfer += oprot->writeListBegin(::apache::thrift::protocol::T_STRING, static_cast<uint32_t>(this->topic_deletions.size()));
    std::vector<std::string> ::const_iterator _iter11;
    for (_iter11 = this->topic_deletions.begin(); _iter11 != this->topic_deletions.end(); ++_iter11)
    {
      xfer += oprot->writeString((*_iter11));
    }
    xfer += oprot->writeListEnd();
  }
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldStop();
  xfer += oprot->writeStructEnd();
  return xfer;
}

void swap(TTopicUpdate &a, TTopicUpdate &b) {
  using ::std::swap;
  swap(a.topic_name, b.topic_name);
  swap(a.topic_updates, b.topic_updates);
  swap(a.topic_deletions, b.topic_deletions);
}

const char* TTopicDelta::ascii_fingerprint = "C2805DE04682BB50E371BDF62B2C1232";
const uint8_t TTopicDelta::binary_fingerprint[16] = {0xC2,0x80,0x5D,0xE0,0x46,0x82,0xBB,0x50,0xE3,0x71,0xBD,0xF6,0x2B,0x2C,0x12,0x32};

uint32_t TTopicDelta::read(::apache::thrift::protocol::TProtocol* iprot) {

  uint32_t xfer = 0;
  std::string fname;
  ::apache::thrift::protocol::TType ftype;
  int16_t fid;

  xfer += iprot->readStructBegin(fname);

  using ::apache::thrift::protocol::TProtocolException;

  bool isset_topic_name = false;
  bool isset_topic_entries = false;
  bool isset_topic_deletions = false;
  bool isset_is_delta = false;

  while (true)
  {
    xfer += iprot->readFieldBegin(fname, ftype, fid);
    if (ftype == ::apache::thrift::protocol::T_STOP) {
      break;
    }
    switch (fid)
    {
      case 1:
        if (ftype == ::apache::thrift::protocol::T_STRING) {
          xfer += iprot->readString(this->topic_name);
          isset_topic_name = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 2:
        if (ftype == ::apache::thrift::protocol::T_LIST) {
          {
            this->topic_entries.clear();
            uint32_t _size12;
            ::apache::thrift::protocol::TType _etype15;
            xfer += iprot->readListBegin(_etype15, _size12);
            this->topic_entries.resize(_size12);
            uint32_t _i16;
            for (_i16 = 0; _i16 < _size12; ++_i16)
            {
              xfer += this->topic_entries[_i16].read(iprot);
            }
            xfer += iprot->readListEnd();
          }
          isset_topic_entries = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 3:
        if (ftype == ::apache::thrift::protocol::T_LIST) {
          {
            this->topic_deletions.clear();
            uint32_t _size17;
            ::apache::thrift::protocol::TType _etype20;
            xfer += iprot->readListBegin(_etype20, _size17);
            this->topic_deletions.resize(_size17);
            uint32_t _i21;
            for (_i21 = 0; _i21 < _size17; ++_i21)
            {
              xfer += iprot->readString(this->topic_deletions[_i21]);
            }
            xfer += iprot->readListEnd();
          }
          isset_topic_deletions = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 4:
        if (ftype == ::apache::thrift::protocol::T_BOOL) {
          xfer += iprot->readBool(this->is_delta);
          isset_is_delta = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      default:
        xfer += iprot->skip(ftype);
        break;
    }
    xfer += iprot->readFieldEnd();
  }

  xfer += iprot->readStructEnd();

  if (!isset_topic_name)
    throw TProtocolException(TProtocolException::INVALID_DATA);
  if (!isset_topic_entries)
    throw TProtocolException(TProtocolException::INVALID_DATA);
  if (!isset_topic_deletions)
    throw TProtocolException(TProtocolException::INVALID_DATA);
  if (!isset_is_delta)
    throw TProtocolException(TProtocolException::INVALID_DATA);
  return xfer;
}

uint32_t TTopicDelta::write(::apache::thrift::protocol::TProtocol* oprot) const {
  uint32_t xfer = 0;
  uint32_t fcnt = 0;
  xfer += oprot->writeStructBegin("TTopicDelta");

  ++fcnt;
  xfer += oprot->writeFieldBegin("topic_name", ::apache::thrift::protocol::T_STRING, 1);
  xfer += oprot->writeString(this->topic_name);
  xfer += oprot->writeFieldEnd();

  ++fcnt;
  xfer += oprot->writeFieldBegin("topic_entries", ::apache::thrift::protocol::T_LIST, 2);
  {
    xfer += oprot->writeListBegin(::apache::thrift::protocol::T_STRUCT, static_cast<uint32_t>(this->topic_entries.size()));
    std::vector<TTopicItem> ::const_iterator _iter22;
    for (_iter22 = this->topic_entries.begin(); _iter22 != this->topic_entries.end(); ++_iter22)
    {
      xfer += (*_iter22).write(oprot);
    }
    xfer += oprot->writeListEnd();
  }
  xfer += oprot->writeFieldEnd();

  ++fcnt;
  xfer += oprot->writeFieldBegin("topic_deletions", ::apache::thrift::protocol::T_LIST, 3);
  {
    xfer += oprot->writeListBegin(::apache::thrift::protocol::T_STRING, static_cast<uint32_t>(this->topic_deletions.size()));
    std::vector<std::string> ::const_iterator _iter23;
    for (_iter23 = this->topic_deletions.begin(); _iter23 != this->topic_deletions.end(); ++_iter23)
    {
      xfer += oprot->writeString((*_iter23));
    }
    xfer += oprot->writeListEnd();
  }
  xfer += oprot->writeFieldEnd();

  ++fcnt;
  xfer += oprot->writeFieldBegin("is_delta", ::apache::thrift::protocol::T_BOOL, 4);
  xfer += oprot->writeBool(this->is_delta);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldStop();
  xfer += oprot->writeStructEnd();
  return xfer;
}

void swap(TTopicDelta &a, TTopicDelta &b) {
  using ::std::swap;
  swap(a.topic_name, b.topic_name);
  swap(a.topic_entries, b.topic_entries);
  swap(a.topic_deletions, b.topic_deletions);
  swap(a.is_delta, b.is_delta);
}

const char* TTopicRegistration::ascii_fingerprint = "7D61C9AA00102AB4D8F72A1DA58297DC";
const uint8_t TTopicRegistration::binary_fingerprint[16] = {0x7D,0x61,0xC9,0xAA,0x00,0x10,0x2A,0xB4,0xD8,0xF7,0x2A,0x1D,0xA5,0x82,0x97,0xDC};

uint32_t TTopicRegistration::read(::apache::thrift::protocol::TProtocol* iprot) {

  uint32_t xfer = 0;
  std::string fname;
  ::apache::thrift::protocol::TType ftype;
  int16_t fid;

  xfer += iprot->readStructBegin(fname);

  using ::apache::thrift::protocol::TProtocolException;

  bool isset_topic_name = false;
  bool isset_is_transient = false;

  while (true)
  {
    xfer += iprot->readFieldBegin(fname, ftype, fid);
    if (ftype == ::apache::thrift::protocol::T_STOP) {
      break;
    }
    switch (fid)
    {
      case 1:
        if (ftype == ::apache::thrift::protocol::T_STRING) {
          xfer += iprot->readString(this->topic_name);
          isset_topic_name = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 2:
        if (ftype == ::apache::thrift::protocol::T_BOOL) {
          xfer += iprot->readBool(this->is_transient);
          isset_is_transient = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      default:
        xfer += iprot->skip(ftype);
        break;
    }
    xfer += iprot->readFieldEnd();
  }

  xfer += iprot->readStructEnd();

  if (!isset_topic_name)
    throw TProtocolException(TProtocolException::INVALID_DATA);
  if (!isset_is_transient)
    throw TProtocolException(TProtocolException::INVALID_DATA);
  return xfer;
}

uint32_t TTopicRegistration::write(::apache::thrift::protocol::TProtocol* oprot) const {
  uint32_t xfer = 0;
  uint32_t fcnt = 0;
  xfer += oprot->writeStructBegin("TTopicRegistration");

  ++fcnt;
  xfer += oprot->writeFieldBegin("topic_name", ::apache::thrift::protocol::T_STRING, 1);
  xfer += oprot->writeString(this->topic_name);
  xfer += oprot->writeFieldEnd();

  ++fcnt;
  xfer += oprot->writeFieldBegin("is_transient", ::apache::thrift::protocol::T_BOOL, 2);
  xfer += oprot->writeBool(this->is_transient);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldStop();
  xfer += oprot->writeStructEnd();
  return xfer;
}

void swap(TTopicRegistration &a, TTopicRegistration &b) {
  using ::std::swap;
  swap(a.topic_name, b.topic_name);
  swap(a.is_transient, b.is_transient);
}

const char* TRegisterSubscriberRequest::ascii_fingerprint = "79FBAF663F4F9AC94F2386BD4840E86A";
const uint8_t TRegisterSubscriberRequest::binary_fingerprint[16] = {0x79,0xFB,0xAF,0x66,0x3F,0x4F,0x9A,0xC9,0x4F,0x23,0x86,0xBD,0x48,0x40,0xE8,0x6A};

uint32_t TRegisterSubscriberRequest::read(::apache::thrift::protocol::TProtocol* iprot) {

  uint32_t xfer = 0;
  std::string fname;
  ::apache::thrift::protocol::TType ftype;
  int16_t fid;

  xfer += iprot->readStructBegin(fname);

  using ::apache::thrift::protocol::TProtocolException;

  bool isset_protocol_version = false;
  bool isset_subscriber_id = false;
  bool isset_subscriber_location = false;
  bool isset_topic_registrations = false;

  while (true)
  {
    xfer += iprot->readFieldBegin(fname, ftype, fid);
    if (ftype == ::apache::thrift::protocol::T_STOP) {
      break;
    }
    switch (fid)
    {
      case 1:
        if (ftype == ::apache::thrift::protocol::T_I32) {
          int32_t ecast24;
          xfer += iprot->readI32(ecast24);
          this->protocol_version = (StateStoreServiceVersion::type)ecast24;
          isset_protocol_version = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 2:
        if (ftype == ::apache::thrift::protocol::T_STRING) {
          xfer += iprot->readString(this->subscriber_id);
          isset_subscriber_id = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 3:
        if (ftype == ::apache::thrift::protocol::T_STRUCT) {
          xfer += this->subscriber_location.read(iprot);
          isset_subscriber_location = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 4:
        if (ftype == ::apache::thrift::protocol::T_LIST) {
          {
            this->topic_registrations.clear();
            uint32_t _size25;
            ::apache::thrift::protocol::TType _etype28;
            xfer += iprot->readListBegin(_etype28, _size25);
            this->topic_registrations.resize(_size25);
            uint32_t _i29;
            for (_i29 = 0; _i29 < _size25; ++_i29)
            {
              xfer += this->topic_registrations[_i29].read(iprot);
            }
            xfer += iprot->readListEnd();
          }
          isset_topic_registrations = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      default:
        xfer += iprot->skip(ftype);
        break;
    }
    xfer += iprot->readFieldEnd();
  }

  xfer += iprot->readStructEnd();

  if (!isset_protocol_version)
    throw TProtocolException(TProtocolException::INVALID_DATA);
  if (!isset_subscriber_id)
    throw TProtocolException(TProtocolException::INVALID_DATA);
  if (!isset_subscriber_location)
    throw TProtocolException(TProtocolException::INVALID_DATA);
  if (!isset_topic_registrations)
    throw TProtocolException(TProtocolException::INVALID_DATA);
  return xfer;
}

uint32_t TRegisterSubscriberRequest::write(::apache::thrift::protocol::TProtocol* oprot) const {
  uint32_t xfer = 0;
  uint32_t fcnt = 0;
  xfer += oprot->writeStructBegin("TRegisterSubscriberRequest");

  ++fcnt;
  xfer += oprot->writeFieldBegin("protocol_version", ::apache::thrift::protocol::T_I32, 1);
  xfer += oprot->writeI32((int32_t)this->protocol_version);
  xfer += oprot->writeFieldEnd();

  ++fcnt;
  xfer += oprot->writeFieldBegin("subscriber_id", ::apache::thrift::protocol::T_STRING, 2);
  xfer += oprot->writeString(this->subscriber_id);
  xfer += oprot->writeFieldEnd();

  ++fcnt;
  xfer += oprot->writeFieldBegin("subscriber_location", ::apache::thrift::protocol::T_STRUCT, 3);
  xfer += this->subscriber_location.write(oprot);
  xfer += oprot->writeFieldEnd();

  ++fcnt;
  xfer += oprot->writeFieldBegin("topic_registrations", ::apache::thrift::protocol::T_LIST, 4);
  {
    xfer += oprot->writeListBegin(::apache::thrift::protocol::T_STRUCT, static_cast<uint32_t>(this->topic_registrations.size()));
    std::vector<TTopicRegistration> ::const_iterator _iter30;
    for (_iter30 = this->topic_registrations.begin(); _iter30 != this->topic_registrations.end(); ++_iter30)
    {
      xfer += (*_iter30).write(oprot);
    }
    xfer += oprot->writeListEnd();
  }
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldStop();
  xfer += oprot->writeStructEnd();
  return xfer;
}

void swap(TRegisterSubscriberRequest &a, TRegisterSubscriberRequest &b) {
  using ::std::swap;
  swap(a.protocol_version, b.protocol_version);
  swap(a.subscriber_id, b.subscriber_id);
  swap(a.subscriber_location, b.subscriber_location);
  swap(a.topic_registrations, b.topic_registrations);
}

const char* TRegisterSubscriberResponse::ascii_fingerprint = "5D172D269EB9D48C37F2702186BA51B0";
const uint8_t TRegisterSubscriberResponse::binary_fingerprint[16] = {0x5D,0x17,0x2D,0x26,0x9E,0xB9,0xD4,0x8C,0x37,0xF2,0x70,0x21,0x86,0xBA,0x51,0xB0};

uint32_t TRegisterSubscriberResponse::read(::apache::thrift::protocol::TProtocol* iprot) {

  uint32_t xfer = 0;
  std::string fname;
  ::apache::thrift::protocol::TType ftype;
  int16_t fid;

  xfer += iprot->readStructBegin(fname);

  using ::apache::thrift::protocol::TProtocolException;

  bool isset_status = false;

  while (true)
  {
    xfer += iprot->readFieldBegin(fname, ftype, fid);
    if (ftype == ::apache::thrift::protocol::T_STOP) {
      break;
    }
    switch (fid)
    {
      case 1:
        if (ftype == ::apache::thrift::protocol::T_STRUCT) {
          xfer += this->status.read(iprot);
          isset_status = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      default:
        xfer += iprot->skip(ftype);
        break;
    }
    xfer += iprot->readFieldEnd();
  }

  xfer += iprot->readStructEnd();

  if (!isset_status)
    throw TProtocolException(TProtocolException::INVALID_DATA);
  return xfer;
}

uint32_t TRegisterSubscriberResponse::write(::apache::thrift::protocol::TProtocol* oprot) const {
  uint32_t xfer = 0;
  uint32_t fcnt = 0;
  xfer += oprot->writeStructBegin("TRegisterSubscriberResponse");

  ++fcnt;
  xfer += oprot->writeFieldBegin("status", ::apache::thrift::protocol::T_STRUCT, 1);
  xfer += this->status.write(oprot);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldStop();
  xfer += oprot->writeStructEnd();
  return xfer;
}

void swap(TRegisterSubscriberResponse &a, TRegisterSubscriberResponse &b) {
  using ::std::swap;
  swap(a.status, b.status);
}

const char* TUpdateStateRequest::ascii_fingerprint = "811E0A6DBF85758EE37F39E46F7E5CF6";
const uint8_t TUpdateStateRequest::binary_fingerprint[16] = {0x81,0x1E,0x0A,0x6D,0xBF,0x85,0x75,0x8E,0xE3,0x7F,0x39,0xE4,0x6F,0x7E,0x5C,0xF6};

uint32_t TUpdateStateRequest::read(::apache::thrift::protocol::TProtocol* iprot) {

  uint32_t xfer = 0;
  std::string fname;
  ::apache::thrift::protocol::TType ftype;
  int16_t fid;

  xfer += iprot->readStructBegin(fname);

  using ::apache::thrift::protocol::TProtocolException;

  bool isset_protocol_version = false;
  bool isset_topic_deltas = false;

  while (true)
  {
    xfer += iprot->readFieldBegin(fname, ftype, fid);
    if (ftype == ::apache::thrift::protocol::T_STOP) {
      break;
    }
    switch (fid)
    {
      case 1:
        if (ftype == ::apache::thrift::protocol::T_I32) {
          int32_t ecast31;
          xfer += iprot->readI32(ecast31);
          this->protocol_version = (StateStoreServiceVersion::type)ecast31;
          isset_protocol_version = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 2:
        if (ftype == ::apache::thrift::protocol::T_MAP) {
          {
            this->topic_deltas.clear();
            uint32_t _size32;
            ::apache::thrift::protocol::TType _ktype33;
            ::apache::thrift::protocol::TType _vtype34;
            xfer += iprot->readMapBegin(_ktype33, _vtype34, _size32);
            uint32_t _i36;
            for (_i36 = 0; _i36 < _size32; ++_i36)
            {
              std::string _key37;
              xfer += iprot->readString(_key37);
              TTopicDelta& _val38 = this->topic_deltas[_key37];
              xfer += _val38.read(iprot);
            }
            xfer += iprot->readMapEnd();
          }
          isset_topic_deltas = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      default:
        xfer += iprot->skip(ftype);
        break;
    }
    xfer += iprot->readFieldEnd();
  }

  xfer += iprot->readStructEnd();

  if (!isset_protocol_version)
    throw TProtocolException(TProtocolException::INVALID_DATA);
  if (!isset_topic_deltas)
    throw TProtocolException(TProtocolException::INVALID_DATA);
  return xfer;
}

uint32_t TUpdateStateRequest::write(::apache::thrift::protocol::TProtocol* oprot) const {
  uint32_t xfer = 0;
  uint32_t fcnt = 0;
  xfer += oprot->writeStructBegin("TUpdateStateRequest");

  ++fcnt;
  xfer += oprot->writeFieldBegin("protocol_version", ::apache::thrift::protocol::T_I32, 1);
  xfer += oprot->writeI32((int32_t)this->protocol_version);
  xfer += oprot->writeFieldEnd();

  ++fcnt;
  xfer += oprot->writeFieldBegin("topic_deltas", ::apache::thrift::protocol::T_MAP, 2);
  {
    xfer += oprot->writeMapBegin(::apache::thrift::protocol::T_STRING, ::apache::thrift::protocol::T_STRUCT, static_cast<uint32_t>(this->topic_deltas.size()));
    std::map<std::string, TTopicDelta> ::const_iterator _iter39;
    for (_iter39 = this->topic_deltas.begin(); _iter39 != this->topic_deltas.end(); ++_iter39)
    {
      xfer += oprot->writeString(_iter39->first);
      xfer += _iter39->second.write(oprot);
    }
    xfer += oprot->writeMapEnd();
  }
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldStop();
  xfer += oprot->writeStructEnd();
  return xfer;
}

void swap(TUpdateStateRequest &a, TUpdateStateRequest &b) {
  using ::std::swap;
  swap(a.protocol_version, b.protocol_version);
  swap(a.topic_deltas, b.topic_deltas);
}

const char* TUpdateStateResponse::ascii_fingerprint = "29927C815DE049DEA54ECFF2B3284EF8";
const uint8_t TUpdateStateResponse::binary_fingerprint[16] = {0x29,0x92,0x7C,0x81,0x5D,0xE0,0x49,0xDE,0xA5,0x4E,0xCF,0xF2,0xB3,0x28,0x4E,0xF8};

uint32_t TUpdateStateResponse::read(::apache::thrift::protocol::TProtocol* iprot) {

  uint32_t xfer = 0;
  std::string fname;
  ::apache::thrift::protocol::TType ftype;
  int16_t fid;

  xfer += iprot->readStructBegin(fname);

  using ::apache::thrift::protocol::TProtocolException;

  bool isset_status = false;
  bool isset_topic_updates = false;

  while (true)
  {
    xfer += iprot->readFieldBegin(fname, ftype, fid);
    if (ftype == ::apache::thrift::protocol::T_STOP) {
      break;
    }
    switch (fid)
    {
      case 1:
        if (ftype == ::apache::thrift::protocol::T_STRUCT) {
          xfer += this->status.read(iprot);
          isset_status = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 2:
        if (ftype == ::apache::thrift::protocol::T_LIST) {
          {
            this->topic_updates.clear();
            uint32_t _size40;
            ::apache::thrift::protocol::TType _etype43;
            xfer += iprot->readListBegin(_etype43, _size40);
            this->topic_updates.resize(_size40);
            uint32_t _i44;
            for (_i44 = 0; _i44 < _size40; ++_i44)
            {
              xfer += this->topic_updates[_i44].read(iprot);
            }
            xfer += iprot->readListEnd();
          }
          isset_topic_updates = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      default:
        xfer += iprot->skip(ftype);
        break;
    }
    xfer += iprot->readFieldEnd();
  }

  xfer += iprot->readStructEnd();

  if (!isset_status)
    throw TProtocolException(TProtocolException::INVALID_DATA);
  if (!isset_topic_updates)
    throw TProtocolException(TProtocolException::INVALID_DATA);
  return xfer;
}

uint32_t TUpdateStateResponse::write(::apache::thrift::protocol::TProtocol* oprot) const {
  uint32_t xfer = 0;
  uint32_t fcnt = 0;
  xfer += oprot->writeStructBegin("TUpdateStateResponse");

  ++fcnt;
  xfer += oprot->writeFieldBegin("status", ::apache::thrift::protocol::T_STRUCT, 1);
  xfer += this->status.write(oprot);
  xfer += oprot->writeFieldEnd();

  ++fcnt;
  xfer += oprot->writeFieldBegin("topic_updates", ::apache::thrift::protocol::T_LIST, 2);
  {
    xfer += oprot->writeListBegin(::apache::thrift::protocol::T_STRUCT, static_cast<uint32_t>(this->topic_updates.size()));
    std::vector<TTopicUpdate> ::const_iterator _iter45;
    for (_iter45 = this->topic_updates.begin(); _iter45 != this->topic_updates.end(); ++_iter45)
    {
      xfer += (*_iter45).write(oprot);
    }
    xfer += oprot->writeListEnd();
  }
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldStop();
  xfer += oprot->writeStructEnd();
  return xfer;
}

void swap(TUpdateStateResponse &a, TUpdateStateResponse &b) {
  using ::std::swap;
  swap(a.status, b.status);
  swap(a.topic_updates, b.topic_updates);
}

} // namespace
 /*
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
 *
 * Copyright 2020 RDK Management
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
 
#pragma once

#include "Module.h"
#include "Portability.h"
#include "Netlink.h"
#include "NodeId.h"
#include "Portability.h"
#include "SocketPort.h"

namespace WPEFramework {
namespace Core {

    class EXTERNAL AdapterObserver {
    public:
        struct EXTERNAL INotification {
            virtual ~INotification() = default;

            virtual void Event(const string&) = 0;
        };

    public:
        AdapterObserver() = delete;
        AdapterObserver(const AdapterObserver&) = delete;
        AdapterObserver& operator=(const AdapterObserver&) = delete;

        AdapterObserver(INotification* callback);
        ~AdapterObserver();

    public:
        uint32_t Open();
        uint32_t Close();

    private:
        INotification* _callback;
    };

#ifdef __WINDOWS__

    class EXTERNAL IPV4AddressIterator {
    public:
        inline IPV4AddressIterator()
            : _adapter(static_cast<uint16_t>(~0))
            , _index(static_cast<uint16_t>(~0))
            , _section1(0)
            , _section2(0)
            , _section3(0)
        {
        }
        IPV4AddressIterator(const uint16_t adapter);
        inline IPV4AddressIterator(const IPV4AddressIterator& copy)
            : _adapter(copy._adapter)
            , _index(copy._index)
            , _section1(copy._section1)
            , _section2(copy._section2)
            , _section3(copy._section3)
        {
        }
        inline ~IPV4AddressIterator()
        {
        }

        inline IPV4AddressIterator& operator=(const IPV4AddressIterator& RHS)
        {
            _adapter = RHS._adapter;
            _index = RHS._index;

            _section1 = RHS._section1;
            _section2 = RHS._section2;
            _section3 = RHS._section3;

            return (*this);
        }

    public:
        inline bool IsValid() const
        {
            return (_index < Count());
        }
        inline void Reset()
        {
            _index = static_cast<uint16_t>(~0);
        }
        inline bool Next()
        {
            if (_index == static_cast<uint16_t>(~0)) {
                _index = 0;
            } else if (_index < Count()) {
                _index++;
            }

            return (IsValid());
        }
        inline uint16_t Count() const
        {
            return (_section3);
        }
        IPNode Address() const;

    private:
        uint16_t _adapter;
        uint16_t _index;
        uint16_t _section1;
        uint16_t _section2;
        uint16_t _section3;
    };

    class EXTERNAL IPV6AddressIterator {
    public:
        inline IPV6AddressIterator()
            : _adapter(static_cast<uint16_t>(~0))
            , _index(static_cast<uint16_t>(~0))
            , _section1(0)
            , _section2(0)
            , _section3(0)
        {
        }
        IPV6AddressIterator(const uint16_t adapter);
        inline IPV6AddressIterator(const IPV6AddressIterator& copy)
            : _adapter(copy._adapter)
            , _index(copy._index)
            , _section1(copy._section1)
            , _section2(copy._section2)
            , _section3(copy._section3)
        {
        }
        inline ~IPV6AddressIterator()
        {
        }

        inline IPV6AddressIterator& operator=(const IPV6AddressIterator& RHS)
        {
            _adapter = RHS._adapter;
            _index = RHS._index;
            _section1 = RHS._section1;
            _section2 = RHS._section2;
            _section3 = RHS._section3;
            return (*this);
        }

    public:
        inline bool IsValid() const
        {
            return (_index < Count());
        }
        inline void Reset()
        {
            _index = static_cast<uint16_t>(~0);
        }
        inline bool Next()
        {
            if (_index == static_cast<uint16_t>(~0)) {
                _index = 0;
            } else if (_index < Count()) {
                _index++;
            }

            return (IsValid());
        }
        inline uint16_t Count() const
        {
            return (_section3);
        }
        IPNode Address() const;

    private:
        uint16_t _adapter;
        uint16_t _index;
        uint16_t _section1;
        uint16_t _section2;
        uint16_t _section3;
    };


    class EXTERNAL AdapterIterator {
    public:
        inline AdapterIterator()
            : _index(static_cast<uint16_t>(~0))
        {
        }
        inline AdapterIterator(const string& name)
            : _index(static_cast<uint16_t>(~0))
        {
            while ((Next() == true) && (Name() != name)) /* intentionally left blank */
                ;

            if (IsValid() == false) {
                Reset();
            }
        }
        inline AdapterIterator(const AdapterIterator& copy)
            : _index(copy._index)
        {
        }
        inline ~AdapterIterator()
        {
        }

        inline AdapterIterator& operator=(const AdapterIterator& RHS)
        {
            _index = RHS._index;
            return (*this);
        }

    public:
        inline uint16_t Index() const
        {
            return (_index);
        }
        inline bool IsValid() const
        {
            return (_index < Count());
        }
        inline void Reset()
        {
            _index = static_cast<uint16_t>(~0);
        }
        inline bool Next()
        {
            if (_index == static_cast<uint16_t>(~0)) {
                _index = 0;
            } else if (_index < Count()) {
                _index++;
            }

            return (IsValid());
        }
        inline IPV4AddressIterator IPV4Addresses() const
        {
            return (IPV4AddressIterator(_index));
        }
        inline IPV6AddressIterator IPV6Addresses() const
        {
            return (IPV6AddressIterator(_index));
        }
        NodeId Broadcast() const;
        bool IsUp() const;
        bool IsRunning() const;
        uint32_t Up(const bool enabled);

        uint16_t Count() const;
        string Name() const;

        bool HasMAC() const;

        string MACAddress(const char delimiter) const;
        void MACAddress(uint8_t buffer[], const uint8_t length) const;

        uint32_t Add(const IPNode& address);
        uint32_t Delete(const IPNode& address);
        uint32_t Gateway(const IPNode& network, const NodeId& gateway);
        uint32_t Broadcast(const Core::NodeId& address);

    private:
        uint16_t _index;
    };

#else

    class EXTERNAL IPV4AddressIterator {
    public:
        inline IPV4AddressIterator()
            : _reset(true)
            , _list()
            , _index() {
        }
        IPV4AddressIterator(const std::list<IPNode>& container) 
            : _reset(true)
            , _list(container)
            , _index(_list.begin()) {
        }
        inline IPV4AddressIterator(const IPV4AddressIterator& copy)
            : _reset(true)
            , _list(copy._list)
            , _index(_list.begin()) {
        }
        inline ~IPV4AddressIterator() = default;

        inline IPV4AddressIterator& operator=(const IPV4AddressIterator& RHS)
        {
            _reset = RHS._reset;
            _list = RHS._list;
            if (RHS._index != RHS._list.end()) {
                _index = find(_list.begin(), _list.end(), *(RHS._index));
            } else {
                _index = _list.begin();
            }

            return (*this);
        }

    public:
        inline bool IsValid() const
        {
            return ((_reset != true) && (_index != _list.end()));
        }
        inline void Reset()
        {
            _reset = true;
            _index = _list.begin();
        }
        inline bool Next()
        {
            if (_reset == true) {
                _reset = false;
            } else if (_index != _list.end()) {
                _index++;
            }

            return (_index != _list.end());
        }
        inline uint16_t Count() const
        {
            return (_list.size());
        }
        IPNode Address() const {
            ASSERT (IsValid() == true);
            return (*_index);
        }

    private:
        bool _reset;
        std::list<IPNode> _list;
        std::list<IPNode>::const_iterator _index;
    };

    using IPV6AddressIterator = IPV4AddressIterator;

    class EXTERNAL Network {
    public:
        Network() = delete;
        Network(const Network&) = delete;
        Network& operator=(const Network&) = delete;

        Network(const uint32_t index, const struct rtattr* iface, const uint32_t length);
        ~Network() = default;

    public:
        inline bool IsValid() const
        {
            return (_index != 0);
        }
        inline uint32_t Id() const
        {
            return (_index);
        }
        inline string Name() const
        {
            SafeSyncType<CriticalSection> scopedLock(_adminLock);

            return (_name);
        }
        inline void MAC(uint8_t buffer[], const uint8_t length) const
        {
            ASSERT(length >= sizeof(_MAC));

            _adminLock.Lock();

            ::memcpy(buffer, _MAC, (length >= sizeof(_MAC) ? sizeof(_MAC) : length));

            _adminLock.Unlock();

            if (length > sizeof(_MAC)) {
                ::memset(&buffer[sizeof(_MAC)], 0, length - sizeof(_MAC));
            }
        }
        inline IPV4AddressIterator IPv4Nodes() const
        {
            SafeSyncType<CriticalSection> scopedLock(_adminLock);

            return (IPV4AddressIterator(_ipv4Nodes));
        }
        inline IPV6AddressIterator IPv6Nodes() const
        {
            SafeSyncType<CriticalSection> scopedLock(_adminLock);

            return (IPV6AddressIterator(_ipv6Nodes));
        }
        inline void Added(const IPNode& address) {
            _adminLock.Lock();

            if (address.Type() == Core::NodeId::TYPE_IPV4) {
                std::list<IPNode>::iterator index (std::find(_ipv4Nodes.begin(), _ipv4Nodes.end(), address));
                if (index == _ipv4Nodes.end()) {
                    _ipv4Nodes.push_back(address);
                }
            }
            else if (address.Type() == Core::NodeId::TYPE_IPV6) {
                std::list<IPNode>::iterator index (std::find(_ipv6Nodes.begin(), _ipv6Nodes.end(), address));
                if (index == _ipv6Nodes.end()) {
                    _ipv6Nodes.push_back(address);
                }
            }
            else {
                TRACE_L1("Network::Added: Unexpected node type: %d", address.Type()); 
            }

            _adminLock.Unlock();
        }
        inline void Removed(const IPNode& address) {

            _adminLock.Lock();

            if (address.Type() == Core::NodeId::TYPE_IPV4) {
                std::list<IPNode>::iterator index (std::find(_ipv4Nodes.begin(), _ipv4Nodes.end(), address));
                if (index != _ipv4Nodes.end()) {
                    _ipv4Nodes.erase(index);
                }
            }
            else if (address.Type() == Core::NodeId::TYPE_IPV6) {
                std::list<IPNode>::iterator index (std::find(_ipv6Nodes.begin(), _ipv6Nodes.end(), address));
                if (index != _ipv6Nodes.end()) {
                    _ipv6Nodes.erase(index);
                }
            }
            else {
                TRACE_L1("Network::Added: Unexpected node type: %d", address.Type()); 
            }

            _adminLock.Unlock();
        }

        bool IsUp() const;
        bool IsRunning() const;
        uint32_t Up(const bool enabled);
        uint32_t Broadcast(const Core::NodeId& address);
        NodeId Broadcast() const;
        uint32_t Add(const IPNode& address);
        uint32_t Delete(const IPNode& address);
        uint32_t Gateway(const IPNode& network, const NodeId& gateway);
        void Update(const struct rtattr* rtatp, const uint16_t length);
        void Addresses();

    private:
        mutable Core::CriticalSection _adminLock;
        const uint32_t _index;
        uint8_t _MAC[6];
        string _name;
        std::list<IPNode> _ipv4Nodes;
        std::list<IPNode> _ipv6Nodes;
        bool _loaded;
    };

    class EXTERNAL AdapterIterator {
    public:
        AdapterIterator();
        AdapterIterator(const string& name);
        AdapterIterator(const AdapterIterator& copy);
        ~AdapterIterator() = default;

        AdapterIterator& operator=(const AdapterIterator& RHS);

    public:
        inline bool IsValid() const
        {
            return ((_reset == false) && (_index != _list.end()));
        }
        inline void Reset()
        {
            _reset = true;
            _index = _list.begin();
        }
        inline bool Next()
        {
            if (_reset == true) {
                _reset = false;
            } else if (_index != _list.end()) {
                _index++;
            }

            return (_index != _list.end());
        }
        inline uint16_t Count() const {
            return (_list.size());
        }

        inline string Name() const {
            ASSERT (IsValid());
            return ((*_index)->Name());
        }
        inline string MACAddress(const char delimiter) const
        {
            uint8_t MAC[6];
            string result;

            ASSERT(IsValid());

            (*_index)->MAC(MAC, sizeof(MAC));

            ConvertMACToString(MAC, sizeof(MAC), delimiter, result);

            return (result);
        }
        inline void MACAddress(uint8_t buffer[], const uint8_t length) const
        {
            ASSERT(IsValid());

            (*_index)->MAC(buffer, length);
        }
        inline IPV4AddressIterator IPV4Addresses() const {
            ASSERT(IsValid());

            return ((*_index)->IPv4Nodes());
        }
        inline IPV6AddressIterator IPV6Addresses() const {
            ASSERT(IsValid());

            return ((*_index)->IPv6Nodes());
        }
        inline bool IsUp() const {
            ASSERT(IsValid());

            return ((*_index)->IsUp());
        }
        inline bool IsRunning() const {
            ASSERT(IsValid());

            return ((*_index)->IsRunning());
        }
        inline uint32_t Up(const bool enabled) {
            ASSERT(IsValid());

            return ((*_index)->Up(enabled));
        }
        inline NodeId Broadcast() const {
            ASSERT(IsValid());

            return ((*_index)->Broadcast());
        }
        inline uint32_t Broadcast(const Core::NodeId& address) {
            ASSERT(IsValid());

            return ((*_index)->Broadcast(address));
        }
        inline uint32_t Add(const IPNode& address) {
            ASSERT(IsValid());

            return ((*_index)->Add(address));
        }
        inline uint32_t Delete(const IPNode& address) {
            ASSERT(IsValid());

            return ((*_index)->Delete(address));
        }
        inline uint32_t Gateway(const IPNode& network, const NodeId& gateway) {
            ASSERT(IsValid());

            return ((*_index)->Gateway(network, gateway));
        }
        bool HasMAC() const;

    private:
        inline void ConvertMACToString(const uint8_t address[], const uint8_t length, const char delimiter, string& output) const
        {
            for (uint8_t i = 0; i < length; i++) {
                // Reason for the low-level approch is performance.
                // In stead of using string operations, we know that each byte exists of 2 nibbles,
                // lets just translate these nibbles to Hexadecimal numbers and add them to the output.
                // This saves a setup of several string manipulation operations.
                uint8_t highNibble = ((address[i] & 0xF0) >> 4);
                uint8_t lowNibble = (address[i] & 0x0F);
                if ((i != 0) && (delimiter != '\0')) {
                    output += delimiter;
                }
                output += static_cast<char>(highNibble + (highNibble >= 10 ? ('A' - 10) : '0'));
                output += static_cast<char>(lowNibble + (lowNibble >= 10 ? ('A' - 10) : '0'));
            }
        }

    private:
        bool _reset;
        std::list<Core::ProxyType<Network> > _list;
        std::list<Core::ProxyType<Network> >::iterator _index;
    };

#endif

}
}

// Copyright (c) 2022 by Apex.AI Inc. All rights reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// SPDX-License-Identifier: Apache-2.0

#include "discovery_monitor.hpp"

namespace discovery
{
ServiceDiscovery& serviceDiscovery()
{
    static ServiceDiscovery instance;
    return instance;
}

Discovery::Discovery()
    : m_discovery(&serviceDiscovery())
{
}

void Discovery::deregisterCallback()
{
    if (m_callback)
    {
        m_listener.detachEvent(*m_discovery, iox::runtime::ServiceDiscoveryEvent::SERVICE_REGISTRY_CHANGED);
    }
    m_callback = nullptr;
}

ServiceContainer Discovery::findService(const iox::cxx::optional<iox::capro::IdString_t>& service,
                                        const iox::cxx::optional<iox::capro::IdString_t>& instance,
                                        const iox::cxx::optional<iox::capro::IdString_t>& event)
{
    return m_discovery->findService(service, instance, event);
}

void Discovery::invokeCallback(ServiceDiscovery* discovery, Discovery* self)
{
    self->m_callback(*discovery);
}

} // namespace discovery
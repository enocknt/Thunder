# If not stated otherwise in this file or this component's license file the
# following copyright and licenses apply:
#
# Copyright 2020 Metrological
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

if(LINUX)
set(TEST_RUNNER_NAME "Thunder_test_tests")

add_executable(${TEST_RUNNER_NAME}
   test_iptestmanager.cpp
   ../IPTestAdministrator.cpp
)

target_link_libraries(${TEST_RUNNER_NAME} 
    ${GTEST_BOTH_LIBRARIES}
    ${CMAKE_THREAD_LIBS_INIT}
    ThunderCore
    ThunderTracing
    ThunderWebSocket
    ThunderCOM
)

install(
    TARGETS ${TEST_RUNNER_NAME}
    DESTINATION ${CMAKE_INSTALL_BINDIR} COMPONENT ${NAMESPACE}_Test)

add_test(${TEST_RUNNER_NAME} ${TEST_RUNNER_NAME})

endif()

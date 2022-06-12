// Copyright 2022 PingCAP, Ltd.
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
#include <Storages/DeltaMerge/DeltaMergeDefines.h>
#include <Storages/DeltaMerge/DeltaTree.h>
#include <Storages/DeltaMerge/DeltaTreeMemory.h>
#include <gtest/gtest.h>

namespace DB::DM
{
TEST(DeltaTreeMemory, GlobalRecycle)
{
    auto global = NumaAwareMemoryHierarchy::GlobalPagePool {};
    auto & list = global.getFreeList();
    auto * a = list.allocate();
    list.recycle(a);
    auto * b = list.allocate();
    list.recycle(b);
    EXPECT_EQ(a, b);
}
TEST(DeltaTreeMemory, BasicAllocation)
{
    auto client = getClient(sizeof(DefaultDeltaTree::Intern), alignof(DefaultDeltaTree::Intern));
    client.deallocate(client.allocate());
}
}
/*
 * @CopyRight: MIT License
 * Copyright (c) 2020 SaeruHikari
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 *  IN THESOFTWARE.
 * 
 * @Description: 
 * @Version: 0.1.0
 * @Autor: SaeruHikari
 * @Date: 2020-03-02 18:44:11
 * @LastEditTime: 2020-03-10 12:19:13
 */
#pragma once
#include "SakuraEngine/Core/CoreMinimal/CoreMinimal.h"

namespace Sakura::Graphics
{
    SInterface CommandContext;
    SInterface Fence;
}

namespace Sakura::Graphics
{
    enum CommandQueueTypes
    {
        COMMAND_QUEUE_GRAPHICS,
        COMMAND_QUEUE_COMPUTE,
        COMMAND_QUEUE_COPY
    };

    SInterface CommandQueue
    {
        virtual void Submit(CommandContext* commandContext,
            Fence* fence = nullptr, Fence* fenceToWait = nullptr) = 0;
        virtual bool WaitFence(Fence* fence, std::uint64_t timeout) = 0;
        virtual void WaitIdle() = 0;
    protected:
        CommandQueue() = default;
    };
}
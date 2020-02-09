/*
 * @Descripttion: CopyRight SaeruHikari: Interface alias of Sakura
 * @Version: 0.1.0
 * @Author: SaeruHikari
 * @Date: 2020-02-02 09:37:28
 * @LastEditors  : SaeruHikari
 * @LastEditTime : 2020-02-09 10:29:32
 */
#pragma once

#ifndef Interface
#define Interface struct
#endif
#ifndef Implements
#define Implements public
#endif

namespace Sakura
{
    // Has V-Table Overhead!
    // Use Macro-defination and SFINAE instead.
    //struct NonCopyble
    //{
    //   NonCopyble() = default;
    //    NonCopyble(const NonCopyble& rhs) = delete;
    //   NonCopyble& operator=(const NonCopyble& rhs) = delete;
    //};

}

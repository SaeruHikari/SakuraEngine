-- add modes: debug and release
add_rules("mode.debug", "mode.release")

set_languages("c99", "c++20")

add_defines("SAKURA_COMPILER_CLANG")
add_cxxflags("/await /D _CRT_SECURE_NO_WARNINGS -DNOMINMAX /MP /EHsc")

add_cxxflags("-Wconstant-logical-operand")

add_includedirs("Extern/include")
add_includedirs("Extern/include/DirectXMath/Inc")
add_includedirs("./")
add_includedirs("SakuraEngine/")


EngineVersion = "0.0.1"
set_version(EngineVersion)
add_defines("SAKURA_CONSOLE_INOUT")
add_defines("SAKURA_DEBUG_EDITOR")
add_defines("SAKURA_DEBUG_GAME")
if is_plat("linux", "macosx") then 
    add_defines("SAKURA_TARGET_PLATFORM_UNIX") 
    if is_plat("linux") then
        add_defines("SAKURA_TARGET_PLATFORM_LINUX") 
    elseif is_plat("macosx") then
        add_defines("SAKURA_TARGET_PLATFORM_OSX") 
    end
elseif is_plat("windows") then
    add_defines("SAKURA_TARGET_PLATFORM_WIN32") 
end

-- Generate Engine Module Metas
--target("Sakura")
    --before_build(function(target)
    --    print("Sakura Engine Version "..target:get("version"))
        --os.exec("python3 SPA/anyToheader.py meta .json SakuraEngine")
        --os.exec("python3 SPA/ModuleCollector.py meta SakuraEngine")
    --end)

function static_lib(targetName, version, ...)
target(targetName)
    set_version(version)
    set_kind("static")
    add_files(...)
end

function shared_lib(targetName, version, ...)
target(targetName)
    set_version(version)
    set_kind("shared")
    add_files(...)
end

function static_module(targetName, version, ...)
    static_lib(targetName, version, ...)
    before_build(function(target)
        os.exec("lua BuildTools/ModuleInfoGen.lua ".."meta "..target:scriptdir().." ./")
    end)
end

function shared_module(targetName, version, ...)
    shared_lib(targetName, version, ...)
    before_build(function(target)
        os.exec("lua BuildTools/ModuleInfoGen.lua ".."meta "..target:scriptdir().." ./")
        for _, includedir in ipairs(target:get("includedirs")) do
            --print(includedir)
        end
    end)
end

includes("SPA")
includes("SakuraEngine")
includes("SPAUnitTest")

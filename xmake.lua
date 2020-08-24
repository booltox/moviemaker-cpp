set_project("moviemake-cpp")
set_version("0.1.0")

add_requires("vcpkg::ffmpeg", {alias = "ffmpeg"})
add_requires("vcpkg::x264", {alias = "x264"})
add_requires("gtest", {optional = true})
-- add_requires("cairo", {optional = true})
-- add_requires("vcpkg::librsvg", {alias = "librsvg", optional = true})

function handle_mode()
    if is_mode("debug") then
        set_symbols("debug")
        set_strip("none")
        set_optimize("none")
        add_defines("DEBUG")
    elseif is_mode("release") then
        set_symbols("none")
        set_strip("all")
        set_optimize("fastest")
    end
end

target("moviemaker-cpp")
    set_kind("static")
    handle_mode()

    -- if you want cairo and png, svg support
    -- add_packages("cairo", "librsvg")
    -- add_defines("USE_CAIRO")

    add_includedirs("include")
    add_packages("ffmpeg", "x264")

    add_files("src/*.cpp")

target("moviemaker-cpp-test")
    set_kind("binary")
    handle_mode()

    add_includedirs("include")
    add_packages("ffmpeg", "x264", "gtest")
    if is_os("windows") then
        add_links("ole32", "Ws2_32", "Secur32", "user32", "Bcrypt")
    end
    add_defines("TESTING")

    -- if you want cairo and png, svg support
    -- add_packages("cairo", "librsvg")
    -- add_defines("USE_CAIRO")

    add_files("src/*.cpp")
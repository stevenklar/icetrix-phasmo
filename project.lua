-- Prepare some dynamic variables
PROJECT = "Phasmophobia"

include "variables.lua"
include "functions.lua"
include "workspace.lua"

project(PROJECT)
    -- 64bit
    kind "SharedLib"

    includeIcetrix()
    includeProject()

    files {
        PROJECT_VENDOR .. "imgui/examples/imgui_impl_win32.*",
        PROJECT_VENDOR .. "imgui/examples/imgui_impl_dx11*",
        PROJECT_VENDOR .. "implot/implot*",
    }
    includedirs(VENDOR_DIR .. "implot")

    libdirs(VENDOR_DIR .. "kiero/minhook/lib")
    includedirs(VENDOR_DIR .. "kiero")
    files {
        -- kiero with minhook
        PROJECT_VENDOR .. "kiero/minhook/src/hde/*",
        PROJECT_VENDOR .. "kiero/minhook/src/*",
        PROJECT_VENDOR .. "kiero/minhook/include/MinHook.*",
        PROJECT_VENDOR .. "kiero/kiero.*",
        PROJECT_VENDOR .. "kiero/examples/imgui/impl/d3d11*",
        PROJECT_VENDOR .. "kiero/examples/imgui/impl/shared.*",
    } 

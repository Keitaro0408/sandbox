#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#define VK_USE_PLATFORM_WIN32_KHR
#define GLFW_INCLUDE_VULKAN
#define GLFW_EXPOSE_NATIVE_WIN32

#include <vector>
#include <array>
#include <cassert>
#include <sstream>
#include <numeric>
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

#include "glm/glm.hpp"

//#include "CubeApp.h"

#pragma comment(lib, "vulkan-1.lib")

const int WindowWidth = 1280, WindowHeight = 720;
const char* AppTitle = "VulkanPractice";

int __stdcall wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
    UNREFERENCED_PARAMETER(lpCmdLine);
    UNREFERENCED_PARAMETER(hPrevInstance);
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, 0);
    auto window = glfwCreateWindow(WindowWidth, WindowHeight, AppTitle, nullptr, nullptr);

    // Vulkan 初期化
    std::vector<const char*> extensions;

    VkApplicationInfo appInfo;
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pEngineName = "test";
    appInfo.pApplicationName = "test";
    appInfo.apiVersion = VK_API_VERSION_1_1;
    appInfo.engineVersion = VK_MAKE_VERSION(1,0,0);

    std::vector<VkExtensionProperties> props;
    {
        uint32_t count = 0;
        
        vkEnumerateInstanceExtensionProperties(nullptr, &count, nullptr);
        props.resize(count);
        vkEnumerateInstanceExtensionProperties(nullptr, &count, props.data());

        for (const auto& v : props)
        {
            extensions.push_back(v.extensionName);
        }
    }

    VkInstanceCreateInfo ci{};
    ci.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    ci.enabledExtensionCount = uint32_t(extensions.size());
    ci.ppEnabledExtensionNames = extensions.data();
    ci.pApplicationInfo = &appInfo;

#ifdef _DEBUG
    const char* layers[] = {"VK_LAYER_LUNARG_standard_validation"};
    ci.enabledLayerCount = 1;
    ci.ppEnabledLayerNames = layers;
#endif
    VkInstance vkInstance;

    // インスタンス生成
    auto result = vkCreateInstance(&ci, nullptr, &vkInstance);
    if (result != VK_SUCCESS)
    {
        DebugBreak();
    }

    while (glfwWindowShouldClose(window) == GLFW_FALSE)
    {
        glfwPollEvents();
    }

    // Vulkan 終了
    glfwTerminate();
    return 0;
}

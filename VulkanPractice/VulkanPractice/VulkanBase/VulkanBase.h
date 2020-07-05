#ifndef VULKAN_BASE
#define VULKAN_BASE

#define VK_USE_PLATFORM_WIN32_KHR
#define GLFW_INCLUDE_VULKAN
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#include <vulkan/vk_layer.h>
#include <vulkan/vulkan_win32.h>

class VulkanBase
{
public:
	VulkanBase() {}
	virtual ~VulkanBase() {}

	void Initialize(const char* appName);
	void Finalize();

private:
	bool CreateDevice();
	bool CreateVkInstance(const char* appName);

	void SelectPhysicalDevice();
	uint32_t SearchGraphicsQueueIndex();

	VkResult		 m_LastResult;
	VkInstance		 m_VkInstance;
	VkDevice		 m_Device;
	VkPhysicalDevice m_physDev;

	VkPhysicalDeviceMemoryProperties m_physMemProps;

};


#endif
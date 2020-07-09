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

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="appName">アプリケーションの名前</param>
	void Initialize(const char* appName);

	/// <summary>
	/// 解放
	/// </summary>
	void Finalize();

private:

	/// <summary>
	/// デバイスの生成
	/// </summary>
	bool CreateDevice();

	/// <summary>
	/// Vulkanインスタンスの生成
	/// </summary>
	/// <param name="appName"></param>
	bool CreateVkInstance(const char* appName);

	/// <summary>
	/// 物理デバイスの選択
	/// </summary>
	void SelectPhysicalDevice();

	bool CreateCommandPool(uint32_t grahicsQueueIndex, VkCommandPool& commandPool);

	/// <summary>
	/// 物理デバイスインデックスの選択
	/// </summary>
	/// <returns>物理デバイスインデックス</returns>
	uint32_t SearchGraphicsQueueIndex();

	VkResult		 m_LastResult;
	VkInstance		 m_VkInstance;
	VkDevice		 m_Device;
	VkQueue			 m_DeviceQueue;
	VkPhysicalDevice m_PhysicalDevice;
	uint32_t		 m_GraphicQueueIndex;
	VkPhysicalDeviceMemoryProperties m_PhysicalMemoryProps;

};


#endif
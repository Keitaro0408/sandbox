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
	/// ������
	/// </summary>
	/// <param name="appName">�A�v���P�[�V�����̖��O</param>
	void Initialize(const char* appName);

	/// <summary>
	/// ���
	/// </summary>
	void Finalize();

private:

	/// <summary>
	/// �f�o�C�X�̐���
	/// </summary>
	bool CreateDevice();

	/// <summary>
	/// Vulkan�C���X�^���X�̐���
	/// </summary>
	/// <param name="appName"></param>
	bool CreateVkInstance(const char* appName);

	/// <summary>
	/// �����f�o�C�X�̑I��
	/// </summary>
	void SelectPhysicalDevice();

	bool CreateCommandPool(uint32_t grahicsQueueIndex, VkCommandPool& commandPool);

	/// <summary>
	/// �����f�o�C�X�C���f�b�N�X�̑I��
	/// </summary>
	/// <returns>�����f�o�C�X�C���f�b�N�X</returns>
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
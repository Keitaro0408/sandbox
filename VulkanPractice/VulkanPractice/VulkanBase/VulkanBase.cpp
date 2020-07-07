#include "VulkanBase.h"
#include <vector>


void VulkanBase::Initialize(const char* appName)
{
	CreateVkInstance(appName);
	SelectPhysicalDevice();
	m_GraphicQueueIndex = SearchGraphicsQueueIndex();


}

void VulkanBase::Finalize()
{
}

bool VulkanBase::CreateDevice()
{
	const float queuePriority = 1.0f;
	VkDeviceQueueCreateInfo info;
	info.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
	info.queueFamilyIndex = m_GraphicQueueIndex;
	info.queueCount = 1;
	info.pQueuePriorities = &queuePriority;

	std::vector<VkExtensionProperties> deviceExProps;
	{
		uint32_t count = 0;
		vkEnumerateDeviceExtensionProperties(m_PhysicalDevice, nullptr, &count, nullptr);
		deviceExProps.resize(count);
		vkEnumerateDeviceExtensionProperties(m_PhysicalDevice, nullptr, &count, deviceExProps.data());
	}

	std::vector<const char*> exNames;
	for (const auto& v : deviceExProps)
	{
		exNames.push_back(v.extensionName);
	}
	VkDeviceCreateInfo ci{};
	ci.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	ci.pQueueCreateInfos = &info;
	ci.queueCreateInfoCount = 1;
	ci.ppEnabledExtensionNames = exNames.data();
	ci.enabledExtensionCount = uint32_t(exNames.size());

	m_LastResult = vkCreateDevice(m_PhysicalDevice, &ci, nullptr, &m_Device);

	vkGetDeviceQueue(m_Device, m_GraphicQueueIndex, 0, &m_DeviceQueue);

	if (m_LastResult != VK_SUCCESS)
	{
		return false;
	}

	return true;
}

bool VulkanBase::CreateVkInstance(const char* appName)
{
	std::vector<const char*> extensions;
	VkApplicationInfo appInfo{};
	appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	appInfo.pApplicationName = appName;
	appInfo.pEngineName = appName;
	appInfo.apiVersion = VK_API_VERSION_1_1;
	appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);

	std::vector<VkExtensionProperties> props;
	{
		uint32_t count = 0;
		vkEnumerateInstanceExtensionProperties(nullptr, &count, nullptr);
		props.resize(count);
		vkEnumerateInstanceExtensionProperties(nullptr, &count, props.data());

		for (const auto& itr : props)
		{
			extensions.push_back(itr.extensionName);
		}
	}

	VkInstanceCreateInfo ci{};
	ci.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	ci.enabledExtensionCount = uint32_t(extensions.size());
	ci.ppEnabledExtensionNames = extensions.data();
	ci.pApplicationInfo = &appInfo;

#ifdef _DEBUG
	// デバッグビルド時には検証レイヤーを有効化
	const char* layers[] = { "VK_LAYER_LUNARG_standard_validation" };
	ci.enabledLayerCount = 1;
	ci.ppEnabledLayerNames = layers;
#endif

	m_LastResult = vkCreateInstance(&ci, nullptr, &m_VkInstance);

	if (m_LastResult != VK_SUCCESS)
	{
		return false;
	}

	return true;
}

void VulkanBase::SelectPhysicalDevice()
{
	uint32_t devCount = 0;
	vkEnumeratePhysicalDevices(m_VkInstance, &devCount, nullptr);
	std::vector<VkPhysicalDevice> physDevs(devCount);
	vkEnumeratePhysicalDevices(m_VkInstance, &devCount, physDevs.data());

	m_PhysicalDevice = physDevs[0];

	vkGetPhysicalDeviceMemoryProperties(m_PhysicalDevice, &m_PhysicalMemoryProps);
}

uint32_t VulkanBase::SearchGraphicsQueueIndex()
{
	uint32_t count;
	vkGetPhysicalDeviceQueueFamilyProperties(m_PhysicalDevice, &count, nullptr);
	std::vector<VkQueueFamilyProperties> props(count);
	vkGetPhysicalDeviceQueueFamilyProperties(m_PhysicalDevice, &count, props.data());

	uint32_t queueIndex = 0;

	for (uint32_t i = 0; i < count; i++)
	{
		if (props[i].queueFlags & VK_QUEUE_GRAPHICS_BIT)
		{
			queueIndex = i;
		}
	}


	return queueIndex;
}

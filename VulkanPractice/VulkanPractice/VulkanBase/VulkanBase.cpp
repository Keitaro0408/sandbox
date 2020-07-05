#include "VulkanBase.h"
#include <vector>


void VulkanBase::Initialize(const char* appName)
{
	CreateVkInstance(appName);
	SelectPhysicalDevice();


}

void VulkanBase::Finalize()
{
}

bool VulkanBase::CreateDevice()
{
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

	m_physDev = physDevs[0];

	vkGetPhysicalDeviceMemoryProperties(m_physDev, &m_physMemProps);
}

uint32_t VulkanBase::SearchGraphicsQueueIndex()
{
	return uint32_t();
}

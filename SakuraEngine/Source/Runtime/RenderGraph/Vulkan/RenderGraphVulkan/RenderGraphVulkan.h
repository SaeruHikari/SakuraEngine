#pragma once
#include "BufferVulkan.h"
#include "TextureVulkan.h"
#include "DeviceVulkan.h"
#include "FenceVulkan.h"
#include "ShaderVulkan.h"
#include "SwapChainVulkan.h"
#include "RenderPipelineVulkan.h"

namespace sakura::graphics::vk
{
	RenderGraphVulkanAPI VkPresentModeKHR translate(EPresentMode present_mode);

	RenderGraphVulkanAPI EPresentMode translate(VkPresentModeKHR present_mode);

	RenderGraphVulkanAPI VkFormat translate(ETextureFormat format);

	RenderGraphVulkanAPI ETextureFormat translate(VkFormat format);

	RenderGraphVulkanAPI VkShaderStageFlagBits translate(EShaderFrequency frequency);

	RenderGraphVulkanAPI VkColorComponentFlags translate(ColorMask mask);

	RenderGraphVulkanAPI VkBlendOp translate(EBlendOp blendOp);

	RenderGraphVulkanAPI VkBlendFactor translate(EBlendFactor blendFactor);

	RenderGraphVulkanAPI VkPolygonMode translate(EPolygonMode polygonMode);

	RenderGraphVulkanAPI VkAttachmentLoadOp translate(ELoadOp op);

	RenderGraphVulkanAPI VkAttachmentStoreOp translate(EStoreOp op);

	RenderGraphVulkanAPI VkBufferUsageFlags translate(EBufferUsage usage);

	RenderGraphVulkanAPI VkPrimitiveTopology translate(EPrimitiveTopology topo);

	RenderGraphVulkanAPI VkVertexInputRate translate(VertexLayout::Frequency freq);

	RenderGraphVulkanAPI VkFormat translate(EVertexFormat format);

	RenderGraphVulkanAPI VkDescriptorType translate(BindingLayout::EType type);

	const bool bEnableValidationLayers = false;

	// cn: 尼強哈陪侭俶勣議恷弌制婢鹿栽.
	// en: The minimum set of extensions required to start the engine.
	// jp: エンジンをランチするために駅勣なエクステンション-セット.
	FORCEINLINE const std::vector<const char*> basic_extentions()
	{
		std::vector<const char*> res = {
#ifdef SAKURA_TARGET_PLATFORM_WIN
				VK_KHR_WIN32_SURFACE_EXTENSION_NAME,
#endif
				VK_KHR_SURFACE_EXTENSION_NAME
		};
		if (bEnableValidationLayers)
		{
			res.emplace_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
		}
		return res;
	}

	// cn: 性軟 physics device 斤�麕�勣箔議恷弌譜姥制婢鹿栽.
	// en: The minimum set of device extensions required by the physics device object.
	// jp: 麗尖デバイスオブジェクトによって駅勣とされるデバイス-エクステンションの恷弌鹿栽.
	const std::vector<const char*> basic_device_exts =
	{

	};

	// cn: 性軟 main device 斤�麕�勣箔議恷弌譜姥制婢鹿栽.
	// en: The minimum set of device extensions required by the main device object.
	// jp: メイン-デバイスオブジェクトによって駅勣とされるデバイス-エクステンションの恷弌鹿栽.
	const std::vector<const char*> main_device_exts =
	{
		VK_KHR_SWAPCHAIN_EXTENSION_NAME
	};

	const std::vector<const char*> validationLayers = {
		"VK_LAYER_KHRONOS_validation"
	};
}
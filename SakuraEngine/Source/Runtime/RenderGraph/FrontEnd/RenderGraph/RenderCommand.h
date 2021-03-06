﻿#pragma once
#include "RenderGraph/RenderGraphCore.h"
#include <optional>

namespace sakura::graphics
{
    struct RenderCommand
    {
        virtual ~RenderCommand() = default;
        virtual ERenderCommandType type() const = 0;
    };

    template<ERenderCommandType CommandType, uint32_t QueueType>
    struct RenderCommandTyped : public RenderCommand
    {
        static const ERenderCommandType command_type = CommandType;
        static const uint8_t queue_type = QueueType;
        ERenderCommandType type() const final override { return CommandType; }
        RenderCommandTyped() { }
    };


    struct RenderCommandCopyTextureToTexture final
        : public RenderCommandTyped<ERenderCommandType::copy_texture_to_texture, ERenderQueueType::QueueTypeAll>
    {
        GpuTextureHandle src;
        TextureSlice src_slice;
        GpuTextureHandle dst;
        TextureSlice dst_slice;
    	extent3d copy_size = {0, 0, 0};

    	// TODO
    	// cn: 不给出origin和copy_size的情形下, 默认从[0,0,0]的origin拷贝source texture大小到dest上.
    	// en: If origin and copy_size given, copy texture size to destination from the origin of [0,0,0] by default.
    	// jp: originとcopy_sizeが指定されている場合、デフォルトで[0,0,0]の起点からデスティネーションにテクスチャサイズをコピーする.
        // TODO

        RenderCommandCopyTextureToTexture(GpuTextureHandle source, GpuTextureHandle destination, extent3d copy_size, uint32_t mip_level = 1);
        RenderCommandCopyTextureToTexture(GpuTextureHandle source, TextureSlice src_slice,
            TextureSlice dst_slice, GpuTextureHandle destination, extent3d copy_size);
    };

    struct RenderCommandCopyTextureToBuffer final
        : public RenderCommandTyped<ERenderCommandType::copy_texture_to_buffer, ERenderQueueType::QueueTypeAll>
    {
        TextureSlice src_slice;
        GpuTextureHandle src;
        GpuBufferHandle dst;
        TextureDataLayout dst_layout;
        extent3d copy_size = { 0, 0, 0 };
    	
        RenderCommandCopyTextureToBuffer(GpuTextureHandle src, TextureSlice src_slice, GpuBufferHandle dest, TextureDataLayout dst_layout, extent3d copy_size);
    };
	
    struct RenderCommandCopyBufferToBuffer final
        : public RenderCommandTyped<ERenderCommandType::copy_buffer_to_buffer, ERenderQueueType::QueueTypeAll>
    {
        GpuBufferHandle src;
        GpuBufferHandle dst;
        uint64_t src_offset = 0;
        uint64_t dst_offset = 0;
        uint64_t copy_size = 0;

        RenderCommandCopyBufferToBuffer(GpuBufferHandle src, uint64_t src_offset,
            GpuBufferHandle dst, uint64_t dst_offset, uint64_t copy_size);
    };

    struct RenderCommandCopyBufferToTexture final
        : public RenderCommandTyped<ERenderCommandType::copy_buffer_to_texture, ERenderQueueType::QueueTypeAll>
    {
        TextureDataLayout layout;
        GpuBufferHandle src;
        TextureSlice dst_slice;
        GpuTextureHandle dst;
        extent3d copy_size;

        RenderCommandCopyBufferToTexture(GpuBufferHandle src, GpuTextureHandle dst, TextureSlice dst_slice,
            TextureDataLayout layout, extent3d copy_size);
    };
	
    struct RenderCommandDispatch final
        : public RenderCommandTyped<ERenderCommandType::dispatch, ERenderQueueType::Compute>
    {

    };

    struct RenderCommandBeginRenderPass final
        : public RenderCommandTyped<ERenderCommandType::begin_render_pass, ERenderQueueType::Graphics>
    {
        RenderCommandBeginRenderPass(
            RenderPipelineHandle pipeline, const Attachment& attachment, const DepthStencil& depth_stencil = {});
        RenderPipelineHandle pipeline = RenderGraphId::UNINITIALIZED;
        Attachment attachments;
        DepthStencil depth_stencil;
    };

    struct RenderCommandEndRenderPass final
        : public RenderCommandTyped<ERenderCommandType::end_render_pass, ERenderQueueType::Graphics>
    {
        RenderCommandEndRenderPass() = default;
    };

    struct RenderCommandUpdateBinding final
        : public RenderCommandTyped<ERenderCommandType::update_binding, ERenderQueueType::Graphics>
    {
        RenderCommandUpdateBinding(const Binding& binding) noexcept;

        Binding binder;
    };

    struct RenderCommandFence final
        : public RenderCommandTyped<ERenderCommandType::fence, ERenderQueueType::QueueTypeAll>
    {
    	
    };

    struct RenderCommandSetScissorRect final
        : public RenderCommandTyped<ERenderCommandType::set_scissor_rect, ERenderQueueType::Graphics>
    {
        RenderCommandSetScissorRect(uint32 x, uint32 y, uint32 width, uint32 height) noexcept;

        uint32 x;
        uint32 y;
        uint32 width;
        uint32 height;
    };

    struct RenderCommandSetVB final
        : public RenderCommandTyped<ERenderCommandType::set_vbs, ERenderQueueType::Graphics>
    {
        GpuBufferHandle vertex_buffer;
        size_t stride = 0;
        size_t offset = 0;
        uint32_t slot = 0;
        
        RenderCommandSetVB(const uint32_t slot, const GpuBufferHandle handle, const size_t offset = 0, const size_t stride = 0);
    };

    struct RenderCommandSetIB final
        : public RenderCommandTyped<ERenderCommandType::set_ib, ERenderQueueType::Graphics>
    {
        size_t offset = 0;
        size_t stride = 0;
        EIndexFormat format = EIndexFormat::UINT16;
        GpuBufferHandle index_buffer;

        RenderCommandSetIB(GpuBufferHandle index_buffer, 
            EIndexFormat format = EIndexFormat::UINT16, size_t offset = 0, size_t stride = 0);
    };

    struct RenderCommandDrawIndirect final
		: public RenderCommandTyped<ERenderCommandType::draw_indirect, ERenderQueueType::Graphics>
	{
		GpuBufferHandle indirect_buffer;
		size_t offset;
	};

    struct RenderCommandDraw final
        : public RenderCommandTyped<ERenderCommandType::draw, ERenderQueueType::Graphics>
    {
        uint32 index_count = 0;
        uint32 instance_count = 1;
        uint32 first_index = 0;
        uint32 base_vertex = 0;
        uint32 first_instance = 0;
        bool instance_draw = false;

        RenderCommandDraw(const uint32 index_count,
            const uint32 instance_count = 1, const uint32 first_index = 0, uint32 baseVertex = 0, uint32 firstInstance = 0);
    };

    FORCEINLINE RenderCommandCopyTextureToTexture::RenderCommandCopyTextureToTexture(GpuTextureHandle source,
	    GpuTextureHandle destination, extent3d copy_size, uint32_t mip_level)
		:src(source), src_slice(TextureSlice{ETextureAspect::All, mip_level, {0, 0, 0}}),
		dst(destination), dst_slice(TextureSlice{ETextureAspect::All, mip_level, { 0, 0, 0 }})
    {
    	
    }

    FORCEINLINE RenderCommandCopyTextureToTexture::RenderCommandCopyTextureToTexture(GpuTextureHandle source,
	    TextureSlice src_slice, TextureSlice dst_slice, GpuTextureHandle destination, extent3d copy_size)
		:src(source), src_slice(src_slice), dst(destination), dst_slice(dst_slice), copy_size(copy_size)
    {
    	
    }

    FORCEINLINE RenderCommandCopyTextureToBuffer::RenderCommandCopyTextureToBuffer(GpuTextureHandle src,
	    TextureSlice src_slice, GpuBufferHandle dest, TextureDataLayout unpack_layout, extent3d copy_size)
		:src(src), src_slice(src_slice), dst(dest), dst_layout(unpack_layout), copy_size(copy_size)
    {
    	
    }

    FORCEINLINE RenderCommandCopyBufferToBuffer::RenderCommandCopyBufferToBuffer(
        GpuBufferHandle src, uint64_t src_offset, GpuBufferHandle dst, uint64_t dst_offset, uint64_t copy_size)
	    :src(src), src_offset(src_offset), dst(dst), dst_offset(dst_offset), copy_size(copy_size)
	{
    	
    }

    FORCEINLINE RenderCommandCopyBufferToTexture::RenderCommandCopyBufferToTexture(GpuBufferHandle src, 
        GpuTextureHandle dst, TextureSlice dst_slice, TextureDataLayout layout, extent3d copy_size)
		:src(src), dst(dst), dst_slice(dst_slice), layout(layout), copy_size(copy_size)
    {
    	
    }

    FORCEINLINE RenderCommandBeginRenderPass::RenderCommandBeginRenderPass(
        RenderPipelineHandle ppl, const Attachment& att, const DepthStencil& ds)
        :pipeline(ppl), attachments(att), depth_stencil(ds)
    {

    }

    FORCEINLINE RenderCommandSetScissorRect::RenderCommandSetScissorRect(
        uint32 _x, uint32 _y, uint32 _width, uint32 _height) noexcept
        :x(_x), y(_y), width(_width), height(_height)
    {

    }

    FORCEINLINE RenderCommandUpdateBinding::RenderCommandUpdateBinding(const Binding& binding) noexcept
        :binder(binding)
    {

    }
	
    FORCEINLINE RenderCommandSetVB::RenderCommandSetVB(const uint32_t slot_,
        const GpuBufferHandle handle_, const size_t offset_, const size_t stride_)
        : slot(slot_), vertex_buffer(handle_), stride(stride_), offset(offset_)
    {

    }
        
    FORCEINLINE RenderCommandSetIB::RenderCommandSetIB(GpuBufferHandle indexBuffer,
        EIndexFormat format, size_t offset, size_t stride)
        : index_buffer(indexBuffer), format(format), offset(offset), stride(stride)
    {

    }

    FORCEINLINE RenderCommandDraw::RenderCommandDraw(const uint32 index_count,
        const uint32 instanceCount, const uint32 firstIndex, uint32 baseVertex, uint32 firstInstance)
        : instance_draw(true), instance_count(instanceCount), index_count(index_count),
        first_index(firstIndex), base_vertex(baseVertex), first_instance(firstInstance)
    {
      
    }
}


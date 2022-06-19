#pragma once
#include <cstdint>
#include <vector>
#include <string>
#include <Junia/Log.hpp>
#include <functional>

namespace Junia
{
	enum class ShaderDataType : uint8_t
	{
		None = 0,
		Float, Float2, Float3, Float4,
		Mat3, Mat4,
		Int, Int2, Int3, Int4,
		Bool
	};

	static uint32_t ShaderDataTypeSize(ShaderDataType type)
	{
		switch (type)
		{
		case ShaderDataType::Float:  return 4;
		case ShaderDataType::Float2: return 4 * 2;
		case ShaderDataType::Float3: return 4 * 3;
		case ShaderDataType::Float4: return 4 * 4;
		case ShaderDataType::Mat3:   return 4 * 3 * 3;
		case ShaderDataType::Mat4:   return 4 * 4 * 4;
		case ShaderDataType::Int:    return 4;
		case ShaderDataType::Int2:   return 4 * 2;
		case ShaderDataType::Int3:   return 4 * 3;
		case ShaderDataType::Int4:   return 4 * 4;
		case ShaderDataType::Bool:   return 1;
		default:
			JELOG_BASE_ERROR("Unknown ShaderDataType!");
			return 0;
		}
	}

	struct BufferElement
	{
		std::string name;
		ShaderDataType type = ShaderDataType::None;
		uint32_t size = 0;
		uint32_t offset = 0;
		bool normalized = false;

		BufferElement() { }

		BufferElement(ShaderDataType type, const std::string& name, bool normalized = false)
		: name(name), type(type), size(ShaderDataTypeSize(type)), offset(0), normalized(normalized) { }

		uint32_t GetComponentCount() const
		{
			switch (type)
			{
			case ShaderDataType::Float:  return 1;
			case ShaderDataType::Float2: return 2;
			case ShaderDataType::Float3: return 3;
			case ShaderDataType::Float4: return 4;
			case ShaderDataType::Mat3:   return 3 * 3;
			case ShaderDataType::Mat4:   return 4 * 4;
			case ShaderDataType::Int:    return 1;
			case ShaderDataType::Int2:   return 2;
			case ShaderDataType::Int3:   return 3;
			case ShaderDataType::Int4:   return 4;
			case ShaderDataType::Bool:   return 1;
			default:
				JELOG_BASE_ERROR("Unknown ShaderDataType!");
				return 0;
			}
		}
	};

	class BufferLayout
	{
	public:

		BufferLayout() { }

		BufferLayout(const std::initializer_list<BufferElement>& elements) : elements(elements)
		{
			CalculateOffsetsAndStride();
		}

		uint32_t GetStride() const { return stride; };
		const std::vector<BufferElement>& GetElements() const { return elements; };

	private:
		void CalculateOffsetsAndStride()
		{
			uint32_t offset = 0;
			stride = 0;
			for (auto& element : elements)
			{
				element.offset = offset;
				offset += element.size;
				stride += element.size;
			}
		}

		std::vector<BufferElement> elements;
		uint32_t stride = 0;
	};

	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() = default;

		virtual void Bind()   const = 0;
		virtual void Unbind() const = 0;

		virtual const BufferLayout& GetLayout() const = 0;
		virtual void SetLayout(const BufferLayout& layout) = 0;

		static VertexBuffer* Create(float* vertices, uint32_t size);
	};

	class IndexBuffer
	{
	public:
		virtual ~IndexBuffer() = default;

		virtual void Bind()   const = 0;
		virtual void Unbind() const = 0;

		virtual uint32_t GetCount() const = 0;

		static IndexBuffer* Create(uint32_t* indices, uint32_t count);
	};
}

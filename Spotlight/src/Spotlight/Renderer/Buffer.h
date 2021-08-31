#pragma once

namespace Spotlight
{

	// VERTEX BUFFER LAYOUT ==========================================================

	enum class ShaderDataType
	{
		None = 0, Bool,
		Float, Float2, Float3, Float4,
		Int, Int2, Int3, Int4,
		Byte, Byte2, Byte3, Byte4,
		Mat3, Mat4
	};

	static uint32_t ShaderDataTypeToSize(ShaderDataType type)
	{
		switch (type)
		{
			case ShaderDataType::Bool:   return 1;
			case ShaderDataType::Float:  return 4;
			case ShaderDataType::Float2: return 4 * 2;
			case ShaderDataType::Float3: return 4 * 3;
			case ShaderDataType::Float4: return 4 * 4;
			case ShaderDataType::Int:    return 4;
			case ShaderDataType::Int2:   return 4 * 2;
			case ShaderDataType::Int3:   return 4 * 3;
			case ShaderDataType::Int4:   return 4 * 4;
			case ShaderDataType::Byte:   return 1;
			case ShaderDataType::Byte2:  return 1 * 2;
			case ShaderDataType::Byte3:  return 1 * 3;
			case ShaderDataType::Byte4:  return 1 * 4;
			case ShaderDataType::Mat3:   return 4 * 3 * 3;
			case ShaderDataType::Mat4:   return 4 * 4 * 4;
		}
		SPL_CORE_ASSERT(false, "Specified ShaderDataType unknown!");
		return 0;
	}

	// BUFFER ELEMENT STRUCTURE 

	struct BufferElement
	{
		std::string Name;
		ShaderDataType Type;
		bool Normalized;
		uint32_t Size;
		uint32_t Offset;

		// Default constructor
		BufferElement()
			: Name("Unknown"), Type(ShaderDataType::None), Normalized(false), Size(0), Offset(0) {}
		// Main constructor
		BufferElement(ShaderDataType type, const std::string& name, bool isNormalized = false)
			: Name(name), Type(type), Normalized(isNormalized), Size(ShaderDataTypeToSize(type)), Offset(0) {}

		uint32_t GetComponentCount() const
		{
			switch (Type)
			{
				case ShaderDataType::Bool:   return 1;
				case ShaderDataType::Float:  return 1;
				case ShaderDataType::Float2: return 2;
				case ShaderDataType::Float3: return 3;
				case ShaderDataType::Float4: return 4;
				case ShaderDataType::Int:    return 1;
				case ShaderDataType::Int2:   return 2;
				case ShaderDataType::Int3:   return 3;
				case ShaderDataType::Int4:   return 4;
				case ShaderDataType::Byte:   return 1;
				case ShaderDataType::Byte2:  return 2;
				case ShaderDataType::Byte3:  return 3;
				case ShaderDataType::Byte4:  return 4;
				case ShaderDataType::Mat3:   return 3 * 3;
				case ShaderDataType::Mat4:   return 4 * 4;
			}
			SPL_CORE_ASSERT(false, "Specified ShaderDataType unknown!");
			return 0;
		}
	};

	// BUFFER LAYOUT ====================================================================

	class BufferLayout
	{
	public:
		BufferLayout()
			: m_Elements({BufferElement()}), m_Stride(0) {}
		BufferLayout(const std::initializer_list<BufferElement>& element /*Take in one or multiple arrays of BufferElement as argument*/ )
			: m_Elements(element), m_Stride(0)
		{
			ComputeOffsetAndStride();
		}

		// Getters
		inline const std::vector<BufferElement>& GetAllElements() const { return m_Elements; }
		inline uint32_t GetStride() const { return m_Stride; }
		
		// begin/end iterator functions for for-each statements
		inline std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
		inline std::vector<BufferElement>::iterator end() { return m_Elements.end(); }
		inline std::vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); }
		inline std::vector<BufferElement>::const_iterator end() const { return m_Elements.end(); }
	private:
		void ComputeOffsetAndStride()
		{
			uint32_t offset = 0;
			m_Stride = 0;

			for (auto& element : m_Elements)
			{
				element.Offset = offset;
				offset = element.Size;
				m_Stride += element.Size;
			}
		}
	private:
		std::vector<BufferElement> m_Elements;
		uint32_t m_Stride;	
	};

	// VERTEX BUFFER =================================================================

	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() {}
		
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual const BufferLayout& GetLayout() const = 0;
		virtual void SetLayout(const BufferLayout& layout) = 0;

		static VertexBuffer* Create(float* vertices, uint32_t size);
	};

	// INDEX BUFFER ==================================================================

	class IndexBuffer
	{
	public:
		virtual ~IndexBuffer() {}

		virtual void Bind() const= 0;
		virtual void Unbind() const = 0;

		virtual uint32_t GetCount() const = 0;

		static IndexBuffer* Create(uint32_t* indices, uint32_t count);
	};
}
#include <Junia/Renderer/Mesh.hpp>
#include <Junia/Core/FileSystem.hpp>
#include <stdexcept>
#include <vulkan/vulkan.hpp>
#include "../../Platform/Vulkan/VulkanVertexBuffer.hpp"

#include <iostream>
#include <fstream>
#include <string_view>

namespace Junia {

Mesh::Mesh(const std::string& path, FileType type) {
	if (type == FileType::OBJ) {
		std::ifstream objFile(path);
		if (!objFile.is_open()) throw std::runtime_error("failed to open file");

		std::string line;

		size_t vertexCount = 0, faceCount = 0, uvCount = 0;
		while (std::getline(objFile, line)) {
			std::string_view identifier(line.c_str(), 2);
			if (identifier == "v ") vertexCount++;
			else if (identifier == "f ") faceCount++;
			else if (identifier == "vt") uvCount++;
		}

		vertices.resize(vertexCount);
		indices.resize(faceCount);
		if (uvCount > 0) uvs = std::vector<JMath::Vec2f>(uvCount);

		objFile.clear();
		objFile.seekg(0);

		size_t currVertexId = 0, currFaceId = 0, currUvId = 0;

		while (std::getline(objFile, line)) {
			size_t startLoc = line.find(' ', 0);
			if (startLoc == std::string::npos) continue;
			const char* identifier = line.c_str();
			line.at(startLoc) = '\0';
			startLoc++;

			if (std::strcmp(identifier, "v") == 0) {
				JMath::Vec3f vertex;
				for (uint8_t i = 0; i < 3; i++) {
					size_t spaceLoc = line.find(' ', startLoc);
					if (spaceLoc == std::string::npos) spaceLoc = line.length() - 1;
					else line.at(spaceLoc) = '\0';
					vertex[i] = std::atof(line.c_str() + startLoc);
					startLoc = spaceLoc + 1;
				}
				vertices[currVertexId] = vertex;
				currVertexId++;
			} else if (std::strcmp(identifier, "f") == 0) {
				JMath::Vec3ui face;
				for (uint8_t i = 0; i < 3; i++) {
					size_t spaceLoc = line.find(' ', startLoc);
					if (spaceLoc == std::string::npos) spaceLoc = line.length() - 1;
					else line.at(spaceLoc) = '\0';
					face[i] = std::atol(line.c_str() + startLoc) - 1;
					startLoc = spaceLoc + 1;
				}
				indices[currFaceId] = face;
				currFaceId++;
			} else if (uvs.has_value() && std::strcmp(identifier, "vt") == 0) {
				JMath::Vec2f uv;
				for (uint8_t i = 0; i < 2; i++) {
					size_t spaceLoc = line.find(' ', startLoc);
					if (spaceLoc == std::string::npos) spaceLoc = line.length() - 1;
					else line.at(spaceLoc) = '\0';
					uv[i] = std::atol(line.c_str() + startLoc);
					startLoc = spaceLoc + 1;
				}
				uvs.value()[currUvId] = uv;
				currUvId++;
			}
		}
		objFile.close();
	} else {
		throw std::runtime_error("unknown mesh file type");
	}
}

std::shared_ptr<Mesh> Mesh::Create(const std::string& path, FileType type) {
	return std::shared_ptr<Mesh>(new Mesh(path, type));
}

Mesh::~Mesh() {
}

void Mesh::MoveToGPU(uint32_t vertexBinding, uint32_t vertexLocation) {
	VkVertexInputBindingDescription bindingDescription{ };
	bindingDescription.binding = vertexBinding;
	bindingDescription.stride = 3 * sizeof(float);
	bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

	VkVertexInputAttributeDescription attributeDescription;
	attributeDescription.binding = vertexBinding;
	attributeDescription.location = vertexLocation;
	attributeDescription.format = VK_FORMAT_R32G32B32_SFLOAT;
	attributeDescription.offset = 0;

	Vulkan::VulkanVertexBuffer vertexBuffer(vertices.size(), vertices.data());
}

bool Mesh::HasUVs() const {
	return uvs.has_value();
}

const std::vector<JMath::Vec3f>& Mesh::GetVertices() const {
	return vertices;
}

const std::vector<JMath::Vec3ui>& Mesh::GetIndices() const {
	return indices;
}

const std::vector<JMath::Vec2f>& Mesh::GetUVs() const {
	if (!HasUVs()) throw std::runtime_error("mesh does not have UVs");
	return uvs.value();
}

} // namespace Junia

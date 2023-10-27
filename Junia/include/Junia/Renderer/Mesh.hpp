#pragma once

#include <array>
#include <optional>
#include <string>
#include <vector>
#include <memory>
#include <JMath/Vector3.hpp>
#include <JMath/Vector2.hpp>

namespace Junia {

class Mesh {
public:
	enum class FileType : std::uint8_t {
		NONE,
		OBJ
	};

protected:
	std::vector<JMath::Vec3f> vertices{ };
	std::vector<JMath::Vec3ui> indices{ };
	std::optional<std::vector<JMath::Vec2f>> uvs{ };

	void LoadModel(const std::string& path, FileType type);

public:
	static std::shared_ptr<Mesh> Create(const std::string& path, FileType type);
	virtual ~Mesh();

	[[nodiscard]] bool HasUVs() const;
	[[nodiscard]] const std::vector<JMath::Vec3f>& GetVertices() const;
	[[nodiscard]] const std::vector<JMath::Vec3ui>& GetIndices() const;
	[[nodiscard]] const std::vector<JMath::Vec2f>& GetUVs() const;
};

} // namespace Junia

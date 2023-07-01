#pragma once

#include <cstdint>
#include <memory>

namespace Junia {

class Shader {
public:
	enum class Type : uint8_t {
		VERTEX                 = 0,
		FRAGMENT               = 1,
		TESSELATION_CONTROL    = 2,
		TESSELATION_EVALUATION = 3,
		GEOMETRY               = 4,
		//COMPUTE                = 5
	};

private:
	Type type;

protected:
	Shader(Type type);

public:
	static std::shared_ptr<Shader> Create(const std::string& path, Type type);
	virtual ~Shader() = 0;

	[[nodiscard]] inline Type GetType() const { return type; }
};

} // namespace Junia

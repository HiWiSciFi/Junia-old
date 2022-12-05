#pragma once
#include <memory>
#include <fstream>
#include <string>
#include <sstream>

namespace Junia
{
	class Logstream
	{
	public:
		Logstream(FILE* _stream);
		Logstream(const Logstream& other);
		~Logstream();

		template<typename T>
		Logstream& operator<<(T const& value)
		{
			stream << value;
			return *this;
		}

	private:
		FILE* fp;
		std::ofstream stream;
	};

	class Logger
	{
	public:
		explicit Logger(const std::string& name);

		~Logger();

		static std::shared_ptr<Logger> Create(const std::string& name = "Logger");

		Logstream Trace();
		Logstream Info();
		Logstream Warn();
		Logstream Error();
		Logstream Critical();

	private:
		std::string name = "";
		Logstream stream;
	};
}

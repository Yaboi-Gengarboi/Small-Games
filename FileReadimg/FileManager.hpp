// JLibrary
// FileManager.hpp
// Created on 08 January 2022 by Justyn Durnford
// Last modified on 24 July 2022 by Justyn Durnford
// Header file for the FileManager class.

#pragma once

#include "Buffer.hpp"

#include <cstddef>
#include <filesystem>
#include <fstream>
#include <stdexcept>
#include <string>
#include <vector>

import Array;

namespace jlib
{
	// Reads the line from fin into the string str.
	// Returns true on success.
	// Returns false on error.
	bool try_getline(std::ifstream& fin, std::string& str);

	///////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////

	// Class that handles reading and writing to files.
	class FileManager
	{
		std::filesystem::path _filepath;
		std::ifstream _fin;
		std::ofstream _fout;

		public:

		// Default constructor.
		FileManager() = default;

		// std::string constructor.
		// Opens the std::ifstream with the given path.
		FileManager(const std::string& filepath);

		// Secondary constructor.
		// Opens the std::ifstream with the given path.
		FileManager(const std::filesystem::path& filepath);

		// Reads count number of bytes into the buffer.
		void read(void* buffer, std::size_t count);

		// Reads count number of bytes into the buffer.
		void read(Buffer& buffer, std::size_t count);

		// Reads count number of bytes into the given std::string.
		void read(std::string& str, std::size_t count);

		// Reads count number of bytes into the given std::vector<char>.
		void read(std::vector<char>& vec, std::size_t count);

		// Reads count number of bytes into the given jlib::Array<char>.
		void read(jlib::Array<char>& arr, std::size_t count);

		// Reads bytes until a space or newline character is read or the end of the file is reached.
		// Returns a string filled with all of the read bytes except the trailing character.
		std::string read();

		// Reads bytes until a newline character is read or the end of the file is reached.
		// Returns a string filled with all of the read bytes except the trailing newline character.
		std::string readLine();

		// Reads all of the lines from the file.
		std::vector<std::string> readLines();

		// Writes count number of bytes to the file from the buffer.
		void write(const char* buffer, std::size_t count);

		// Writes the bytes in the range [begin, end) to the file.
		void write(const char* begin, const char* end);

		// Writes the std::string to the file.
		void write(const std::string& str);

		// Writes count characters from the std::string to the file.
		void write(const std::string& str, std::size_t count);

		// Writes count bytes from the std::vector<char> to the file.
		void write(const std::vector<char>& vec, std::size_t count);

		// Writes count bytes from the jlib::Array<char> to the file.
		void write(const jlib::Array<char>& arr, std::size_t count);

		// Writes the std::string_view to the file.
		void write(std::string_view view);

		// Writes the buffer to the file with a trailing newline.
		void writeLine(const char* buffer, std::size_t count);

		// Writes the std::string to the file with a trailing newline.
		void writeLine(const std::string& str);

		// 
		void writeLines(const std::string* lines, std::size_t count);

		// 
		void writeLines(const std::vector<std::string>& lines);

		// 
		void writeLines(const jlib::Array<std::string>& lines);

		// 
		void insertLine(const std::string& line, std::size_t line_index);

		// 
		void insertLines(const std::vector<std::string>& lines, std::size_t line_index);

		// 
		void append(const char* buffer, std::size_t count);

		// 
		void append(const std::string& str);

		// 
		void append(const std::string& str, std::size_t count);

		// 
		void append(const std::vector<char>& vec);

		// 
		void append(const jlib::Array<char>& arr);

		// Appends the std::string to the file with a trailing newline.
		// Returns the number of bytes written.
		void appendLine(const std::string& str);

		// 
		void appendLines(const std::string* lines, std::size_t count);

		// 
		void appendLines(const jlib::Array<std::string>& lines);

		// 
		void appendLines(const std::vector<std::string>& lines);

		// 
		bool eof() const;

		// 
		void open(const std::string path);

		// Closes the file.
		void close();

		// Returns true if the file is open.
		bool isOpen() const;

		// Returns true if the file is closed.
		bool isClosed() const;

		// 
		template <typename T>
		T get()
		{
			if (!_fin.is_open())
				throw std::runtime_error(std::string("FileManager::get() threw an exception: File cannot be read."));
			
			T var;
			_fin >> var;

			if (_fin.bad())
				throw std::runtime_error(std::string("FileManager::get() threw an exception: File cannot be read."));

			return var;
		}

		// 
		template <typename T>
		FileManager& operator >> (T& var)
		{
			if (!_fin.is_open())
				throw std::runtime_error(std::string("FileManager& operator >> (T& var) threw an exception: File cannot be read."));

			_fin >> var;

			if (_fin.bad())
				throw std::runtime_error(std::string("FileManager& operator >> (T& var) threw an exception: File cannot be read."));

			return *this;
		}

		// 
		template <typename T>
		FileManager& operator << (T& var)
		{
			_fin.close();
			_fout.open(_filepath);

			if (!_fout.is_open())
				throw std::runtime_error(std::string("FileManager& operator << (T& var) threw an exception: File cannot be written to."));

			_fout << var;

			if (_fin.bad())
				throw std::runtime_error(std::string("FileManager& operator << (T& var) threw an exception: File cannot be read."));

			return *this;
		}
	};
}
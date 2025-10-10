#pragma once
#include <stdexcept>
#include <string>

using namespace std;

class ValidationException : public runtime_error {
public:
	explicit ValidationException(const string& msg) : runtime_error(msg) {}
};

class RepositoryException : public runtime_error {
public:
	explicit RepositoryException(const string& msg) : runtime_error(msg) {}
};

class InputException : public runtime_error {
public:
	explicit InputException(const string& msg) : runtime_error(msg) {}
};
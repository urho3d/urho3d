/* Copyright 2010 Jukka Jylänki

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License. */
#pragma once

/** @file NetException.h
	@brief The class NetException. Common exception class thrown by kNet on errors. */
#include <exception>
#include <string>

namespace kNet
{

class NetException : public std::exception
{
public:
	explicit NetException(const char *reason)
	:exception(reason)
	{
	}

	~NetException() throw()
	{
	}

	const char *what() const throw() { return exception.c_str(); }

private:
	std::string exception;
};

} // ~kNet

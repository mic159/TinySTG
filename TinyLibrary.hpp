#ifndef TINYLIBRARY_HPP
#define TINYLIBRARY_HPP

#ifndef NULL
#ifdef __cplusplus
#define NULL 0
#else
#define NULL ((void *)0)
#endif
#endif

#if defined(_WIN32)
	#include "../../TinyLibrary/Screen.hpp"
	#include "../../TinyLibrary/Controller.hpp"
	#include "../../TinyLibrary/SoundStream.hpp"
	#include "../../TinyLibrary/TinyFile.hpp"
	#define String std::string
#elif defined(__ANDROID__)
	#include "../../TinyLibrary/Screen.hpp"
	#include "../../TinyLibrary/Controller.hpp"
	#include "../../TinyLibrary/SoundStream.hpp"
	#include "../../TinyLibrary/TinyFile.hpp"
	#define String std::string
#else
	#include "Screen.hpp"
	#include "Controller.hpp"
	#include "SoundStream.hpp"
	#include "TinyFile.hpp"
#endif

#endif

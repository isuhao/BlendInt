/*
 * FontManager.cpp
 *
 *  Created on: 2013年7月4日
 *      Author: zhanggyb
 */

#include <iostream>
#include <fstream>
#include <algorithm>

#include <boost/filesystem.hpp>

#include <BIL/FontConfig.h>

using namespace std;
using namespace boost;
using namespace boost::filesystem;

namespace BIL {

	FontConfig* FontConfig::service = NULL;

	bool FontConfig::initialized = false;

	bool FontConfig::initialize (void)
	{
		if (initialized)
			return false;

		// load system files    TODO: load more fonts
		// loadFontDir("/usr/share/fonts");

		if (!FcInit())
			return false;

		initialized = true;
		return true;
	}

	FontConfig::~FontConfig ()
	{
		FontIter it;
		for (it = _fonts.begin(); it != _fonts.end(); it++) {
			delete (*it).second;
		}
		_fonts.clear();

		// clear the namedb but no need to delete the objects again
		_namedb.clear();

		// finish fontconfig
		if (initialized)
			FcFini();

		if (_defaultFontBuf != NULL) {
			delete[] _defaultFontBuf;
			_defaultFontBuf = NULL;
			_defaultFontBufSize = 0;
		}

		initialized = false;
	}

	bool FontConfig::loadDefaultFontToMem (const string& family)
	{
		if (!initialized)
			return false;

		string filepath = getFontPath(family);

		if (filepath.empty()) {
			return false;
		}

		ifstream file(filepath.c_str(), ios::binary);
		if (file) {
			file.seekg(0, ios::end);
			fstream::pos_type filesize = file.tellg();
			file.seekg(0);

			if (_defaultFontBuf != NULL) {
				delete[] _defaultFontBuf;
				_defaultFontBuf = NULL;
			}

			_defaultFontBufSize = filesize;
			_defaultFontBuf = new unsigned char[_defaultFontBufSize];
			file.read((char*) _defaultFontBuf, _defaultFontBufSize);

			return true;
		}

		return false;
	}

	string FontConfig::getFontPath (const string& family, float size, bool bold,
	        bool italic)
	{
		string file;

		int weight = bold ? FC_WEIGHT_BOLD : FC_WEIGHT_REGULAR;
		int slant = italic ? FC_SLANT_ITALIC : FC_SLANT_ROMAN;

		FcPattern *pattern = FcPatternCreate();
		FcPatternAddDouble(pattern, FC_SIZE, size);
		FcPatternAddInteger(pattern, FC_WEIGHT, weight);
		FcPatternAddInteger(pattern, FC_SLANT, slant);
		FcPatternAddString(pattern, FC_FAMILY, (FcChar8*) family.c_str());
		FcConfigSubstitute(0, pattern, FcMatchPattern);
		FcDefaultSubstitute(pattern);
		FcResult result;
		FcPattern *match = FcFontMatch(0, pattern, &result);
		FcPatternDestroy(pattern);

		if (!match) {
			// TODO: return default font
			return getFontPath(Font("Sans"));
		} else {
			FcValue value;
			FcResult result = FcPatternGet(match, FC_FILE, 0, &value);
			if (result) {
				// print error
			} else {
				file = (char*) (value.u.s);
			}
		}

		FcPatternDestroy(match);

		return file;
	}

	string FontConfig::getFontPath (const Font& font)
	{
		string file;

		int weight = font.bold() ? FC_WEIGHT_BOLD : FC_WEIGHT_REGULAR;
		int slant = font.italic() ? FC_SLANT_ITALIC : FC_SLANT_ROMAN;

		FcPattern *pattern = FcPatternCreate();
		FcPatternAddDouble(pattern, FC_SIZE, font.size());
		FcPatternAddInteger(pattern, FC_WEIGHT, weight);
		FcPatternAddInteger(pattern, FC_SLANT, slant);
		FcPatternAddString(pattern, FC_FAMILY,
		        (FcChar8*) font.family().c_str());
		FcConfigSubstitute(0, pattern, FcMatchPattern);
		FcDefaultSubstitute(pattern);
		FcResult result;
		FcPattern *match = FcFontMatch(0, pattern, &result);
		FcPatternDestroy(pattern);

		if (!match) {
			// TODO: return default font
		} else {
			FcValue value;
			FcResult result = FcPatternGet(match, FC_FILE, 0, &value);
			if (result) {
				// print error
			} else {
				file = (char*) (value.u.s);
			}
		}

		FcPatternDestroy(match);

		return file;
	}

	bool FontConfig::loadFontFile (const string& file)
	{
		if (file.empty())
			return false;

		// check if we already load this font
		FontIter it = _fonts.find(file);
		if (it != _fonts.end())
			return false;

		// check if the path is valid
		if (!exists(path(file)))
			return false;

		/*
		 FontType *font = new FontType(_fontLib, file);
		 if (font->isValid()) {
		 _fonts[file] = font;
		 string psname = font->getPostscriptName();
		 if (!psname.empty()) {
		 _namedb[psname] = font;
		 }
		 } else {
		 delete font;
		 font = NULL;
		 }
		 */

		return true;
	}

	void FontConfig::loadFontDir (const string& path)
	{
		filesystem::path p(path);
		string ext;

		if (!exists(p))
			return;
		if (!is_directory(p))
			return;

		filesystem::directory_iterator end_it;
		filesystem::directory_iterator it(p);   // begin
		while (it != end_it) {
			if (is_directory(it->path())) {
				loadFontDir(it->path().string());
			}
			ext = extension(*it);
			if ((ext == ".ttf") || (ext == ".TTF") || (ext == ".otf")
			        || (ext == ".OTF")) {
				loadFontFile(it->path().string());
			}
			it++;
		}
	}

} /* namespace BIL */
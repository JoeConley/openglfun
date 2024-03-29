//
//  Log.h
//  GameEngine
//
//  Created by NoEvilPeople on 7/13/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef GameEngine_Log_h
#define GameEngine_Log_h

// Assert functionality only in debug
#ifdef DEBUG
#define LOG(x,...)					internal_Log(__FILE__,__FUNCTION__,__LINE__,false,x,##__VA_ARGS__)
#define LOG_WITH_METADATA(x,...)	internal_Log(__FILE__,__FUNCTION__,__LINE__,true,x,##__VA_ARGS__)
#else
#define LOG(x,...)
#define LOG_WITH_METADATA(x,...)
#endif

// Don't use me directly!  Use macros above
void internal_Log(const char* file, const char* function, const int line, bool printMetaInfo, const char* format, ...);

#endif
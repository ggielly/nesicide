#ifndef _APP_HPP_
#define _APP_HPP_

#include "ChannelMap.h"
#include "Settings.h"
#include "common.hpp"

class CSettings;

namespace core
{
	class SoundSink;
}

namespace app
{
  const CChannelMap * channelMap();
  const CSettings * settings();
}

#endif


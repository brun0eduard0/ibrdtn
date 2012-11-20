/*
 * EventDebugger.cpp
 *
 * Copyright (C) 2011 IBR, TU Braunschweig
 *
 * Written-by: Johannes Morgenroth <morgenroth@ibr.cs.tu-bs.de>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#include "core/EventDebugger.h"
#include "core/NodeEvent.h"
#include "core/CustodyEvent.h"
#include "core/BundleEvent.h"
#include "core/TimeEvent.h"
#include "core/GlobalEvent.h"
#include <ibrcommon/Logger.h>
#include <iostream>

using namespace std;
using namespace ibrcommon;

namespace dtn
{
	namespace core
	{
		EventDebugger::EventDebugger()
		{
		}

		EventDebugger::~EventDebugger()
		{
		}

		void EventDebugger::raiseEvent(const Event *evt) throw ()
		{
			try {
				const CustodyEvent &custody = dynamic_cast<const CustodyEvent&>(*evt);
				switch (custody.getAction())
				{
					case CUSTODY_ACCEPT:
						if (custody.getBundle().procflags & dtn::data::Bundle::CUSTODY_REQUESTED)
						{
							IBRCOMMON_LOGGER(notice) << evt->getName() << ": custody acceptance" << IBRCOMMON_LOGGER_ENDL;
						}
						break;

					case CUSTODY_REJECT:
						if (custody.getBundle().procflags & dtn::data::Bundle::CUSTODY_REQUESTED)
						{
							IBRCOMMON_LOGGER(notice) << evt->getName() << ": custody reject" << IBRCOMMON_LOGGER_ENDL;
						}
						break;
				};
				return;
			} catch (const std::bad_cast&) { }

			try {
				const BundleEvent &bundle = dynamic_cast<const BundleEvent&>(*evt);

				switch (bundle.getAction())
				{
				case BUNDLE_DELETED:
					IBRCOMMON_LOGGER(notice) << evt->getName() << ": bundle " << bundle.getBundle().toString() << " deleted" << IBRCOMMON_LOGGER_ENDL;
					break;
				case BUNDLE_CUSTODY_ACCEPTED:
					IBRCOMMON_LOGGER(notice) << evt->getName() << ": custody accepted for " << bundle.getBundle().toString() << IBRCOMMON_LOGGER_ENDL;
					break;
				case BUNDLE_FORWARDED:
					IBRCOMMON_LOGGER(notice) << evt->getName() << ": bundle " << bundle.getBundle().toString() << " forwarded" << IBRCOMMON_LOGGER_ENDL;
					break;
				case BUNDLE_DELIVERED:
					IBRCOMMON_LOGGER(notice) << evt->getName() << ": bundle " << bundle.getBundle().toString() << " delivered" << IBRCOMMON_LOGGER_ENDL;
					break;
				case BUNDLE_RECEIVED:
					IBRCOMMON_LOGGER(notice) << evt->getName() << ": bundle " << bundle.getBundle().toString() << " received" << IBRCOMMON_LOGGER_ENDL;
					break;
				case BUNDLE_STORED:
					IBRCOMMON_LOGGER(notice) << evt->getName() << ": bundle " << bundle.getBundle().toString() << " stored" << IBRCOMMON_LOGGER_ENDL;
					break;
				default:
					IBRCOMMON_LOGGER(notice) << evt->getName() << ": unknown" << IBRCOMMON_LOGGER_ENDL;
					break;
				}
				return;
			} catch (const std::bad_cast&) { }

			try {
				const NodeEvent &node = dynamic_cast<const NodeEvent&>(*evt);

				switch (node.getAction())
				{
				case NODE_AVAILABLE:
					IBRCOMMON_LOGGER(notice) << node.getName() << ": Node " << node.getNode().toString() << " available " << IBRCOMMON_LOGGER_ENDL;
					break;
				case NODE_UNAVAILABLE:
					IBRCOMMON_LOGGER(notice) << node.getName() << ": Node " << node.getNode().toString() << " unavailable" << IBRCOMMON_LOGGER_ENDL;
					break;
				default:
					IBRCOMMON_LOGGER(notice) << node.getName() << ": unknown" << IBRCOMMON_LOGGER_ENDL;
					break;
				}
				return;
			} catch (const std::bad_cast&) { }

			try {
				const TimeEvent &time = dynamic_cast<const TimeEvent&>(*evt);
				// do not debug print time events
				return;
			} catch (const std::bad_cast&) { }

			try {
				const GlobalEvent &global = dynamic_cast<const GlobalEvent&>(*evt);

				switch (global.getAction()) {
				case GlobalEvent::GLOBAL_SHUTDOWN:
					IBRCOMMON_LOGGER(notice) << global.getName() << ": Shutdown initiated." << IBRCOMMON_LOGGER_ENDL;
					break;
				case GlobalEvent::GLOBAL_RELOAD:
					IBRCOMMON_LOGGER(notice) << global.getName() << ": Reload signal received." << IBRCOMMON_LOGGER_ENDL;
					break;
				case GlobalEvent::GLOBAL_IDLE:
					break;
				case GlobalEvent::GLOBAL_BUSY:
					break;
				case GlobalEvent::GLOBAL_SUSPEND:
					IBRCOMMON_LOGGER(notice) << global.getName() << ": Go into suspend mode." << IBRCOMMON_LOGGER_ENDL;
					break;
				case GlobalEvent::GLOBAL_POWERSAVE:
					IBRCOMMON_LOGGER(notice) << global.getName() << ": Go into powersave mode." << IBRCOMMON_LOGGER_ENDL;
					break;
				case GlobalEvent::GLOBAL_WAKEUP:
					IBRCOMMON_LOGGER(notice) << global.getName() << ": Wake-up components." << IBRCOMMON_LOGGER_ENDL;
					break;
				case GlobalEvent::GLOBAL_INTERNET_AVAILABLE:
					IBRCOMMON_LOGGER(notice) << global.getName() << ": Internet connection is available." << IBRCOMMON_LOGGER_ENDL;
					break;
				case GlobalEvent::GLOBAL_INTERNET_UNAVAILABLE:
					IBRCOMMON_LOGGER(notice) << global.getName() << ": Internet connection is gone." << IBRCOMMON_LOGGER_ENDL;
					break;
				default:
					IBRCOMMON_LOGGER(notice) << evt->toString() << IBRCOMMON_LOGGER_ENDL;
					break;
				}
				return;
			} catch (const std::bad_cast&) { }

			// unknown event
			IBRCOMMON_LOGGER(notice) << evt->toString() << IBRCOMMON_LOGGER_ENDL;
		}
	}
}

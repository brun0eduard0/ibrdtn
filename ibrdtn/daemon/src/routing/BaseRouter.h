/*
 * BaseRouter.h
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

#ifndef BASEROUTER_H_
#define BASEROUTER_H_

#include "Component.h"
#include "routing/NeighborDatabase.h"
#include "routing/NodeHandshake.h"
#include "core/EventReceiver.h"
#include "storage/BundleStorage.h"
#include "storage/BundleSeeker.h"

#include "routing/RoutingExtension.h"
#include "routing/NodeHandshakeExtension.h"
#include "routing/RetransmissionExtension.h"

#include <ibrdtn/data/BundleSet.h>
#include <ibrdtn/data/DTNTime.h>
#include <ibrdtn/data/BundleID.h>
#include <ibrdtn/data/MetaBundle.h>

#include <ibrcommon/thread/Thread.h>
#include <ibrcommon/thread/Conditional.h>


namespace dtn
{
	namespace routing
	{
		class BaseRouter : public dtn::core::EventReceiver, public dtn::daemon::IntegratedComponent
		{
		public:
			class RoutingException : public ibrcommon::Exception
			{
				public:
					RoutingException(string what = "An error occured during routing.") throw() : Exception(what)
					{
					};
			};

			/**
			 * If no neighbour was found, this exception is thrown.
			 */
			class NoNeighbourFoundException : public RoutingException
			{
				public:
					NoNeighbourFoundException(string what = "No neighbour was found.") throw() : RoutingException(what)
					{
					};
			};

			/**
			 * If no route can be found, this exception is thrown.
			 */
			class NoRouteFoundException : public RoutingException
			{
				public:
					NoRouteFoundException(string what = "No route found.") throw() : RoutingException(what)
					{
					};
			};

			typedef std::list<RoutingExtension*> extension_list;

			BaseRouter();
			~BaseRouter();

			/**
			 * Add a routing extension to the routing core.
			 * @param extension
			 */
			void addExtension(RoutingExtension *extension);

			/**
			 * Returns a reference to all extensions.
			 * @return
			 */
			const extension_list& getExtensions() const;

			/**
			 * method to receive new events from the EventSwitch
			 */
			void raiseEvent(const dtn::core::Event *evt) throw ();

			/**
			 * provides direct access to the bundle storage
			 */
			dtn::storage::BundleStorage &getStorage();

			/**
			 * provides direct access to the bundle seeker
			 */
			dtn::storage::BundleSeeker &getSeeker();

			/**
			 * Request a neighbor handshake
			 * @param eid
			 */
			void doHandshake(const dtn::data::EID &eid);

			/**
			 * This method returns true, if the given BundleID is known.
			 * @param id
			 * @return
			 */
			bool isKnown(const dtn::data::BundleID &id);

			/**
			 * check if a bundle is known
			 * if the bundle is unkown add it to the known list and return false
			 * @param id
			 * @return
			 */
			bool filterKnown(const dtn::data::MetaBundle &meta);

			/**
			 * This method add a BundleID to the set of known bundles
			 * @param id
			 */
			void setKnown(const dtn::data::MetaBundle &meta);

			/**
			 * Get a vector (bloomfilter) of all known bundles.
			 * @return
			 */
			const dtn::data::BundleSet getKnownBundles();

			/**
			 * Get a vector (bloomfilter) of all purged bundles.
			 * @return
			 */
			const dtn::data::BundleSet getPurgedBundles();

			/**
			 * Add a bundle to the purge vector of this daemon.
			 * @param meta The bundle to purge.
			 */
			void addPurgedBundle(const dtn::data::MetaBundle &meta);

			/**
			 * @see Component::getName()
			 */
			virtual const std::string getName() const;

			/**
			 * Access to the neighbor database. Where several data about the neighbors is stored.
			 * @return
			 */
			NeighborDatabase& getNeighborDB();

		protected:
			virtual void componentUp() throw ();
			virtual void componentDown() throw ();

		private:
			void extensionsUp() throw ();
			void extensionsDown() throw ();

			void __forward_event(const dtn::core::Event *evt) const throw ();

			ibrcommon::Mutex _known_bundles_lock;
			dtn::data::BundleSet _known_bundles;

			ibrcommon::Mutex _purged_bundles_lock;
			dtn::data::BundleSet _purged_bundles;

			extension_list _extensions;

			NeighborDatabase _neighbor_database;
			NodeHandshakeExtension _nh_extension;
			RetransmissionExtension _retransmission_extension;
		};
	}
}


#endif /* BASEROUTER_H_ */

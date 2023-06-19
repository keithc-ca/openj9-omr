/*******************************************************************************
 * Copyright IBM Corp. and others 1991
 *
 * This program and the accompanying materials are made available under
 * the terms of the Eclipse Public License 2.0 which accompanies this
 * distribution and is available at https://www.eclipse.org/legal/epl-2.0/
 * or the Apache License, Version 2.0 which accompanies this distribution and
 * is available at https://www.apache.org/licenses/LICENSE-2.0.
 *
 * This Source Code may also be made available under the following
 * Secondary Licenses when the conditions for such availability set
 * forth in the Eclipse Public License, v. 2.0 are satisfied: GNU
 * General Public License, version 2 with the GNU Classpath
 * Exception [1] and GNU General Public License, version 2 with the
 * OpenJDK Assembly Exception [2].
 *
 * [1] https://www.gnu.org/software/classpath/license.html
 * [2] https://openjdk.org/legal/assembly-exception.html
 *
 * SPDX-License-Identifier: EPL-2.0 OR Apache-2.0 OR GPL-2.0-only WITH Classpath-exception-2.0 OR GPL-2.0-only WITH OpenJDK-assembly-exception-1.0
 *******************************************************************************/


#include "omrcfg.h"

#include "EnvironmentStandard.hpp"
#include "GCExtensionsBase.hpp"
#include "ObjectAllocationInterface.hpp"

#include "OMRVMThreadInterface.hpp"

void
GC_OMRVMThreadInterface::flushCachesForWalk(MM_EnvironmentBase *env)
{
	env->_objectAllocationInterface->flushCache(env);
	/* If we are in a middle of a concurrent GC, we want to flush GC caches, typically for mutator threads doing GC work.
	 * (GC threads are  smart enough to do it themselves, before they let the walk occur) */
	env->flushGCCaches(true);
}

void
GC_OMRVMThreadInterface::flushNonAllocationCaches(MM_EnvironmentBase *env)
{
	env->flushNonAllocationCaches();
}

void
GC_OMRVMThreadInterface::flushCachesForGC(MM_EnvironmentBase *env)
{
	flushCachesForWalk(env);
	flushNonAllocationCaches(env);
}

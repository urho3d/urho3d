/*************************************************************************
*                                                                       *
* Thread local storage access stub for Open Dynamics Engine,            *
* Copyright (C) 2008 Oleh Derevenko. All rights reserved.               *
* Email: odar@eleks.com (change all "a" to "e")                         *
*                                                                       *
* Open Dynamics Engine, Copyright (C) 2001,2002 Russell L. Smith.       *
* All rights reserved.  Email: russ@q12.org   Web: www.q12.org          *
*                                                                       *
*                                                                       *
* This library is free software; you can redistribute it and/or         *
* modify it under the terms of EITHER:                                  *
*   (1) The GNU Lesser General Public License as published by the Free  *
*       Software Foundation; either version 2.1 of the License, or (at  *
*       your option) any later version. The text of the GNU Lesser      *
*       General Public License is included with this library in the     *
*       file LICENSE.TXT.                                               *
*   (2) The BSD-style license that is included with this library in     *
*       the file LICENSE-BSD.TXT.                                       *
*                                                                       *
* This library is distributed in the hope that it will be useful,       *
* but WITHOUT ANY WARRANTY; without even the implied warranty of        *
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the files    *
* LICENSE.TXT and LICENSE-BSD.TXT for more details.                     *
*                                                                       *
*************************************************************************/

/*

ODE Thread Local Storage access stub implementation.

*/

#include <ode/common.h>
#include <ode/odemath.h>
#include "config.h"
#include "odetls.h"
#include "collision_trimesh_internal.h"
#include "util.h"


#if dTLS_ENABLED

//////////////////////////////////////////////////////////////////////////
// Class static fields

HTLSKEY COdeTls::m_ahtkStorageKeys[OTK__MAX] = { 0 };


//////////////////////////////////////////////////////////////////////////
// Initialization and finalization

bool COdeTls::Initialize(EODETLSKIND tkTLSKind)
{
	dIASSERT(!m_ahtkStorageKeys[tkTLSKind]);

	bool bResult = false;

	unsigned uOUFlags = 0;

	if (tkTLSKind == OTK_MANUALCLEANUP)
	{
		uOUFlags |= CTLSInitialization::SIF_MANUAL_CLEANUP_ON_THREAD_EXIT;
	}

	if (CTLSInitialization::InitializeTLSAPI(m_ahtkStorageKeys[tkTLSKind], OTI__MAX, uOUFlags))
	{
		bResult = true;
	}

	return bResult;
}

void COdeTls::Finalize(EODETLSKIND tkTLSKind)
{
	CTLSInitialization::FinalizeTLSAPI();

	m_ahtkStorageKeys[tkTLSKind] = 0;
}


void COdeTls::CleanupForThread()
{
	if (m_ahtkStorageKeys[OTK_MANUALCLEANUP])
	{
		CTLSInitialization::CleanupOnThreadExit();
	}
	else
	{
		dIASSERT(false); // The class is not intended to be cleaned up manually
	}
}


//////////////////////////////////////////////////////////////////////////
// Value modifiers

bool COdeTls::AssignDataAllocationFlags(EODETLSKIND tkTLSKind, unsigned uInitializationFlags)
{
	bool bResult = CThreadLocalStorage::SetStorageValue(m_ahtkStorageKeys[tkTLSKind], OTI_DATA_ALLOCATION_FLAGS, (tlsvaluetype)(size_t)uInitializationFlags);
	return bResult;
}


bool COdeTls::AssignTrimeshCollidersCache(EODETLSKIND tkTLSKind, TrimeshCollidersCache *pccInstance)
{
	dIASSERT(!CThreadLocalStorage::GetStorageValue(m_ahtkStorageKeys[tkTLSKind], OTI_TRIMESH_TRIMESH_COLLIDER_CACHE));

	bool bResult = CThreadLocalStorage::SetStorageValue(m_ahtkStorageKeys[tkTLSKind], OTI_TRIMESH_TRIMESH_COLLIDER_CACHE, (tlsvaluetype)pccInstance, &COdeTls::FreeTrimeshCollidersCache_Callback);
	return bResult;
}

void COdeTls::DestroyTrimeshCollidersCache(EODETLSKIND tkTLSKind)
{
	TrimeshCollidersCache *pccCacheInstance = (TrimeshCollidersCache *)CThreadLocalStorage::GetStorageValue(m_ahtkStorageKeys[tkTLSKind], OTI_TRIMESH_TRIMESH_COLLIDER_CACHE);

	if (pccCacheInstance)
	{
		FreeTrimeshCollidersCache(pccCacheInstance);

		CThreadLocalStorage::UnsafeSetStorageValue(m_ahtkStorageKeys[tkTLSKind], OTI_TRIMESH_TRIMESH_COLLIDER_CACHE, (tlsvaluetype)NULL);
	}
}


//////////////////////////////////////////////////////////////////////////
// Value type destructors

void COdeTls::FreeTrimeshCollidersCache(TrimeshCollidersCache *pccCacheInstance)
{
	delete pccCacheInstance;
}


//////////////////////////////////////////////////////////////////////////
// Value type destructor callbacks

void COdeTls::FreeTrimeshCollidersCache_Callback(tlsvaluetype vValueData)
{
	TrimeshCollidersCache *pccCacheInstance = (TrimeshCollidersCache *)vValueData;
	FreeTrimeshCollidersCache(pccCacheInstance);
}


#endif // #if dTLS_ENABLED


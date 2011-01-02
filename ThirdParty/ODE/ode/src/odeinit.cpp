/*************************************************************************
*                                                                       *
* Open Dynamics Engine, Copyright (C) 2001-2003 Russell L. Smith.       *
* All rights reserved.  Email: russ@q12.org   Web: www.q12.org          *
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

ODE initialization/finalization code

*/

#include <ode/common.h>
#include <ode/odemath.h>
#include <ode/odeinit.h>
// <ode/objects.h> included for dWorldQuickStepCleanup()
#include <ode/objects.h>
#include "config.h"
#include "collision_kernel.h"
#include "collision_trimesh_internal.h"
#include "odetls.h"
#include "odeou.h"
#include "util.h"


//****************************************************************************
// Initialization tracking variables

static unsigned int g_uiODEInitCounter = 0;
static unsigned int g_uiODEInitModes = 0;

enum EODEINITMODE
{
	OIM__MIN,

	OIM_AUTOTLSCLEANUP = OIM__MIN,
	OIM_MANUALTLSCLEANUP,

	OIM__MAX,
};

#if dTLS_ENABLED
static const EODETLSKIND g_atkTLSKindsByInitMode[OIM__MAX] =
{
	OTK_AUTOCLEANUP, // OIM_AUTOTLSCLEANUP,
	OTK_MANUALCLEANUP, // OIM_MANUALTLSCLEANUP,
};
#endif // #if dTLS_ENABLED

static inline bool IsODEModeInitialized(EODEINITMODE imInitMode)
{
	return (g_uiODEInitModes & (1U << imInitMode)) != 0;
}

static inline void SetODEModeInitialized(EODEINITMODE imInitMode)
{
	g_uiODEInitModes |= (1U << imInitMode);
}

static inline void ResetODEModeInitialized(EODEINITMODE imInitMode)
{
	g_uiODEInitModes &= ~(1U << imInitMode);
}

static inline bool IsODEAnyModeInitialized()
{
	return g_uiODEInitModes != 0;
}


enum
{
	TLD_INTERNAL_COLLISIONDATA_ALLOCATED = 0x00000001,
};

static bool AllocateThreadBasicDataIfNecessary(EODEINITMODE imInitMode)
{
	bool bResult = false;

	do
	{
#if dTLS_ENABLED
		EODETLSKIND tkTlsKind = g_atkTLSKindsByInitMode[imInitMode];

		const unsigned uDataAllocationFlags = COdeTls::GetDataAllocationFlags(tkTlsKind);

		// If no flags are set it may mean that TLS slot is not allocated yet
		if (uDataAllocationFlags == 0)
		{
			// Assign zero flags to make sure that TLS slot has been allocated
			if (!COdeTls::AssignDataAllocationFlags(tkTlsKind, 0))
			{
				break;
			}
		}

#endif // #if dTLS_ENABLED

		bResult = true;
	}
	while (false);

	return bResult;
}

static void FreeThreadBasicDataOnFailureIfNecessary(EODEINITMODE imInitMode)
{
#if dTLS_ENABLED

	if (imInitMode == OIM_MANUALTLSCLEANUP)
	{
		EODETLSKIND tkTlsKind = g_atkTLSKindsByInitMode[imInitMode];

		const unsigned uDataAllocationFlags = COdeTls::GetDataAllocationFlags(tkTlsKind);

		if (uDataAllocationFlags == 0)
		{
			// So far, only free TLS slot, if no subsystems have data allocated
			COdeTls::CleanupForThread();
		}
	}

#endif // #if dTLS_ENABLED
}

#if dTLS_ENABLED
static bool AllocateThreadCollisionData(EODETLSKIND tkTlsKind)
{
	bool bResult = false;

	do
	{
		dIASSERT(!(COdeTls::GetDataAllocationFlags(tkTlsKind) & TLD_INTERNAL_COLLISIONDATA_ALLOCATED));

#if dTRIMESH_ENABLED 

		TrimeshCollidersCache *pccColliderCache = new TrimeshCollidersCache();
		if (!COdeTls::AssignTrimeshCollidersCache(tkTlsKind, pccColliderCache))
		{
			delete pccColliderCache;
			break;
		}

#endif // dTRIMESH_ENABLED

		COdeTls::SignalDataAllocationFlags(tkTlsKind, TLD_INTERNAL_COLLISIONDATA_ALLOCATED);

		bResult = true;
	}
	while (false);

	return bResult;
}
#endif // dTLS_ENABLED

static bool AllocateThreadCollisionDataIfNecessary(EODEINITMODE imInitMode, bool &bOutDataAllocated)
{
	bool bResult = false;
	bOutDataAllocated = false;

	do 
	{
#if dTLS_ENABLED
		EODETLSKIND tkTlsKind = g_atkTLSKindsByInitMode[imInitMode];

		const unsigned uDataAllocationFlags = COdeTls::GetDataAllocationFlags(tkTlsKind);

		if ((uDataAllocationFlags & TLD_INTERNAL_COLLISIONDATA_ALLOCATED) == 0)
		{
			if (!AllocateThreadCollisionData(tkTlsKind))
			{
				break;
			}

			bOutDataAllocated = true;
		}

#endif // #if dTLS_ENABLED

		bResult = true;
	}
	while (false);

	return bResult;
}

static void FreeThreadCollisionData(EODEINITMODE imInitMode)
{
#if dTLS_ENABLED

	EODETLSKIND tkTlsKind = g_atkTLSKindsByInitMode[imInitMode];

	COdeTls::DestroyTrimeshCollidersCache(tkTlsKind);

	COdeTls::DropDataAllocationFlags(tkTlsKind, TLD_INTERNAL_COLLISIONDATA_ALLOCATED);

#endif // dTLS_ENABLED
}


static bool InitODEForMode(EODEINITMODE imInitMode)
{
	bool bResult = false;

#if dOU_ENABLED
	bool bOUCustomizationsDone = false;
#endif
#if dATOMICS_ENABLED
	bool bAtomicsInitialized = false;
#endif
#if dTLS_ENABLED
	EODETLSKIND tkTLSKindToInit = g_atkTLSKindsByInitMode[imInitMode];
	bool bTlsInitialized = false;
#endif

	do
	{
		bool bAnyModeAlreadyInitialized = IsODEAnyModeInitialized();

		if (!bAnyModeAlreadyInitialized)
		{
#if dOU_ENABLED
			if (!COdeOu::DoOUCustomizations())
			{
				break;
			}

			bOUCustomizationsDone = true;
#endif

#if dATOMICS_ENABLED
			if (!COdeOu::InitializeAtomics())
			{
				break;
			}

			bAtomicsInitialized = true;
#endif
		}

#if dTLS_ENABLED
		if (!COdeTls::Initialize(tkTLSKindToInit))
		{
			break;
		}

		bTlsInitialized = true;
#endif

		if (!bAnyModeAlreadyInitialized)
		{
#if dTRIMESH_ENABLED && dTRIMESH_OPCODE
			if (!Opcode::InitOpcode())
			{
				break;
			}
#endif

#if dTRIMESH_ENABLED && dTRIMESH_GIMPACT
			gimpact_init();
#endif

			dInitColliders();
		}

		bResult = true;
	}
	while (false);

	if (!bResult)
	{
#if dTLS_ENABLED
		if (bTlsInitialized)
		{
			COdeTls::Finalize(tkTLSKindToInit);
		}
#endif

#if dATOMICS_ENABLED
		if (bAtomicsInitialized)
		{
			COdeOu::FinalizeAtomics();
		}
#endif

#if dOU_ENABLED
		if (bOUCustomizationsDone)
		{
			COdeOu::UndoOUCustomizations();
		}
#endif
	}

	return bResult;
}


static bool AllocateODEDataForThreadForMode(EODEINITMODE imInitMode, unsigned int uiAllocateFlags)
{
	bool bResult = false;

	bool bCollisionDataAllocated = false;

	do
	{
		if (!AllocateThreadBasicDataIfNecessary(imInitMode))
		{
			break;
		}

		if (uiAllocateFlags & dAllocateFlagCollisionData)
		{
			if (!AllocateThreadCollisionDataIfNecessary(imInitMode, bCollisionDataAllocated))
			{
				break;
			}
		}

		bResult = true;
	}
	while (false);

	if (!bResult)
	{
		if (bCollisionDataAllocated)
		{
			FreeThreadCollisionData(imInitMode);
		}

		FreeThreadBasicDataOnFailureIfNecessary(imInitMode);
	}

	return bResult;
}


static void CloseODEForMode(EODEINITMODE imInitMode)
{
	bool bAnyModeStillInitialized = IsODEAnyModeInitialized();

	if (!bAnyModeStillInitialized)
	{
		dClearPosrCache();
		dFinitUserClasses();
		dFinitColliders();

#if dTRIMESH_ENABLED && dTRIMESH_GIMPACT
		gimpact_terminate();
#endif

#if dTRIMESH_ENABLED && dTRIMESH_OPCODE
		extern void opcode_collider_cleanup();
		// Free up static allocations in opcode
		opcode_collider_cleanup();

		Opcode::CloseOpcode();
#endif
	}

#if dTLS_ENABLED
	EODETLSKIND tkTLSKindToFinalize = g_atkTLSKindsByInitMode[imInitMode];
	COdeTls::Finalize(tkTLSKindToFinalize);
#endif

	if (!bAnyModeStillInitialized)
	{
#if dATOMICS_ENABLED
		COdeOu::FinalizeAtomics();
#endif

#if dOU_ENABLED
		COdeOu::UndoOUCustomizations();
#endif
	}
}


//****************************************************************************
// internal initialization and close routine implementations

static bool InternalInitODE(unsigned int uiInitFlags)
{
	bool bResult = false;

	do 
	{
		EODEINITMODE imInitMode = (uiInitFlags & dInitFlagManualThreadCleanup) ? OIM_MANUALTLSCLEANUP : OIM_AUTOTLSCLEANUP;

		if (!IsODEModeInitialized(imInitMode))
		{
			if (!InitODEForMode(imInitMode))
			{
				break;
			}

			SetODEModeInitialized(imInitMode);
		}

		++g_uiODEInitCounter;
		bResult = true;
	}
	while (false);

	return bResult;
}

static void InternalCloseODE()
{
	unsigned int uiCurrentMode = (--g_uiODEInitCounter == 0) ? OIM__MIN : OIM__MAX;
	for (; uiCurrentMode != OIM__MAX; ++uiCurrentMode)
	{
		if (IsODEModeInitialized((EODEINITMODE)uiCurrentMode))
		{
			// Must be called before CloseODEForMode()
			ResetODEModeInitialized((EODEINITMODE)uiCurrentMode);

			// Must be called after ResetODEModeInitialized()
			CloseODEForMode((EODEINITMODE)uiCurrentMode);
		}
	}
}

static bool InternalAllocateODEDataForThread(unsigned int uiAllocateFlags)
{
	bool bAnyFailure = false;

	for (unsigned uiCurrentMode = OIM__MIN; uiCurrentMode != OIM__MAX; ++uiCurrentMode)
	{
		if (IsODEModeInitialized((EODEINITMODE)uiCurrentMode))
		{
			if (!AllocateODEDataForThreadForMode((EODEINITMODE)uiCurrentMode, uiAllocateFlags))
			{
				bAnyFailure = true;
				break;
			}
		}
	}

	bool bResult = !bAnyFailure;
	return bResult;
}

static void InternalCleanupODEAllDataForThread()
{
#if dTLS_ENABLED
	COdeTls::CleanupForThread();
#endif
}

//****************************************************************************
// initialization and shutdown routines - allocate and initialize data,
// cleanup before exiting

void dInitODE()
{
	int bInitResult = InternalInitODE(0);
	dIASSERT(bInitResult); dVARIABLEUSED(bInitResult);

	int ibAllocResult = InternalAllocateODEDataForThread(dAllocateMaskAll);
	dIASSERT(ibAllocResult); dVARIABLEUSED(ibAllocResult);
}

int dInitODE2(unsigned int uiInitFlags/*=0*/)
	{
	bool bResult = false;
	
	bool bODEInitialized = false;

	do
		{
		if (!InternalInitODE(uiInitFlags))
		{
			break;
		}

		bODEInitialized = true;

		if (!InternalAllocateODEDataForThread(dAllocateFlagBasicData))
		{
			break;
		}
	
		bResult = true;
	}
	while (false);
	
	if (!bResult)
	{
		if (bODEInitialized)
		{
			InternalCloseODE();
}
	}

	return bResult;
}


int dAllocateODEDataForThread(unsigned int uiAllocateFlags)
{
	dUASSERT(g_uiODEInitCounter != 0, "Call dInitODE2 first");

	bool bResult = InternalAllocateODEDataForThread(uiAllocateFlags);
	return bResult;
}


void dCleanupODEAllDataForThread()
{
	dUASSERT(g_uiODEInitCounter != 0, "Call dInitODE2 first or delay dCloseODE until all threads exit");

	InternalCleanupODEAllDataForThread();
}


void dCloseODE()
{
	dUASSERT(g_uiODEInitCounter != 0, "dCloseODE must not be called without dInitODE2 or if dInitODE2 fails"); // dCloseODE must not be called without dInitODE2 or if dInitODE2 fails

	InternalCloseODE();
}


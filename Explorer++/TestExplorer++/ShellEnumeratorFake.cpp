// Copyright (C) Explorer++ Project
// SPDX-License-Identifier: GPL-3.0-only
// See LICENSE in the top level directory

#include "pch.h"
#include "ShellEnumeratorFake.h"

HRESULT ShellEnumeratorFake::EnumerateDirectory(PCIDLIST_ABSOLUTE pidlDirectory,
	std::vector<PidlChild> &outputItems, std::stop_token stopToken) const
{
	UNREFERENCED_PARAMETER(pidlDirectory);
	UNREFERENCED_PARAMETER(outputItems);
	UNREFERENCED_PARAMETER(stopToken);

	return m_shouldSucceed ? S_OK : E_FAIL;
}

void ShellEnumeratorFake::SetShouldSucceed(bool shouldSucceed)
{
	m_shouldSucceed = shouldSucceed;
}

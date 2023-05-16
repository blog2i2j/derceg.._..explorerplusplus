// Copyright (C) Explorer++ Project
// SPDX-License-Identifier: GPL-3.0-only
// See LICENSE in the top level directory

#pragma once

#include "Bookmarks/UI/BookmarkMenuBuilder.h"
#include "Bookmarks/UI/BookmarkMenuController.h"
#include "../Helper/WinRTBaseWrapper.h"
#include "../Helper/WindowSubclassWrapper.h"

class BookmarkItem;
class BookmarkTree;
class CoreInterface;
class IconFetcher;
class Navigator;

// Although it's not necessary, this class is effectively designed to be held
// for the lifetime of its parent class. Doing so is more efficient, as the
// parent window will only be subclassed once (on construction). It's then safe
// to call ShowMenu() as many times as needed.
class BookmarkMenu
{
public:
	BookmarkMenu(BookmarkTree *bookmarkTree, HINSTANCE resourceInstance,
		CoreInterface *coreInterface, Navigator *navigator, IconFetcher *iconFetcher,
		HWND parentWindow);

	BOOL ShowMenu(BookmarkItem *bookmarkItem, const POINT &pt,
		BookmarkMenuBuilder::IncludePredicate includePredicate = nullptr);

private:
	static const int MIN_ID = 1;
	static const int MAX_ID = 1000;

	LRESULT ParentWindowSubclass(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

	void OnMenuRightButtonUp(HMENU menu, int index, const POINT &pt);
	void OnMenuMiddleButtonUp(const POINT &pt, bool isCtrlKeyDown, bool isShiftKeyDown);

	LRESULT OnMenuDrag(HMENU menu, int itemPosition);
	LRESULT OnMenuGetObject(MENUGETOBJECTINFO *objectInfo);

	void OnMenuItemSelected(int menuItemId, BookmarkMenuBuilder::ItemIdMap &menuItemIdMappings);

	HWND m_parentWindow;
	BookmarkMenuBuilder m_menuBuilder;
	BookmarkMenuController m_controller;

	BookmarkTree *m_bookmarkTree = nullptr;

	bool m_showingMenu = false;
	BookmarkMenuBuilder::MenuInfo *m_menuInfo = nullptr;
	winrt::com_ptr<IDropTarget> m_dropTarget;

	std::vector<std::unique_ptr<WindowSubclassWrapper>> m_windowSubclasses;
};

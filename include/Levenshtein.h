/*
************************************************************************
// Copyright (C) 2003-2006, LPReditor SARL, all rights reserved.
// author : Raphael Poulenard.
************************************************************************
// Line.h: interface for the C_Line class.
//
This program is free software : you can redistribute itand /or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
GNU General Public License for more details.
//////////////////////////////////////////////////////////////////////
*/
// Levenshtein.h: interface for the Levenshtein class.
//
//////////////////////////////////////////////////////////////////////
#if !defined(LEVENSHTEIN_H)
#define LEVENSHTEIN_H

#ifndef GITHUB_LPREDITOR
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class Levenshtein  
{
public:
	int Get  (const char* a, const char* b);
	int Get  (const char* a, int aLen, const char* b, int bLen);

    int Get2 (char const *s, char const *t);
    int Get2 (char const *s, int n, char const *t, int dst);
	
	Levenshtein();
	virtual ~Levenshtein();


private:
	//****************************
	// Get minimum of three values
	//****************************
    int Minimum (int a, int b, int c)
	{
		int mi = a;
		
		if (b < mi)		mi = b;
		if (c < mi)		mi = c;
		
		return mi;
	}

	//**************************************************
	// Get a pointer to the specified cell of the matrix
	//**************************************************
    int *GetCellPointer (int *pOrigin, int col, int row, int nCols)
	{ return pOrigin + col + (row * (nCols + 1)); }
    
	//*****************************************************
	// Get the contents of the specified cell in the matrix
	//*****************************************************
	int GetAt (int *pOrigin, int col, int row, int nCols)
	{
		int *pCell = GetCellPointer (pOrigin, col, row, nCols);
		return *pCell;
	}
	
	//********************************************************
	// Fill the specified cell in the matrix with the value x
	//********************************************************
	void PutAt (int *pOrigin, int col, int row, int nCols, int x)
	{
		int *pCell = GetCellPointer (pOrigin, col, row, nCols);
		*pCell = x;
	}
};

#endif //GITHUB_LPREDITOR
#endif // !defined(AFX_LEVENSHTEIN_H__1652E861_359D_11D6_BB45_000102A63CA4__INCLUDED_)

/*
 * CDE - Common Desktop Environment
 *
 * Copyright (c) 1993-2012, The Open Group. All rights reserved.
 *
 * These libraries and programs are free software; you can
 * redistribute them and/or modify them under the terms of the GNU
 * Lesser General Public License as published by the Free Software
 * Foundation; either version 2 of the License, or (at your option)
 * any later version.
 *
 * These libraries and programs are distributed in the hope that
 * they will be useful, but WITHOUT ANY WARRANTY; without even the
 * implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 * PURPOSE. See the GNU Lesser General Public License for more
 * details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with these libraries and programs; if not, write
 * to the Free Software Foundation, Inc., 51 Franklin Street, Fifth
 * Floor, Boston, MA 02110-1301 USA
 */
/* $XConsortium: strton.c /main/3 1995/11/01 18:51:11 rswiston $ */
/***************************************************************
*                                                              *
*                      AT&T - PROPRIETARY                      *
*                                                              *
*         THIS IS PROPRIETARY SOURCE CODE LICENSED BY          *
*                          AT&T CORP.                          *
*                                                              *
*                Copyright (c) 1995 AT&T Corp.                 *
*                     All Rights Reserved                      *
*                                                              *
*           This software is licensed by AT&T Corp.            *
*       under the terms and conditions of the license in       *
*       http://www.research.att.com/orgs/ssr/book/reuse        *
*                                                              *
*               This software was created by the               *
*           Software Engineering Research Department           *
*                    AT&T Bell Laboratories                    *
*                                                              *
*               For further information contact                *
*                     gsf@research.att.com                     *
*                                                              *
***************************************************************/

/* : : generated by proto : : */

#if !defined(__PROTO__)
#if defined(__STDC__) || defined(__cplusplus) || defined(_proto) || defined(c_plusplus)
#if defined(__cplusplus)
#define __MANGLE__	"C"
#else
#define __MANGLE__
#endif
#define __STDARG__
#define __PROTO__(x)	x
#define __OTORP__(x)
#define __PARAM__(n,o)	n
#if !defined(__STDC__) && !defined(__cplusplus)
#if !defined(c_plusplus)
#define const
#endif
#define signed
#define void		int
#define volatile
#define __V_		char
#else
#define __V_		void
#endif
#else
#define __PROTO__(x)	()
#define __OTORP__(x)	x
#define __PARAM__(n,o)	o
#define __MANGLE__
#define __V_		char
#define const
#define signed
#define void		int
#define volatile
#endif
#if defined(__cplusplus) || defined(c_plusplus)
#define __VARARG__	...
#else
#define __VARARG__
#endif
#if defined(__STDARG__)
#define __VA_START__(p,a)	va_start(p,a)
#else
#define __VA_START__(p,a)	va_start(p)
#endif
#endif
#include <ast.h>
#include <ctype.h>

long
strton __PARAM__((const char* s, char** e, char* b, int m), (s, e, b, m)) __OTORP__(const char* s; char** e; char* b; int m;){
	long		n;
	int		c;
	int		r;
	const char*	p;
	int			z;

	if (!b || (r = *b) < 0 || r > 64) r = 0;
	while (isspace(*s)) s++;
	if ((z = (*s == '-')) || *s == '+') s++;
	p = s;
	if (r <= 1)
	{
		if ((c = *p++) >= '0' && c <= '9')
		{
			n = c - '0';
			if ((c = *p) >= '0' && c <= '9')
			{
				n = n * 10 + c - '0';
				p++;
			}
			if (*p == '#')
			{
				if (n >= 2 && n <= 64)
				{
					s = p + 1;
					r = n;
				}
			}
			else if (r) r = 0;
			else if (*s == '0')
			{
				if ((c = *(s + 1)) == 'x' || c == 'X')
				{
					s += 2;
					r = 16;
				}
				else if (c >= '0' && c <= '7') r = 8;
			}
		}
		if (b && r) *b = r;
	}
	n = 0;
	if (r > 36) for (;;)
	{
		if ((c = *s++) >= '0' && c <= '9') c -= '0';
		else if (c >= 'a' && c <= 'z') c -= 'a' - 10;
		else if (c >= 'A' && c <= 'Z') c -= 'A' - 36;
		else if (c == '_') c = 62;
		else if (c == '@') c = 63;
		else
		{
			s--;
			break;
		}
		n = n * r + c;
	}
	else
	{
		if (r) m = -1;
		else r = 10;
		if (r > 10) for (;;)
		{
			if ((c = *s++) >= '0' && c <= '9') c -= '0';
			else if (c >= 'a' && c <= 'z') c -= 'a' - 10;
			else if (c >= 'A' && c <= 'Z') c -= 'A' - 10;
			else break;
			n = n * r + c;
		}
		else for (;;)
		{
			if ((c = *s++) >= '0' && c <= '9') c -= '0';
			else break;
			n = n * r + c;
		}
		if (m >= 0) switch (c)
		{
		case 'b':
		case 'B':
			n *= 512;
			break;
		case 'c':
		case 'C':
			break;
		case 'g':
		case 'G':
			n *= 1024 * 1024 * 1024;
			break;
		case 'k':
		case 'K':
			n *= 1024;
			break;
		case 'm':
		case 'M':
			n *= 1024 * 1024;
			break;
		case '.':
			n *= 100;
			for (m = 10; *s >= '0' && *s <= '9'; m /= 10) 
				n += m * (*s++ - '0');
			break;
		default:
			s--;
			if (m > 1) n *= m;
			break;
		}
		else s--;
	}
	if (e) *e = (char*)s;
	return(z ? -n : n);
}
